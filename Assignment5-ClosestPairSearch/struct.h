#ifndef STRUCT_H
#define STRUCT_H

#include <stdlib.h>     // size_t
#include <float.h>      // DBL_MAX

struct PointStruct
{
    double x;
    double y;
} point;
typedef struct PointStruct Point;

struct PairStruct
{
    Point first;
    Point second;
};
typedef struct PairStruct Pair;

struct AlgReturnStruct
{
    Point* points;
    size_t num_points;
    double distance;
    Pair closest_pair;
};
typedef struct AlgReturnStruct AlgReturn;

struct BoundaryMergeReturnStruct {
    Pair closest_pair;
    double distance;
};
typedef struct BoundaryMergeReturnStruct BoundaryMergeReturn;

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
