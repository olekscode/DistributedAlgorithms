#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>     // printf
#include "struct.h"   // Point, Pair

void print_point(Point p);
void print_arr_of_points(Point arr[], size_t size);
void print_pair(Pair pair);

#endif // PRINT_H