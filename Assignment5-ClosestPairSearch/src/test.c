#include <stdlib.h>          // size_t

#include "struct.h"          // Point, Pair
#include "generate.h"        // generate_arr_of_rand_points
#include "closest_pair.h"    // closest_pair
#include "equal.h"           // close_dbl, equal

#include "test_framework.h"  // TEST, TestResult, run_all

TestResult test_euclidean_dist()
{
    TestResult res;
    res.name = "test_euclidean_dist";

    Point a = new_point(0, 3);
    Point b = new_point(4, 0);

    double dist = euclidean_dist(a, b);

    res.passed = close_dbl(dist, 5.0);
    return res;
}

TestResult test_closest_pair_seq_2_points()
{
    TestResult res;
    res.name = "test_closest_pair_seq_2_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair pair = closest_pair_seq(points, num_points);

    Pair expected_pair = new_pair(
        new_point(0, 3),
        new_point(4, 0));

    res.passed = equal_pairs(pair, expected_pair);
    return res;
}

TestResult test_closest_pair_seq_5_points()
{
    TestResult res;
    res.name = "test_closest_pair_seq_5_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0),
        new_point(3, 3),
        new_point(2, 5),
        new_point(4, 4) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair pair = closest_pair_seq(points, num_points);

    Pair expected_pair = new_pair(
        new_point(3, 3),
        new_point(4, 4));

    res.passed = equal_pairs(pair, expected_pair);
    return res;
}

TestResult test_closest_pair_par_2_points()
{
    TestResult res;
    res.name = "test_closest_pair_par_2_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair pair = closest_pair_par(points, num_points);

    Pair expected_pair = new_pair(
        new_point(0, 3),
        new_point(4, 0));

    res.passed = equal_pairs(pair, expected_pair);
    return res;
}

TestResult test_closest_pair_par_5_points()
{
    TestResult res;
    res.name = "test_closest_pair_par_5_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0),
        new_point(3, 3),
        new_point(2, 5),
        new_point(4, 4) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair pair = closest_pair_par(points, num_points);

    Pair expected_pair = new_pair(
        new_point(3, 3),
        new_point(4, 4));

    res.passed = equal_pairs(pair, expected_pair);
    return res;
}

TestResult test_actual_closest_pair_2_points()
{
    TestResult res;
    res.name = "test_actual_closest_pair_2_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair pair = actual_closest_pair(points, num_points);

    Pair expected_pair = new_pair(
        new_point(0, 3),
        new_point(4, 0));

    res.passed = equal_pairs(pair, expected_pair);
    return res;
}

TestResult test_actual_closest_pair_5_points()
{
    TestResult res;
    res.name = "test_actual_closest_pair_5_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0),
        new_point(3, 3),
        new_point(2, 5),
        new_point(4, 4) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair pair = actual_closest_pair(points, num_points);

    Pair expected_pair = new_pair(
        new_point(3, 3),
        new_point(4, 4));

    res.passed = equal_pairs(pair, expected_pair);
    return res;
}

int main(int argc, char* argv[])
{
    TEST* tests[] = {
        test_euclidean_dist,
        test_closest_pair_seq_2_points,
        test_closest_pair_seq_5_points,
        test_closest_pair_par_2_points,
        test_closest_pair_par_5_points,
        test_actual_closest_pair_2_points,
        test_actual_closest_pair_5_points
    };

    int n = (int) sizeof(tests) / sizeof(tests[0]);

    run_all(tests, n);

    return 0;
}