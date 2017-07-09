#!/usr/bin/env python

from utils import readfile
import numpy as np
import matplotlib.pyplot as plt
import sys
import yaml

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
    with open("fk.yaml", "r") as f:
        config = yaml.load(f)
        num_show = int(config["num_show"])
        file_f = config["file_f"]
        file_k = config["file_k"]
        file_data = config["infile"]
        file_disper = config["outfile"]
        type_value = config['type']
    
    disper = np.loadtxt(file_disper)
    data = np.loadtxt(file_data)
    f = np.loadtxt(file_f)
    k = np.loadtxt(file_k)

    area = []
    for i in range(disper.shape[0]):
        area.append(abs(data[int(disper[i, 1]), int(disper[i, 2])]*20))
    co = [colors[int(i)] for i in disper[:, 0]]
    nco = locate_color(disper[:, 0])
    nco.append(len(co))

    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)

    # plt.scatter(x[:, 2], x[:, 1], area, c=co,
    #             alpha=0.5, edgecolors='face')
    for i in range(len(nco)-1):
        fp = f[disper[nco[i]:nco[i+1], 1].astype(int)]
        kp = k[disper[nco[i]:nco[i+1], 2].astype(int)]
        cp = 2 * np.pi * fp / kp
        if type_value == "k":
            ax.scatter(kp, fp, area, c=co[nco[i]], alpha=0.5,
                       edgecolors='face', label=str(i))
        elif type_value == "c":
            ax.scatter(fp, cp, area, c=co[nco[i]], alpha=0.5,
                       edgecolors='face', label=str(i))
    ax.legend()
    if type_value == "k":
        plt.gca().invert_yaxis()

    plt.show()
