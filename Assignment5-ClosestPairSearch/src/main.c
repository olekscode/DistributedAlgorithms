#include <stdio.h>        // printf
#include <stdlib.h>       // size_t, srand
#include <time.h>         // time

#include "struct.h"       // Point, Pair
#include "generate.h"     // generate_arr_of_rand_points
#include "closest_pair.h" // closest_pair
#include "timeit.h"       // ctimeit, TimeitReturn
#include "print.h"        // print_pair, print_arr_of_points

int main(int argc, char* argv[])
{
    srand(time(NULL));

    Point UPPER_LEFT = new_point(-100, -100);
    Point LOWER_RIGHT = new_point(100, 100);

    size_t n = 10000;
    Point arr[n];

    generate_arr_of_rand_points(arr, n, UPPER_LEFT, LOWER_RIGHT);

    TimeitReturn ret;

    ret = timeit(closest_pair_seq, arr, n);
    print_pair(ret.pair);
    printf("Time: %f sec.\n\n", ret.seconds);

    ret = timeit(closest_pair_par, arr, n);
    print_pair(ret.pair);
    printf("Time: %f sec.\n\n", ret.seconds);

    ret = timeit(actual_closest_pair, arr, n);
    print_pair(ret.pair);
    printf("Time: %f sec.\n\n", ret.seconds);

    return 0;
}
