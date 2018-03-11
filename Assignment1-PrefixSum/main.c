/* Hints:
* If you have 4 cores - create 4 processes, not 100
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "scan.h"

#define MAXCORES 4


void random_array(int arr[], int size)
{
    //! Initializes an array with random elements from 0 to MAXEL.
    /*!
    \param arr an empty array for writing the results.
    \param size size of an array.
    */
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % size;
    }
}

void print_array(int arr[], int size)
{
    //! Prints the given array to stdout.
    /*!
    Format:
    [1, 2, 3, 4, 5].

    \param arr the array to be printed.
    \param size size of an array.
    */
    printf("[");

    for (int i = 0; i < size - 1; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[size - 1]);
}

void perform(void (*func)(int*, int*, int), int arr[], int pref[], int n)
{
    clock_t start = clock();
    func(arr, pref, n);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;\

    printf("Seconds: %f\n", seconds);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("ERROR: %s\n",
            "You must provide the number of elements as an argument.");
        return 1;
    }

    srand(time(NULL));

    int n = atoi(argv[1]);

    int arr[n];
    int pref[n];

    random_array(arr, n);
    printf("Original array\n");
    print_array(arr, n);
    printf("\n");

    perform(seq_scan, arr, pref, n);
    perform(naive_parallel_scan, arr, pref, n);
    perform(work_effic_parallel_scan, arr, pref, n);
}