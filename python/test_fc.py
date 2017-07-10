import numpy as np
import matplotlib.pyplot as plt


f = np.loadtxt("f2.txt")
c = np.loadtxt("c.txt")

X = np.loadtxt("./input_fc.txt")
for x in X:
    x /= np.max(x)

myxlabels=["LabX"+str(l) for l in range(len(X[0,:]))]
myylabels=["LabY"+str(l) for l in range(len(X))]
# plt.imshow(X)
plt.pcolormesh(f, c, X.T, cmap=plt.get_cmap("jet"), vmin=0)
# plt.gca().invert_yaxis()

store = dict()
current_mode = -1
df = f[0]
dc = c[0]

def onclick(event):
    global current_mode
    if current_mode == -1:
        current_mode = 0
        store[0] = []
    print('Returned indices')
    print(event.xdata, event.ydata)
    print('mapping back:')
    f = int(np.round(event.xdata/df))
    c = int(np.round(event.ydata/dc))
    store[current_mode].append((f, c))
    # tx = "Y: {}, X: {}, Value: {:.2f}".format(myylabels[y], myxlabels[x], X[y,x])
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

plt.gcf().canvas.mpl_connect('key_press_event', press)
plt.gcf().canvas.mpl_connect('button_press_event', onclick)

plt.show()
