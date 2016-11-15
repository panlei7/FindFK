#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import sys

def readfile(filename):
    try:
        x = np.loadtxt(filename)
        return x
    except IOError as e:
        print("file doesn't exist. ", e)
        raise


if __name__ == "__main__":
    x = readfile(sys.argv[1])
    nbins = min(np.size(x), 100)
    plt.hist(x.flatten(), nbins)
    plt.title("Value Histogram")
    plt.xlabel("Value")
    plt.ylabel("Frequency")
    plt.show()
