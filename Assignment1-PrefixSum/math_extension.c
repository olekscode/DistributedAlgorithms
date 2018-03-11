#include "math_extension.h"


double log2(double n) {
    //! Calculates log2 of number.
    return log(n) / log(2);  
}

int ipow(int n, int p) {
    //! Calculates the power of integer.
    return (int) pow(n, p);
} 