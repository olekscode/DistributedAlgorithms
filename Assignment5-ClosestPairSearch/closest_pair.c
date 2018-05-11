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
        for (size_t j = 1; j <= 7; ++j) {
            double dist = euclidean_dist(M[i], M[i + j]);
            
            if (dist < min_dist) {
                min_pair = new_pair(M[i], M[i + j]);
                min_dist = dist;
            }
        }
    }
    return new_boundary_merge_return(min_pair, min_dist);
}

static AlgReturn _closest_pair(Point* sorted_points, size_t size)
{
    if (size < 2) {
        return new_alg_return(sorted_points, size, DBL_MAX, empty_pair());
    }
    
    size_t middle = size / 2;
    double median_x = sorted_points[middle].x;

    Point* left = sorted_points;
    Point* right = sorted_points + middle;

    AlgReturn ret_left = _closest_pair(left, middle);
    AlgReturn ret_right = _closest_pair(right, size - middle);

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

    BoundaryMergeReturn ret = boundary_merge(
        sorted_points, size,
        ret_left.closest_pair,
        ret_left.distance,
        ret_right.closest_pair,
        ret_right.distance,
        median_x);

    return new_alg_return(sorted_points, size, ret.distance, ret.closest_pair);
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

Pair closest_pair(Point* points, size_t size)
{
    Point sorted_points[size];

    for (size_t i = 0; i < size; ++i) {
        sorted_points[i] = points[i];
    }

    sort_x(sorted_points, size);

    AlgReturn ret = _closest_pair(sorted_points, size);

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

// typedef struct {
//     Point* sorted_points;
//     size_t size;
// } ClosestPairArgs;

// void* _closest_pair_par(void* args)
// {
//     ClosestPairArgs* actual_args = args;
//     Point* sorted_points = (*args).sorted_points;
//     size_t size = (*args).size;

//     if (size < 2) {
//         return new_alg_return(sorted_points, size, DBL_MAX, empty_pair());
//     }
    
//     size_t middle = size / 2;
//     double median_x = sorted_points[middle].x;

//     Point* left = sorted_points;
//     Point* right = sorted_points + middle;

//     pthread_t tid;
//     void *status;

//     ClosestPairArgs *args_left = malloc(sizeof *args_left);
//     (*args_left).sorted_points = &max_prime;
//     args->ith_prime = &primeArray[i];

//     pthread_create(&tid, NULL, _closest_pair_par, args);

//     free(args);

//     AlgReturn ret_left = _closest_pair(left, middle);
//     AlgReturn ret_right = _closest_pair(right, size - middle);

//     merge_by_y(ret_left.points, middle,
//                ret_right.points, size - middle,
//                sorted_points);

//     BoundaryMergeReturn ret = boundary_merge(
//         sorted_points, size,
//         ret_left.closest_pair,
//         ret_left.distance,
//         ret_right.closest_pair,
//         ret_right.distance,
//         median_x);

//     return new_alg_return(sorted_points, size, ret.distance, ret.closest_pair);
// }

// Pair closest_pair_par(Point* points, size_t size)
// {
//     Point sorted_points[size];

//     for (size_t i = 0; i < size; ++i) {
//         sorted_points[i] = points[i];
//     }

//     sort_x(sorted_points, size);

//     AlgReturn ret = _closest_pair_par(sorted_points, size);

//     return ret.closest_pair;
// }