#include "mapreduce.h"

int shuffle(struct Pair** mapped, size_t num_mappers, size_t doc_size,
            struct ShuffledStruct* shuffled, size_t num_keys, size_t buffer_size)
{
    int num_inserted_keys = 0;
    int was_this_key_inserted;
    int k;

    for (int i = 0; i < num_mappers; ++i) {
        for (int j = 0; j < doc_size; ++j) {
            was_this_key_inserted = 0;
            k = 0;

            while (k < num_inserted_keys && !was_this_key_inserted) {
                if (shuffled[k].key == mapped[i][j].key) {
                    was_this_key_inserted = 1;
                }
                else {
                    ++k;
                }
            }

            if (was_this_key_inserted) {
                shuffled[k].values[shuffled[k].size] = 1;
                shuffled[k].size += 1;
            }
            else {
                shuffled[num_inserted_keys].key = mapped[i][j].key;
                shuffled[num_inserted_keys].values[0] = 1;
                shuffled[num_inserted_keys].size = 1;
                num_inserted_keys += 1;
            }
        }
    }
    return num_inserted_keys;
}

void mapreduce(int* arr, size_t size, struct Pair* counts, size_t num_keys,
               void (*mapper)(int*, size_t, struct Pair*),
               void (*reducer)(struct ShuffledStruct, struct Pair*))
{
    size_t num_mappers = 4;
    size_t doc_size = size / num_mappers;

    struct Pair** mapped = malloc(num_mappers * sizeof(struct Pair*));

    for (int i = 0; i < num_mappers; ++i) {
        mapped[i] = malloc(doc_size * sizeof(pair));
    }

    for (int i = 0; i < num_mappers; ++i) {
        mapper(arr + (i * doc_size), doc_size, mapped[i]);
    }

    size_t buffer_size = size;

    struct ShuffledStruct* shuffled = malloc(num_keys * sizeof(shuffled_struct));

    for (int i = 0; i < num_keys; ++i) {
        shuffled[i].values = malloc(buffer_size * sizeof(int));
    }

    int num_inserted_keys = shuffle(mapped, num_mappers, doc_size,
                                    shuffled, num_keys, buffer_size);

    for (int i = 0; i < num_inserted_keys; ++i) {
        reducer(shuffled[i], &counts[i]);
    }

    for (int i = 0; i < num_keys; ++i) {
        free(shuffled[i].values);
    }

    free(shuffled);

    for (int i = 0; i < num_mappers; ++i) {
        free(mapped[i]);
    }

    free(mapped);
}