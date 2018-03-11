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

#include "math_extension.h"

void seq_scan(int arr[], int res[], int size);
void naive_parallel_scan(int arr[], int out[], int n);
void up_sweep_phase(int res[], int n);
void down_sweep_phase(int res[], int n);
void work_effic_parallel_scan(int arr[], int res[], int size);