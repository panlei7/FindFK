import numpy as np
import matplotlib.pyplot as plt

store = dict()
current_mode = -1

f = np.loadtxt("f1.txt")
k = np.loadtxt("k1.txt")

X = np.loadtxt("./input_fk.txt")
for x in X:
    x /= np.max(x)

def onclick(event):
    global current_mode
    if current_mode == -1:
        current_mode = 0
        store[0] = []
    print('Returned indices')
    print(event.xdata, event.ydata)
    print('mapping back:')
    nk = np.where(k > event.xdata)[0][0]
    nf = np.where(f > event.ydata)[0][0]
    store[current_mode].append([nf, nk])
    print(store)


def press(event):
    global current_mode
    if event.key == "0":
        current_mode = 0
        if 0 not in store:
            store[0] = []
    elif event.key == "1":
        current_mode = 1
        if 1 not in store:
            store[1] = []
    elif event.key == "2":
        current_mode = 2
        if 2 not in store:
            store[2] = []
    elif event.key == "3":
        current_mode = 3
        if 3 not in store:
            store[3] = []
    elif event.key == "4":
        current_mode = 4
        if 4 not in store:
            store[4] = []
    elif event.key == "5":
        current_mode = 5
        if 5 not in store:
            store[5] = []
    elif event.key == "6":
        current_mode = 6
        if 6 not in store:
            store[6] = []
    elif event.key == "backspace":
        if store[current_mode]:
            store[current_mode].pop()
        print(store)

if __name__ == "__main__":

    myxlabels = ["LabX"+str(l) for l in range(len(X[0, :]))]
    myylabels = ["LabY"+str(l) for l in range(len(X))]
    # plt.imshow(X)
    plt.pcolormesh(k, f, X, cmap=plt.get_cmap("jet"), vmin=0)
    plt.gca().invert_yaxis()

    plt.gcf().canvas.mpl_connect('key_press_event', press)
    plt.gcf().canvas.mpl_connect('button_press_event', onclick)

    plt.show()
    with open("data.txt", "w") as stream:
        for key, value in store.items():
            for nf, nk in value:
                stream.write("{:14.7e}{:14.7e}{:5d}\n".format(f[nf], k[nk], key+1))

