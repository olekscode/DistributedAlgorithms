"""
Generating an array of numbers in given range for MapReduce.
(c) Oleksandr Zaytsev <oleks@ucu.edu.ua>
"""

import numpy as np
import pandas as pd
import csv
import time

FILE_NAME = 'input/numbers.csv'
SIZE = 2 ** 22
RANGE_FROM = 0
RANGE_TO = 9


def generate(size, a, b):
    """Generates an array of rangom numbers in range [a, b]"""
    return np.random.randint(a, b + 1, (1, size))


def write(arr, file):
    """Writes the generated array to a file"""
    df = pd.DataFrame(arr)
    df.to_csv(file, index=False, header=False)


def time_str(diff):
    """Creates a readable time string"""
    hours, rem = divmod(diff, 3600)
    minutes, seconds = divmod(rem, 60)
    return '{:0>2}:{:0>2}:{:05.2f}'.format(int(hours), int(minutes), seconds)


if __name__ == '__main__':
    print("Generating array with {} numbers in range [{}, {}]".format(
        SIZE, RANGE_FROM, RANGE_TO))

    start = time.time()
    numbers = generate(SIZE, RANGE_FROM, RANGE_TO)
    diff = time.time() - start
    print("Time to generate:", time_str(diff))

    print("Writing the generated numbers into '{}'".format(
        FILE_NAME))

    start = time.time()
    write(numbers, FILE_NAME)
    diff = time.time() - start
    print("Time to write:", time_str(diff))
