#ifndef EQUAL_H
#define EQUAL_H

#include <math.h>    // fabs

#include "struct.h"  // Point, Pair

#define PREC 0.00001

int close_dbl(double a, double b);
int equal_points(Point a, Point b);
int equal_pairs(Pair a, Pair b);

#endif // EQUAL_H