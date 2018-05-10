#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free

struct Point
{
    double x;
    double y;
} point;

struct Point new_point(double x, double y)
{
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

void swap_arrays(struct Point** a, struct Point** b)
{
    struct Point* tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_int(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap(struct Point** a, int* a_begin, int* a_end,
          struct Point** b, int* b_begin, int* b_end)
{
    swap_arrays(a, b);
    swap_int(a_begin, b_begin);
    swap_int(a_end, b_end);
}

int binary_search(struct Point p, struct Point* arr, int begin, int end)
{
    if (arr[begin].y > p.y) return begin;

    // TODO: Rewrite it as a binary search
    for (int i = begin + 1; i <= end; ++i) {
        if (arr[i].y > p.y) return i - 1;
    }
    return end + 1;
}

void merge(struct Point* a, int a_begin, int a_end,
           struct Point* b, int b_begin, int b_end,
           struct Point* c, int c_begin, int c_end)
{
    int m = a_end - a_begin;
    int n = b_end - b_begin;

    if (m < n) {
        // Swap a and b
        swap(&a, &a_begin, &a_end, &b, &b_begin, &b_end);

        // Swap m and n
        swap_int(&m, &n);
    }

    // Base case, nothing to merge
    if (m <= 0) return;

    printf("%d, %d, %d, %d, %d, %d\n", (int)a_begin, (int)a_end, (int)b_begin, (int)b_end, (int)c_begin, (int)c_end);

    int r = (a_begin + a_end) / 2;
    int s = binary_search(a[r], b, b_begin, b_end);
    int t = c_begin + (r - a_begin) + (s - b_begin);
    c[t] = a[r];

    merge(a, a_begin, r, b, b_begin, s, c, c_begin, t);
    merge(a, r + 1, a_end, b, s + 1, b_end, c, t + 1, c_end);
}

int main(int argc, char* argv[])
{
    int m = 2;
    int n = 3;

    struct Point* a = (struct Point*) malloc(m * sizeof(point));
    struct Point* b = (struct Point*) malloc(n * sizeof(point));
    struct Point* c = (struct Point*) malloc((m + n) * sizeof(point));    

    a[0] = new_point(0, 1);
    a[1] = new_point(0, 2);
    b[0] = new_point(0, 3);
    b[1] = new_point(0, 4);
    b[2] = new_point(0, 5);

    merge(a, 0, m - 1, b, 0, n - 1, c, 0, m + n - 1);

    // Expected: "[1, 2, 3, 4, 5]"
    printf("[%d, %d, %d, %d, %d]\n", (int)c[0].y, (int)c[1].y, (int)c[2].y, (int)c[3].y, (int)c[4].y);

    free(c);
    free(b);
    free(a);

    return 0;
}
