"""
Simple implementation of MapReduce in Python
(c) Oleksandr Zaytsev <oleks@ucu.edu.ua>
"""

import time

import datareader
import mapreduce


FILE_NAME = 'input/numbers-small.csv'


def time_str(diff):
    hours, rem = divmod(diff, 3600)
    minutes, seconds = divmod(rem, 60)
    return '{:0>2}:{:0>2}:{:05.2f}'.format(int(hours), int(minutes), seconds)


def mapper(doc):
    """Custom mapper
    Produces a list of key-value pairs"""
    return [(val, 1) for val in doc]


def reducer(key, value):
    """Custom reducer"""
    return (key, sum(value))


if __name__ == '__main__':
    print("Reading numbers from '{}'".format(
        FILE_NAME))

    start = time.time()
    numbers = datareader.read(FILE_NAME)
    diff = time.time() - start
    print("Time to read:", time_str(diff))

    print("Read an array with {} numbers in range [{}, {}]".format(
        len(numbers), numbers.min(), numbers.max()))

    print()
    print("Starting sequential MapReduce")

    start = time.time()
    counts = mapreduce.mapreduce_sequential(numbers, 4, mapper, reducer)

    print("Result of sequential MapReduce:")
    print(counts)
    diff = time.time() - start
    print("Time to run sequential MapReduce:", time_str(diff))

    print()
    print("Starting parallel MapReduce")

    start = time.time()
    counts = mapreduce.mapreduce_parallel(numbers, 4, mapper, reducer)

    print("Result of parallel MapReduce:")
    print(counts)
    diff = time.time() - start
    print("Time to run parallel MapReduce:", time_str(diff))
