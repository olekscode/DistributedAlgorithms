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

void map(int* doc, size_t doc_size, struct Pair* counts)
{
    for (int i = 0; i < doc_size; ++i) {
        counts[i].key = doc[i];
        counts[i].value = 1;
    }
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
        map(arr + (i * doc_size), doc_size, mapped[i]);
    }

    for (int i = 0; i < num_keys; ++i) {
        counts[i].key = i;
        counts[i].value = i * i;
    }

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
    const size_t SIZE = pow(2, 3);
    const char* FILE_NAME = "input/numbers.csv";

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
    mapreduce(numbers, SIZE, counts, 10);
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