#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "mapreduce.h"
#include "printarray.h"

void read_csv(const char* fname, int* arr, size_t size)
{
    FILE* fstream = fopen(fname, "r");
    
    for (int i = 0; i < size; i++) {
        fscanf(fstream, "%d,", &arr[i]);
    }

    fclose(fstream);
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

int main(int argc, char* argv[])
{
    // const size_t SIZE = pow(2, 10);
    // const char* FILE_NAME = "input/numbers-small.csv";

    const size_t SIZE = pow(2, 22);
    const char* FILE_NAME = "input/numbers.csv";

    // const size_t SIZE = pow(2, 27);
    // const char* FILE_NAME = "input/numbers-big.csv";

    const size_t RANGE_SIZE = 10;

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

    struct Pair* counts = malloc(RANGE_SIZE * sizeof(pair));

    start = clock();
    mapreduce(numbers, SIZE, counts, RANGE_SIZE, &mapper, &reducer);
    end = clock();
    diff = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time to run sequential MapReduce: %f seconds\n", diff);
    printf("Result of sequential MapReduce:\n");
    print_dict(counts, RANGE_SIZE);

    free(counts);
    free(numbers);

    return 0;
}