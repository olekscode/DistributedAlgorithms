#include "closest_pair.h"

double euclidean_dist(Point a, Point b)
{
    //! Euclidean distance between two points.
    /*!
    \param a first point.
    \param a second point.

    Example:
    Point a = new_point(3, 0);
    Point b = new_point(0, 4);
    euclidean_dist(a, b); // 5.0
    */
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

typedef struct {
    Pair closest_pair;
    double distance;
} BoundaryMergeReturn;

static BoundaryMergeReturn boundary_merge(
    Point* points, size_t size,
    Pair left_pair, double left_distance,
    Pair right_pair, double right_distance,
    double median_x)
{
    double min_dist;
    Pair min_pair;

    if (left_distance < right_distance) {
        min_dist = left_distance;
        min_pair = left_pair;
    }
    else {
        min_dist = right_distance;
        min_pair = right_pair;
    }

    Point M[size];
    size_t size_M = 0;

    for (size_t i = 0; i < size; ++i) {
        if ((points[i].x >= median_x - min_dist) &&
            (points[i].x <= median_x + min_dist))
        {
            M[size_M] = points[i];
            ++size_M;
        }
    }

    for (size_t i = 0; i < size_M - MIN(7, size_M - 1); ++i) {
        for (size_t j = 1; j <= MIN(7, size_M - i - 1); ++j) {
            double dist = euclidean_dist(M[i], M[i + j]);
            
            if (dist < min_dist) {
                min_pair = new_pair(M[i], M[i + j]);
                min_dist = dist;
            }
        }
    }

    BoundaryMergeReturn ret;
    ret.closest_pair = min_pair;
    ret.distance = min_dist;

    return ret;
}

typedef struct {
    Point* points;
    size_t num_points;
    Pair closest_pair;
    double distance;
} AlgReturn;

static AlgReturn closest_pair_rec_seq(Point* sorted_points, size_t size)
{
    if (size < 2) {
        AlgReturn ret;
        ret.points = sorted_points;
        ret.num_points = size;
        ret.distance = DBL_MAX;
        return ret;
    }
    
    size_t middle = size / 2;
    double median_x = sorted_points[middle].x;

    Point* left = sorted_points;
    Point* right = sorted_points + middle;

    AlgReturn ret_left = closest_pair_rec_seq(left, middle);
    AlgReturn ret_right = closest_pair_rec_seq(right, size - middle);

    // printf("L = \n");
    // print_arr_of_points(left, middle);
    // printf("L closest pair = \n");
    // print_pair(ret_left.closest_pair);
    // printf("R = \n");
    // print_arr_of_points(right, size - middle);
    // printf("R closest pair = \n");
    // print_pair(ret_right.closest_pair);

    // printf("L* = \n");
    // print_arr_of_points(ret_left.points, middle);
    // printf("R* = \n");
    // print_arr_of_points(ret_right.points, size - middle);

    merge_by_y(ret_left.points, middle,
               ret_right.points, size - middle,
               sorted_points);

    // printf("P* = \n");
    // print_arr_of_points(sorted_points, size);

    BoundaryMergeReturn bm_ret = boundary_merge(
        sorted_points, size,
        ret_left.closest_pair,
        ret_left.distance,
        ret_right.closest_pair,
        ret_right.distance,
        median_x);

    AlgReturn ret;
    ret.points = sorted_points;
    ret.num_points = size;
    ret.closest_pair = bm_ret.closest_pair;
    ret.distance = bm_ret.distance;

    return ret;
}

typedef struct {
    Point* points;
    size_t num_points;
} ClosestPairArgs;

void* closest_pair_rec_wrap(void* args_void)
{
    //! pthread wrapper for closest_pair_rec.

    ClosestPairArgs* args = (ClosestPairArgs*) args_void;
    Point* points = (*args).points;
    size_t num_points = (*args).num_points;

    AlgReturn* ret = malloc(sizeof(AlgReturn));
    *ret = closest_pair_rec_seq(points, num_points);
    pthread_exit(ret);
}

static AlgReturn closest_pair_rec_par(Point* sorted_points, size_t size)
{
    if (size < 2) {
        AlgReturn ret;
        ret.points = sorted_points;
        ret.num_points = size;
        ret.distance = DBL_MAX;
        return ret;
    }
    
    size_t middle = size / 2;
    double median_x = sorted_points[middle].x;

    Point* left = sorted_points;
    Point* right = sorted_points + middle;

    pthread_t tid;

    ClosestPairArgs args;
    args.points = left;
    args.num_points = middle;

    void* ret_void;

    if(pthread_create(&tid, NULL, &closest_pair_rec_wrap, &args)) {
        fprintf(stderr, "Error creating thread\n");
        exit(0);
    }

    AlgReturn ret_right = closest_pair_rec_seq(right, size - middle);

    if(pthread_join(tid, (void**) &ret_void)) {
        fprintf(stderr, "Error joining thread\n");
        free(ret_void);
        exit(0);
    }

    AlgReturn* ret_left_ptr = (AlgReturn*) ret_void;
    AlgReturn ret_left = *ret_left_ptr;
    free(ret_left_ptr);

    merge_by_y(ret_left.points, middle,
               ret_right.points, size - middle,
               sorted_points);

    BoundaryMergeReturn bm_ret = boundary_merge(
        sorted_points, size,
        ret_left.closest_pair,
        ret_left.distance,
        ret_right.closest_pair,
        ret_right.distance,
        median_x);

    AlgReturn ret;
    ret.points = sorted_points;
    ret.num_points = size;
    ret.closest_pair = bm_ret.closest_pair;
    ret.distance = bm_ret.distance;

    return ret;
}

static void swap_point(Point* a, Point* b)
{
    Point tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sort_x(Point* points, size_t size)
{
    // TODO: Make it parallel
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (points[i].x > points[j].x) {
                swap_point(&points[i], &points[j]);
            }
        }
    }
}

Pair closest_pair_par(Point* points, size_t size)
{
    Point sorted_points[size];

    for (size_t i = 0; i < size; ++i) {
        sorted_points[i] = points[i];
    }

    sort_x(sorted_points, size);

    AlgReturn ret = closest_pair_rec_par(sorted_points, size);

    return ret.closest_pair;
}

Pair closest_pair_seq(Point* points, size_t size)
{
    Point sorted_points[size];

    for (size_t i = 0; i < size; ++i) {
        sorted_points[i] = points[i];
    }

    sort_x(sorted_points, size);

    AlgReturn ret = closest_pair_rec_seq(sorted_points, size);

    return ret.closest_pair;
}

Pair actual_closest_pair(Point* points, size_t size)
{
    double min_dist = DBL_MAX;
    Pair min_pair = empty_pair();

    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            double dist = euclidean_dist(points[i], points[j]);

            if (dist < min_dist) {
                min_dist = dist;
                min_pair = new_pair(points[i], points[j]);
            }
        }
    }
    return min_pair;
}