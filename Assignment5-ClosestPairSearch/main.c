#include <stdio.h>    // printf
#include <stdlib.h>   // rand, srand, RAND_MAX
#include <time.h>     // time
#include <float.h>    // DBL_MAX

struct Point
{
    double x;
    double y;
} point;

struct Pair
{
    struct Point first;
    struct Point second;
};

struct PointsDist
{
    struct Point* points;
    size_t num_points;
    double distance;
};

struct Point new_point(double x, double y)
{
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

struct Pair new_pair(struct Point first, struct Point second)
{
    struct Pair pair;
    pair.first = first;
    pair.second = second;
    return pair;
}

struct PointsDist new_points_dist(struct Point points[], size_t num_points, double distance)
{
    struct PointsDist pd;
    pd.points = points;
    pd.num_points = num_points;
    pd.distance = distance;
    return pd;
}

double rand_double(double a, double b)
{
    return (double) rand() / RAND_MAX * (b - a) + a;
}

struct Point generate_rand_point(struct Point upper_left,
                                 struct Point lower_right)
{
    double x = rand_double(upper_left.x, lower_right.x);
    double y = rand_double(upper_left.y, lower_right.y);
    return new_point(x, y);
}

void generate_arr_of_rand_points(struct Point arr[], int size,
                                 struct Point upper_left,
                                 struct Point lower_right)
{
    //! Initializes an array with random elements from 0 to MAXEL.
    /*!
    \param arr an empty array for writing the results.
    \param size size of an array.
    */
    for (int i = 0; i < size; ++i) {
        arr[i] = generate_rand_point(upper_left, lower_right);
    }
}

void print_point(struct Point p)
{
    printf("(%f, %f)", p.x, p.y);
}

void print_arr_of_points(struct Point arr[], int size)
{
    //! Prints the given array to stdout.
    /*!
    Format:
    [1, 2, 3, 4, 5].
    \param arr the array to be printed.
    \param size size of an array.
    */
    printf("[");

    for (int i = 0; i < size - 1; ++i) {
        print_point(arr[i]);
        printf(", ");
    }

    print_point(arr[size - 1]);
    printf("]\n");
}

void print_pair(struct Pair pair)
{
    printf("{");
    print_point(pair.first);
    printf(", ");
    print_point(pair.second);
    printf("}\n");
}

struct Point* merge_by_y(struct Point* left_points, size_t num_left_points,
                         struct Point* right_points, size_t num_right_points)
{

}

double boundary_merge(struct Point* points, size_t size,
                      double left_distance, double right_distance)
{

}

struct PointsDist _closest_pair(struct Point* points, size_t size)
{
    if (size < 2) return new_points_dist(points, size, DBL_MAX);
    
    size_t middle = size / 2;

    struct Point* left = points;
    struct Point* right = points + middle * sizeof(point);

    struct PointsDist pd_left = _closest_pair(left, middle);
    struct PointsDist pd_right = _closest_pair(right, size - middle);

    struct Point* points_sorted = merge_by_y(left.points, middle, right.points, size - middle);
    double distance = boundary_merge(points_sorted, left.distance, right.distance);

    return new_points_dist(points_sorted, size, distance);
}

struct Pair closest_pair(struct Point points[], size_t size)
{
    struct Pair pair;
    pair.first = points[0];
    pair.second = points[1];
    return pair;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));

    struct Point UPPER_LEFT = new_point(0, 0);
    struct Point LOWER_RIGHT = new_point(1, 1);

    size_t n = 10;
    struct Point arr[n];

    generate_arr_of_rand_points(arr, n, UPPER_LEFT, LOWER_RIGHT);
    print_arr_of_points(arr, n);
    print_pair(closest_pair(arr, n));

    struct PointsDist pd = _closest_pair(arr, 1);
    printf("%f\n", pd.distance);

    return 0;
}
