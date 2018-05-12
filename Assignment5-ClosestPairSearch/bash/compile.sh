#!/bin/bash

cd src/main;
gcc -pthread main.c struct.c generate.c print.c merge.c closest_pair.c timeit.c -o ../../bin/closest_pair