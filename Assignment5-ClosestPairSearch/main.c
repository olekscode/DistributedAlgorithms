#include <stdio.h>    // printf
#include <stdlib.h>   // size_t, srand
#include <time.h>     // time
#include <pthread.h>

#include "struct.h"   // Point, Pair, AlgReturn, new_point, new_pair etc.
#include "generate.h"
#include "closest_pair.h"
#include "print.h"    // print_point, print_pair, print_arr_of_points

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

    pair = actual_closest_pair(arr, n);
    print_pair(pair);

    return 0;
}
