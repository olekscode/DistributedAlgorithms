#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//#include "mapreduce.h"


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

void count(int* counts, int* arr, size_t size, int range_from, int range_to)
{
    // Inclusive range
    size_t counts_size = range_to - range_from + 1;

    for (int i = 0; i < counts_size; ++i) {
        counts[i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        int val = arr[i];
        counts[val - range_from] += 1;
    }
}

void mapper(int* doc, size_t doc_size, struct Pair* counts)
{
    for (int i = 0; i < doc_size; ++i) {
        counts[i].key = doc[i];
        counts[i].value = 1;
    }
}

void reducer(struct ShuffledStruct shuffled, struct Pair* counts)
{
    counts->key = shuffled.key;
    counts->value = 0;

    for (int j = 0; j < shuffled.size; ++j) {
        counts->value += shuffled.values[j];
    }
}

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

void mapreduce(int* arr, size_t size, struct Pair* counts, size_t num_keys)
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

void read_csv(const char* fname, int* arr, size_t size)
{
    FILE* fstream = fopen(fname, "r");
    
    for (int i = 0; i < size; i++) {
        fscanf(fstream, "%d,", &arr[i]);
    }

    fclose(fstream);
}

int main(int argc, char* argv[])
{
    const size_t SIZE = pow(2, 27);
    const char* FILE_NAME = "input/numbers-big.csv";

    srand(time(NULL));

    clock_t start, end;
    double diff;

    int* numbers = malloc(SIZE * sizeof(int));

    printf("Reading numbers from '%s'\n", FILE_NAME);

    start = clock();
    read_csv(FILE_NAME, numbers, SIZE);
    end = clock();
    diff = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time to read: %f seconds\n", diff);

    struct Pair* counts = malloc(10 * sizeof(pair));

    start = clock();
    mapreduce(numbers, SIZE, counts, 10);
    end = clock();
    diff = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time to run sequential MapReduce: %f seconds\n", diff);
    printf("Result of sequential MapReduce:\n");
    print_dict(counts, 10);


    // int* counts = malloc(range_size * sizeof(int));

    // generate_array(arr, size, range_from, range_to);
    // count(counts, arr, size, range_from, range_to);

    // print_array(arr, size);
    // print_array(counts, range_size);

    free(counts);
    free(numbers);

    return 0;
}