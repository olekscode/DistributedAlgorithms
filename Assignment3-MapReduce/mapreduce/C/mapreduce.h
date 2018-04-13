#include <stdlib.h>

struct Pair
{
    int key;
    int value;
} pair;

struct ShuffledStruct
{
    int key;
    int* values;
    size_t size;
} shuffled_struct;

void mapreduce(int* arr, size_t size, struct Pair* counts, size_t num_keys,
               void (*mapper)(int*, size_t, struct Pair*),
               void (*reducer)(struct ShuffledStruct, struct Pair*));