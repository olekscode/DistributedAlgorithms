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

Point new_point(double x, double y);

Pair new_pair(Point first, Point second);

Pair empty_pair();

#endif // STRUCT_H
