#!/usr/bin/env python
from utils import readfile
import matplotlib.pyplot as plt
import numpy as np
import sys

if __name__ == "__main__":
    x = readfile(sys.argv[1])
    nbins = min(np.size(x), 100)
    plt.figure()
    plt.subplot(211)
    plt.hist(x.flatten(), nbins)
    plt.title("Value Histogram")
    plt.xlabel("Value")
    plt.ylabel("Frequency")
    plt.subplot(212)
    ind1d = np.argsort(-x, axis=None)[:2000]
    ind2d = np.unravel_index(ind1d, x.shape)
    plt.plot(ind2d[1], ind2d[0], 'o')
    plt.gca().invert_yaxis()
    plt.show()
