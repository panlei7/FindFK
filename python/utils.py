import numpy as np
def readfile(filename):
    try:
        x = np.loadtxt(filename)
        return x
    except IOError as e:
        print("file doesn't exist. ", e)
        raise
