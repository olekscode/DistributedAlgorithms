#include "mapreduce.h"

// void mapreduce(int* arr, size_t size)
// {

// }

// void split(int* arr, size_t size, size_t num_mappers, int* documents)
// {

// }

struct Value
{
    int doc;
    int count;
};

struct Map
{
    int key;
};

void map(int* doc_begin, size_t doc_size, void(*mapper)(int*, size_t))
{
    for (int i = 0; i < doc_size; ++i) {

    }
}

void reduce(int* arr, size_t size)
{

}