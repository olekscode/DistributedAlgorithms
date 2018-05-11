#ifndef CLOSEST_PAIR_H
#define CLOSEST_PAIR_H

#include <stdlib.h>   // size_t
#include <float.h>    // DBL_MAX
#include <math.h>     // pow, sqrt

#include "struct.h"   // Point, Pair, AlgReturn, new_point, new_pair etc.
#include "merge.h"    // merge_by_y

// minimum and maximum macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

double euclidean_dist(Point a, Point b);
Pair closest_pair(Point* points, size_t size);
Pair actual_closest_pair(Point* points, size_t size);

#endif // CLOSEST_PAIR_H