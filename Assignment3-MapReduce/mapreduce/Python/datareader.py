import pandas as pd


def read(file):
    """Reads an array from file"""
    df = pd.read_csv(file, header=None)
    return df.values.flatten()