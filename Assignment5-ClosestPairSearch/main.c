#include <stdio.h>    // printf
#include <stdlib.h>   // size_t, rand, srand, RAND_MAX
#include <time.h>     // time
#include <float.h>    // DBL_MAX
#include <math.h>     // pow, sqrt

#include "struct.h"   // Point, Pair, AlgReturn, new_point, new_pair etc.
#include "print.h"    // print_point, print_pair, print_arr_of_points
#include "merge.h"    // merge_by_y

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b))

double rand_double(double a, double b)
{
    return (double) rand() / RAND_MAX * (b - a) + a;
}

Point generate_rand_point(Point upper_left, Point lower_right)
{
    double x = rand_double(upper_left.x, lower_right.x);
    double y = rand_double(upper_left.y, lower_right.y);
    return new_point(x, y);
}

void generate_arr_of_rand_points(Point arr[], int size,
                                 Point upper_left,
                                 Point lower_right)
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

void swap_point(Point* a, Point* b)
{
    Point tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_x(Point* points, size_t size)
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

BoundaryMergeReturn boundary_merge(
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

    for (size_t i = 0; i < size_M - min(7, size_M - 1); ++i) {
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

AlgReturn _closest_pair(Point* sorted_points, size_t size)
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

    merge_by_y(ret_left.points, middle,
               ret_right.points, size - middle,
               sorted_points);

    BoundaryMergeReturn ret = boundary_merge(
        sorted_points, size,
        ret_left.closest_pair,
        ret_left.distance,
        ret_right.closest_pair,
        ret_right.distance,
        median_x);

    return new_alg_return(sorted_points, size, ret.distance, ret.closest_pair);
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

int main(int argc, char* argv[])
{
    srand(time(NULL));

    Point UPPER_LEFT = new_point(-100, -100);
    Point LOWER_RIGHT = new_point(100, 100);

    size_t n = 10;
    Point arr[n];

    generate_arr_of_rand_points(arr, n, UPPER_LEFT, LOWER_RIGHT);
    
    print_arr_of_points(arr, n);

    Pair pair = closest_pair(arr, n);
    print_pair(pair);

    return 0;
}
