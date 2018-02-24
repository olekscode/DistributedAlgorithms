/*
* DEFINITION - Blelloch (1990)
*
* The all-prefix-sums operation (exclusive scan) takes a binary
* associative operator + with identity I, and an ordered set
* of n elements
* [a0, a1, ..., an−1],
* 
* and returns the ordered set
* [a0, (a0 + a1), ..., (a0 + a1 + ... + an−1)].
*
* Source:
* 1. https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch39.html
* 2. https://www.cs.cmu.edu/~guyb/papers/Ble93.pdf
*/

/* Hints:
* If you have 4 cores - create 4 processes, not 100
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAXCORES 4
#define MAXEL 10

 
double log2( double n ) {
    //! Calculates log2 of number.
    return log(n) / log(2);  
}  

void random_array(int arr[], int size) {
    //! Initializes an array with random elements from 0 to MAXEL.
    /*!
    \param arr an empty array wor writing the results.
    \param size size of an array.
    */
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % MAXEL;
    }
}

void print_array(const char* name, int arr[], int size) {
    //! Prints the given array to stdout.
    /*!
    Format:
    Name of array: [1, 2, 3, 4, 5].

    \param name the name of array to be printed.
    \param arr the array to be printed.
    \param size size of an array.
    */
    printf("%s: [", name);

    for (int i = 0; i < size - 1; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[size - 1]);
}

void seq_scan(int arr[], int res[], int size) {
    //! Sequential scan for comparing the results.
    /*!
    \param arr the original array.
    \param res an empty array wor writing the results.
    \param size size of the original array.
    */
    res[0] = 0;

    for (int i = 0; i < size; ++i) {
        res[i + 1] = res[i] + arr[i];
    }
}

void naive_parallel_scan(int arr[], int res[], int n) {
    //! Naive parallel scan.
    for (int i = 0; i < n; ++i) {
        res[i] = arr[i];
    }

    for (int d = 1; d <= log2(n); ++d) {
        for (int k = 1; k < n; ++k) {
            if (k >= pow(2, d)) {
                res[k] += res[k - (int) pow(2, d-1)];
            }
        }
    }
}

void work_effic_parallel_scan(int arr[], int res[], int size) {
    //! Work-efficient parallel scan.

}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int n = atoi(argv[1]);

    int arr[n];
    int pref[n + 1];

    random_array(arr, n);
    print_array("Original array", arr, n);

    seq_scan(arr, pref, n);
    print_array("Sequential scan", pref, n + 1);

    naive_parallel_scan(arr, pref, n);
    print_array("Naive parallel scan", pref, n + 1);
}