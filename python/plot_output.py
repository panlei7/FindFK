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

def locate_color(color_array):
    n = int(np.amax(color_array))
    ret = []
    for i in range(n+1):
        ret.append(np.where(color_array==i)[0][0])
    return ret;


if __name__ == "__main__":
    inname = sys.argv[1]
    y = readfile(inname)
    outname = sys.argv[2]
    x = readfile(outname)

    area = []
    for i in range(x.shape[0]):
        area.append(abs(y[int(x[i, 1]), int(x[i, 2])]*20))
    co = [colors[int(i)] for i in x[:, 0]]
    nco = locate_color(x[:, 0])
    nco.append(len(co))

    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)

    # plt.scatter(x[:, 2], x[:, 1], area, c=co,
    #             alpha=0.5, edgecolors='face')
    for i in range(len(nco)-1):
        ax.scatter(x[nco[i]:nco[i+1], 2],
                   x[nco[i]:nco[i+1], 1], area, c=co[nco[i]],
                   alpha=0.5, edgecolors='face', label=str(i))

    ax.legend()
    plt.gca().invert_yaxis()
    plt.show()
