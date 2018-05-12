#!/bin/bash

cd src/main;
gcc ../test/test.c ../test/test_framework.c struct.c generate.c print.c merge.c closest_pair.c equal.c timeit.c -o ../../bin/test;
../../bin/test