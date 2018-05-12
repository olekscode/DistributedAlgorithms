#ifndef TIMEIT_H
#define TIMEIT_H

#include <stdlib.h>       // size_t
#include <time.h>         // clock_t, clock, CLOCKS_PER_SEC

#include "struct.h"       // Point, Pair

typedef struct {
    float seconds;
    Pair pair;
} TimeitReturn;

TimeitReturn timeit(
    Pair (*func)(Point*, size_t),
    Point* points, size_t size);

#endif // TIMEIT_H