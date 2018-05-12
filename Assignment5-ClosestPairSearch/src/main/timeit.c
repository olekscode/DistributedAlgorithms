#include "timeit.h"

TimeitReturn timeit(Pair (*func)(Point*, size_t), Point* points, size_t size)
{
    clock_t start = clock();
    Pair pair = func(points, size);
    clock_t end = clock();
    float seconds = (float) (end - start) / CLOCKS_PER_SEC;

    TimeitReturn ret;
    ret.seconds = seconds;
    ret.pair = pair;
    return ret;
}