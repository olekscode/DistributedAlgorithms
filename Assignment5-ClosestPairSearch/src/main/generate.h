#ifndef GENERATE_H
#define GENERATE_H

#include <stdlib.h>   // size_t, rand, RAND_MAX

#include "struct.h"   // Point

Point generate_rand_point(
	Point upper_left,
	Point lower_right);

void generate_arr_of_rand_points(
	Point* arr, size_t size,
    Point upper_left,
    Point lower_right);

#endif // GENERATE_H