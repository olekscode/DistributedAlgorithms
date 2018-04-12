"""
Simple implementation of MapReduce in Python
(c) Oleksandr Zaytsev <oleks@ucu.edu.ua>
"""

from multiprocessing import Process, Queue
import time


def split(arr, num_mappers):
    """Splits an array into a set of documents"""
    doc_size = len(arr) // num_mappers
    return [arr[i * doc_size:(i + 1) * doc_size] for i in range(num_mappers)]


def shuffle(mapped, num_reducers):
    shuffled = {}

    for pairs in mapped:
        for pair in pairs:
            k = pair[0]
            v = pair[1]

            if k in shuffled.keys():
                shuffled[k].append(v)
            else:
                shuffled[k] = [v]

    return shuffled


def mapreduce_sequential(arr, num_mappers, mapper_func, reducer_func):
    splitted = split(arr, num_mappers)
    mapped = [mapper_func(doc) for doc in splitted]
    shuffled = shuffle(mapped, None)
    reduced = dict([reducer_func(k, v) for k, v in shuffled.items()])
    return dict(sorted(reduced.items()))


def parallel_map(doc, output, mapper_func):
    mapped = mapper_func(doc)
    output.put(mapped)


def parallel_reduce(key, value, output, reducer_func):
    reduced = reducer_func(key, value)
    output.put(reduced)


def mapreduce_parallel(arr, num_cores, mapper_func, reducer_func):
    splitted = split(arr, num_cores)
    
    output = Queue()
    processes = [
        Process(target=parallel_map, args=(doc, output, mapper_func))
        for doc in splitted]

    for p in processes:
        p.start()

    for p in processes:
        p.join()

    mapped = [output.get() for p in processes]
    shuffled = shuffle(mapped, None)

    output = Queue()
    processes = [
        Process(target=parallel_reduce, args=(key, value, output, reducer_func))
        for key, value in shuffled.items()]

    for p in processes:
        p.start()

    for p in processes:
        p.join()

    return dict(sorted([output.get() for p in processes]))
