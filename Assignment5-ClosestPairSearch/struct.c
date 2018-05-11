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

AlgReturn new_alg_return(Point points[], size_t num_points,
	                     double distance, Pair closest_pair)
{
    AlgReturn ret;
    ret.points = points;
    ret.num_points = num_points;
    ret.distance = distance;
    ret.closest_pair = closest_pair;
    return ret;
}

BoundaryMergeReturn new_boundary_merge_return(
    Pair closest_pair,
    double distance)
{
    BoundaryMergeReturn ret;
    ret.closest_pair = closest_pair;
    ret.distance = distance;
    return ret;
}

Pair empty_pair()
{
	Point first = new_point(DBL_MAX, DBL_MAX);
	Point second = new_point(DBL_MAX, DBL_MAX);
	return new_pair(first, second);
}