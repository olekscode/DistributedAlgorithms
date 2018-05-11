#ifndef STRUCT_H
#define STRUCT_H

#include <stdlib.h>     // size_t
#include <float.h>      // DBL_MAX

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point first;
    Point second;
} Pair;

typedef struct {
    Point* points;
    size_t num_points;
    double distance;
    Pair closest_pair;
} AlgReturn;

typedef struct {
    Pair closest_pair;
    double distance;
} BoundaryMergeReturn;

Point new_point(double x, double y);

Pair new_pair(Point first, Point second);

AlgReturn new_alg_return(
    Point points[], size_t num_points,
    double distance, Pair closest_pair);

BoundaryMergeReturn new_boundary_merge_return(
    Pair closest_pair,
    double distance);

Pair empty_pair();

#endif // STRUCT_H
