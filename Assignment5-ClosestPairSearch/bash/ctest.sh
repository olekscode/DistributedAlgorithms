#!/bin/bash

cd src;
gcc test.c test_framework.c struct.c generate.c print.c merge.c closest_pair.c equal.c timeit.c -o ../bin/test;
../bin/test