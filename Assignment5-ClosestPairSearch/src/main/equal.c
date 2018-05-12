#include "equal.h"

int close_dbl(double a, double b)
{
    return fabs(a - b) < PREC;
}

int equal_points(Point a, Point b)
{
    return close_dbl(a.x, b.x) && close_dbl(a.y, b.y);
}

int equal_pairs(Pair a, Pair b)
{
    return (equal_points(a.first, b.first) &&
            equal_points(a.second, b.second)) ||
           (equal_points(a.first, b.second) &&
            equal_points(a.second, b.first));
}