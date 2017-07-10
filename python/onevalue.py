#!/usr/bin/env python
from utils import find_kmax, find_fmax
import numpy as np
import matplotlib.pyplot as plt
import yaml


if __name__ == "__main__":
    with open("fk.yaml", "r") as f:
        config = yaml.load(f)
        num_show = int(config["num_show"])
        file_f = config["file_f"]
        file_k = config["file_k"]
        file_data = config["infile"]
        file_disper = config["outfile"]

    disper = np.loadtxt(file_disper)
    data = np.loadtxt(file_data)
    f = np.loadtxt(file_f)
    k = np.loadtxt(file_k)
    # fk_max = find_kmax(disper, data, num_show)
    fk_max = find_fmax(disper, data, num_show)

    x = []
    for key, value in fk_max.items():
        nf = value[:, 0]
        nk = value[:, 1]
        c = 2*np.pi*f[nf] / k[nk] / 1000
        # plt.plot(f[nf], c, '.', label=str(key))
        plt.plot(k[nk]*1000, f[nf], '.', label=str(key))
        if key == 0:
            mode = 1 #2
        elif key == 1:
            mode = 2 #1
        elif key == 2:
            mode = 2 #3
        elif key == 3:
            mode = 4
        elif key == 4:
            mode =5
        for ind_f, ind_k in zip(nf, nk):
            x.append([f[ind_f], k[ind_k]*1000, mode])
        # for ind_f, ind_c in zip(nf, range(len(c))):
            # x.append([f[ind_f], c[ind_c], mode])


    x = np.array(x)
    x = x[x[:, 0].argsort()]
    with open("data.txt", "w") as f:
        for line in x:
            f.write("{:18.12f}{:18.12f}{:5d}\n".format(line[0],
                                                       line[1],
                                                       int(line[2])))
    # plt.ylim([0.15, 0.6])
    # plt.xlim([0, 25])
    # plt.ylim([0.08, 0.4])
    # plt.xlim([0, 25])
    plt.xlim([0, 1000])
    plt.ylim([0, 25])
    plt.legend()
    plt.gca().invert_yaxis()
    plt.show()
