#!/usr/bin/env python

from utils import readfile
import numpy as np
import matplotlib.pyplot as plt
import sys

colors = ['b',
          'g',
          'r',
          'c',
          'm',
          'y',
          'k']

if __name__ == "__main__":
    fname = sys.argv[1]
    y = readfile(fname)
    x = readfile("output.txt")

    plt.figure()
    area = []
    for i in range(x.shape[0]):
        area.append(abs(y[int(x[i, 1]), int(x[i, 2])]*20))
    co = [colors[int(i)] for i in x[:, 0]]
    # plt.scatter(x[:, 2], x[:, 1], area, c=co,
    #             alpha=0.5, edgecolors='face')
    plt.scatter(x[:, 1], x[:, 2], area, c=co,
                alpha=0.5, edgecolors='face')
    # plt.gca().invert_yaxis()
    plt.show()
