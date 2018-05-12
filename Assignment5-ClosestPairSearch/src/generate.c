#include "generate.h"

static double rand_double(double a, double b)
{
    return (double) rand() / RAND_MAX * (b - a) + a;
}

Point generate_rand_point(Point upper_left, Point lower_right)
{
    double x = rand_double(upper_left.x, lower_right.x);
    double y = rand_double(upper_left.y, lower_right.y);
    return new_point(x, y);
}

void generate_arr_of_rand_points(
    Point* arr, size_t size,
    Point upper_left,
    Point lower_right)
{
    //! Initializes an array with random elements from 0 to MAXEL.
    /*!
    \param arr an empty array for writing the results.
    \param size size of an array.
    */
    for (size_t i = 0; i < size; ++i) {
        arr[i] = generate_rand_point(upper_left, lower_right);
    }
}