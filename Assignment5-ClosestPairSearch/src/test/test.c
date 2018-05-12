#include <stdlib.h>                // size_t

#include "../main/struct.h"        // Point, Pair
#include "../main/generate.h"      // generate_arr_of_rand_points
#include "../main/closest_pair.h"  // closest_pair
#include "../main/equal.h"         // close_dbl, equal

#include "test_framework.h"        // TEST, TestResult, run_all

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

TestResult template_test_closest_pair_seq(
    char* name,
    Point* points, size_t num_points,
    Pair expected_pair)
{
    Pair pair = closest_pair_seq(points, num_points);

    TestResult res;
    res.name = name;
    res.passed = equal_pairs(pair, expected_pair);

    return res;
}

TestResult template_test_closest_pair_par(
    char* name,
    Point* points, size_t num_points,
    Pair expected_pair)
{
    Pair pair = closest_pair_par(points, num_points);

    TestResult res;
    res.name = name;
    res.passed = equal_pairs(pair, expected_pair);
    
    return res;
}

TestResult test_closest_pair_seq_2_pos_int_points()
{
    char* name = "test_closest_pair_seq_2_pos_int_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(0, 3),
        new_point(4, 0));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_seq_2_neg_int_points()
{
    char* name = "test_closest_pair_seq_2_neg_int_points";

    Point points[] = {
        new_point(0, -3),
        new_point(-4, 0) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(0, -3),
        new_point(-4, 0));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_seq_2_pos_double_points()
{
    char* name = "test_closest_pair_seq_2_pos_double_points";

    Point points[] = {
        new_point(1.7, 1.5),
        new_point(2.03, 0.2) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(1.7, 1.5),
        new_point(2.03, 0.2));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_seq_2_neg_double_points()
{
    char* name = "test_closest_pair_seq_2_neg_double_points";

    Point points[] = {
        new_point(-1.7, 1.5),
        new_point(-2.03, -0.2) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(-1.7, 1.5),
        new_point(-2.03, -0.2));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_seq_5_pos_int_points()
{
    char* name = "test_closest_pair_seq_5_pos_int_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0),
        new_point(3, 3),
        new_point(2, 5),
        new_point(4, 4) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(3, 3),
        new_point(4, 4));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_seq_5_neg_int_points()
{
    char* name = "test_closest_pair_seq_5_neg_int_points";

    Point points[] = {
        new_point(0, -3),
        new_point(-4, 0),
        new_point(-3, -3),
        new_point(-2, -5),
        new_point(-4, -4) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(-3, -3),
        new_point(-4, -4));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_seq_5_pos_double_points()
{
    char* name = "test_closest_pair_seq_5_pos_double_points";

    Point points[] = {
        new_point(0.02, 3.01),
        new_point(4.01, 0.01),
        new_point(3.02, 3.01),
        new_point(2.02, 5.01),
        new_point(4.01, 4.01) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(3.02, 3.01),
        new_point(4.01, 4.01));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_seq_5_neg_double_points()
{
    char* name = "test_closest_pair_seq_5_neg_double_points";

    Point points[] = {
        new_point(-0.02, -3.01),
        new_point(-4.01, -0.01),
        new_point(-3.02, -3.01),
        new_point(-2.02, -5.01),
        new_point(-4.01, -4.01) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(-3.02, -3.01),
        new_point(-4.01, -4.01));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_seq_5_same_zero_points()
{
    char* name = "test_closest_pair_seq_5_same_zero_points";

    Point points[] = {
        new_point(0, 0),
        new_point(0, 0),
        new_point(0, 0),
        new_point(0, 0),
        new_point(0, 0) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(0, 0),
        new_point(0, 0));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_seq_5_same_nonzero_points()
{
    char* name = "test_closest_pair_seq_5_same_nonzero_points";

    Point points[] = {
        new_point(4, 1),
        new_point(4, 1),
        new_point(4, 1),
        new_point(4, 1),
        new_point(4, 1) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(4, 1),
        new_point(4, 1));

    return template_test_closest_pair_seq(
        name, points, num_points, expected_pair);
}

// =============================================================================

TestResult test_closest_pair_par_2_pos_int_points()
{
    char* name = "test_closest_pair_par_2_pos_int_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(0, 3),
        new_point(4, 0));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_par_2_neg_int_points()
{
    char* name = "test_closest_pair_par_2_neg_int_points";

    Point points[] = {
        new_point(0, -3),
        new_point(-4, 0) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(0, -3),
        new_point(-4, 0));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_par_2_pos_double_points()
{
    char* name = "test_closest_pair_par_2_pos_double_points";

    Point points[] = {
        new_point(1.7, 1.5),
        new_point(2.03, 0.2) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(1.7, 1.5),
        new_point(2.03, 0.2));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_par_2_neg_double_points()
{
    char* name = "test_closest_pair_par_2_neg_double_points";

    Point points[] = {
        new_point(-1.7, 1.5),
        new_point(-2.03, -0.2) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(-1.7, 1.5),
        new_point(-2.03, -0.2));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_par_5_pos_int_points()
{
    char* name = "test_closest_pair_par_5_pos_int_points";

    Point points[] = {
        new_point(0, 3),
        new_point(4, 0),
        new_point(3, 3),
        new_point(2, 5),
        new_point(4, 4) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(3, 3),
        new_point(4, 4));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_par_5_neg_int_points()
{
    char* name = "test_closest_pair_par_5_neg_int_points";

    Point points[] = {
        new_point(0, -3),
        new_point(-4, 0),
        new_point(-3, -3),
        new_point(-2, -5),
        new_point(-4, -4) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(-3, -3),
        new_point(-4, -4));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_par_5_pos_double_points()
{
    char* name = "test_closest_pair_par_5_pos_double_points";

    Point points[] = {
        new_point(0.02, 3.01),
        new_point(4.01, 0.01),
        new_point(3.02, 3.01),
        new_point(2.02, 5.01),
        new_point(4.01, 4.01) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(3.02, 3.01),
        new_point(4.01, 4.01));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_par_5_neg_double_points()
{
    char* name = "test_closest_pair_par_5_neg_double_points";

    Point points[] = {
        new_point(-0.02, -3.01),
        new_point(-4.01, -0.01),
        new_point(-3.02, -3.01),
        new_point(-2.02, -5.01),
        new_point(-4.01, -4.01) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(-3.02, -3.01),
        new_point(-4.01, -4.01));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_par_5_same_zero_points()
{
    char* name = "test_closest_pair_par_5_same_zero_points";

    Point points[] = {
        new_point(0, 0),
        new_point(0, 0),
        new_point(0, 0),
        new_point(0, 0),
        new_point(0, 0) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(0, 0),
        new_point(0, 0));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

TestResult test_closest_pair_par_5_same_nonzero_points()
{
    char* name = "test_closest_pair_par_5_same_nonzero_points";

    Point points[] = {
        new_point(4, 1),
        new_point(4, 1),
        new_point(4, 1),
        new_point(4, 1),
        new_point(4, 1) };

    size_t num_points = (size_t) sizeof(points) / sizeof(points[0]);

    Pair expected_pair = new_pair(
        new_point(4, 1),
        new_point(4, 1));

    return template_test_closest_pair_par(
        name, points, num_points, expected_pair);
}

// =============================================================================

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
        test_closest_pair_seq_2_pos_int_points,
        test_closest_pair_seq_2_neg_int_points,
        test_closest_pair_seq_2_pos_double_points,
        test_closest_pair_seq_2_neg_double_points,
        test_closest_pair_seq_5_pos_int_points,
        test_closest_pair_seq_5_neg_int_points,
        test_closest_pair_seq_5_pos_double_points,
        test_closest_pair_seq_5_neg_double_points,
        test_closest_pair_seq_5_same_zero_points,
        test_closest_pair_seq_5_same_nonzero_points,
        test_closest_pair_par_2_pos_int_points,
        test_closest_pair_par_2_neg_int_points,
        test_closest_pair_par_2_pos_double_points,
        test_closest_pair_par_2_neg_double_points,
        test_closest_pair_par_5_pos_int_points,
        test_closest_pair_par_5_neg_int_points,
        test_closest_pair_par_5_pos_double_points,
        test_closest_pair_par_5_neg_double_points,
        test_closest_pair_par_5_same_zero_points,
        test_closest_pair_par_5_same_nonzero_points,
        test_actual_closest_pair_2_points,
        test_actual_closest_pair_5_points
    };

    int n = (int) sizeof(tests) / sizeof(tests[0]);

    run_all(tests, n);

    return 0;
}