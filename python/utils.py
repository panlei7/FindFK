import numpy as np


def readfile(filename):
    try:
        x = np.loadtxt(filename)
        return x
    except IOError as e:
        print("file doesn't exist. ", e)
        raise


def find_kmax(disper, data, num_show):
    """find kmax for the same frequency"""

    fk_max = dict()
    for imode in range(num_show):
        idx = np.where(disper[:, 0] == imode)
        x_i = disper[idx]
        k0 = int(x_i[0, 2])
        f0 = int(x_i[0, 1])
        k_samef = dict()
        k_samef[f0] = [[k0, data[f0, k0]], ]
        for m in range(1, len(x_i)):
            k1 = int(x_i[m, 2])
            f1 = int(x_i[m, 1])
            if f1 == f0:
                k_samef[f0].append([k1, data[f1, k1]])
            else:
                k0 = k1
                f0 = f1
                k_samef[f0] = [[k1, data[f1, k1]],]

        list_max = []
        for key, value in k_samef.items():
            arr = np.array(value)
            nk_max = np.argmax(arr, axis=0)[1]
            k_max = value[nk_max][0]
            list_max.append([key, k_max])
        fk_max[imode] = np.array(list_max)
    return fk_max


def find_fmax(disper, data, num_show):
    """find fmax for the same wavenumber"""

    fkmax = dict()
    for imode in range(num_show):
        idx = np.where(disper[:, 0] == imode)
        x_i = disper[idx]
        kmin = int(min(x_i[:, 2]))
        kmax = int(max(x_i[:, 2]))
        f_samek = []
        for k in range(kmin, kmax+1):
            idx2 = np.where(x_i[:, 2] == k)
            nf = x_i[idx2, 1][0]
            fmax_data = np.argmax(data[nf.astype(int), k])
            f_samek.append([int(nf[fmax_data]), k])

        fkmax[imode] = np.array(f_samek)

    return fkmax
