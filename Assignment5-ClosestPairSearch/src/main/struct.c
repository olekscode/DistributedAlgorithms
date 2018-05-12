#include "struct.h"

Point new_point(double x, double y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Pair new_pair(Point first, Point second)
{
    Pair pair;
    pair.first = first;
    pair.second = second;
    return pair;
}

Pair empty_pair()
{
	Point first = new_point(DBL_MAX, DBL_MAX);
	Point second = new_point(DBL_MAX, DBL_MAX);
	return new_pair(first, second);
}