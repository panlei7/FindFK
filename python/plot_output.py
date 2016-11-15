#!/usr/bin/env python

from utils import readfile
import numpy as np
import matplotlib.pyplot as plt

colors = ['b',
          'g',
          'r',
          'c',
          'm',
          'y',
          'k']

if __name__ == "__main__":
    y = readfile("test_data.txt")
    x = readfile("output.txt")

    plt.figure()
    # for i in range(x.shape[0]):
    #     area = y[int(x[i, 1]), int(x[i, 2])]*20
    #     # plt.plot(x[i, 2], x[i, 1], 'o', c=colors[int(x[i, 0])])
    #     plt.scatter(x[i, 2], x[i, 1], area, c=colors[int(x[i, 0])],
    #                 alpha=0.3, edgecolors='face')
    area = []
    for i in range(x.shape[0]):
        area.append(abs(y[int(x[i, 1]), int(x[i, 2])]*20))
    co = [colors[int(i)] for i in x[:, 0]]
    # plt.scatter(x[:, 2], x[:, 1], 20, c=co,
    #             alpha=0.5, edgecolors='face')
    plt.scatter(x[:, 1], x[:, 2], area, c=co,
                alpha=0.5, edgecolors='face')
    # plt.gca().invert_yaxis()
    plt.show()
