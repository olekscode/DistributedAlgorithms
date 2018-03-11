#include "scan.h"


void swap_arrays(int** a, int** b) {
    int* temp = *a;
    *a = *b;
    *b = temp;
}

void seq_scan(int arr[], int res[], int size) {
    //! Sequential scan for comparing the results.
    /*!
    \param arr the original array.
    \param res an empty array wor writing the results.
    \param size size of the original array.
    */
    res[0] = arr[0];

    for (int i = 1; i < size; ++i) {
        res[i] = res[i - 1] + arr[i];
    }
}

void naive_parallel_scan(int arr[], int out[], int n) {
    //! Naive parallel scan.

    int* in = arr;

    for (int d = 0; d < log2(n); ++d) {
        for (int k = 0; k < n; ++k) {
            if (k >= ipow(2, d)) {
                out[k] = in[k] + in[k - ipow(2, d)];
            }
            else {
                out[k] = in[k];
            }
        }
        swap_arrays(&in, &out);
    }
}

void up_sweep_phase(int res[], int n) {
    for (int d = 0; d < log2(n) - 1; ++d) {
        for (int k = 0; k < n; k += ipow(2, d + 1)) {
            res[k + ipow(2, d + 1) - 1] += res[k + ipow(2, d) - 1];
        }
    }
}

void down_sweep_phase(int res[], int n) {
    res[n - 1] = 0;
    int t;

    for (int d = log2(n) - 1; d >= 0; --d) {
        for (int k = 0; k < n; k += ipow(2, d) + 1) {
            t = res[k + ipow(2, d) - 1];
            res[k + ipow(2, d) - 1] = res[k + ipow(2, d + 1) - 1];
            res[k + ipow(2, d + 1) - 1] += t;
        }
    }
}

void work_effic_parallel_scan(int arr[], int res[], int size) {
    //! Work-efficient parallel scan.
    res[0] = 0;

    for (int i = 1; i < size; ++i) {
        res[i] = arr[i - 1];
    }

    up_sweep_phase(res, size);
    down_sweep_phase(res, size);
}