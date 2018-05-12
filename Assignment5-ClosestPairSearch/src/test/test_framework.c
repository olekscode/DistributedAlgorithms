#include "test_framework.h"

static unsigned num_passed = 0;

void run(TEST test)
{
    TestResult res = test();
    char* color;

    if (res.passed) {
        color = GREEN;
        ++num_passed;
    }
    else {
        color = RED;
    }

    printf("\t--> %s%s%s\n", color, res.name, ESCAPE);
}

void run_all(TEST** tests, int num_tests)
{
    printf("Running %d tests\n\n", num_tests);

    for (int i = 0; i < num_tests; ++i) {
        run(tests[i]);
    }

    printf("\n%d tests executed: %d passed, %d failed\n",
        num_tests, num_passed, num_tests - num_passed);
}