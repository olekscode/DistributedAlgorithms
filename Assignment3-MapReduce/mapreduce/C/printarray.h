#ifndef PRINTARRAY_H
#define PRINTARRAY_H

#include <stdlib.h>
#include "mapreduce.h"

void print_array(int* arr, size_t size)
{
    printf("[");

    for (int i = 0; i < size - 1; ++i) {
        printf("%d, ", arr[i]);
    }

    printf("%d]\n", arr[size - 1]);
}

void print_dict(struct Pair* pairs, size_t size)
{
    printf("{");

    for (int i = 0; i < size - 1; ++i) {
        printf("%d: %d, ", pairs[i].key, pairs[i].value);
    }

    printf("%d: %d}\n", pairs[size - 1].key, pairs[size - 1].value);
}

#endif // PRINTARRAY_H