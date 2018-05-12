#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>           // printf

#define GREEN "\033[38;5;2m"
#define RED "\033[38;5;1m"
#define ESCAPE "\033[0m"

typedef struct {
    int passed;
    char* name;
} TestResult;

// Function pointer
typedef TestResult TEST();

void run(TEST test);
void run_all(TEST** tests, int num_tests);

#endif // TEST_FRAMEWORK_H