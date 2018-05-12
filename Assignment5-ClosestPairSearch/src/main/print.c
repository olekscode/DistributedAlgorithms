#include "print.h"

void print_point(Point p)
{
    printf("(%f, %f)", p.x, p.y);
}

void print_arr_of_points(Point arr[], size_t size)
{
    //! Prints the given array to stdout.
    /*!
    Format:
    [1, 2, 3, 4, 5].
    \param arr the array to be printed.
    \param size size of an array.
    */
    printf("[");

    for (size_t i = 0; i < size - 1; ++i) {
        print_point(arr[i]);
        printf(",\n");
    }

    print_point(arr[size - 1]);
    printf("]\n");
}

void print_pair(Pair pair)
{
    printf("{");
    print_point(pair.first);
    printf(", ");
    print_point(pair.second);
    printf("}\n");
}