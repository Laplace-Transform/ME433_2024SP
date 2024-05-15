import matplotlib.pyplot as plt
import numpy as np
import csv


def myfft(data,time):
    
    y = data # the data to make the fft from
    n = len(y) # length of the signal
    Fs = n/time[-1] # sample rate
    k = np.arange(n)
    T = n/Fs
    frq = k/T # two sides frequency range
    frq = frq[range(int(n/2))] # one side frequency range
    Y = np.fft.fft(y)/n # fft computing and normalization
    Y = Y[range(int(n/2))]

    return abs(Y),frq


def mymaf(data,window_size):
    mafdata = []
    for i in range(len(data) - window_size + 1):
        window = data[i:i + window_size]
        average = sum(window) / window_size
        mafdata = np.append([mafdata],[average])
    mafdata = np.append(np.zeros(window_size-1),[mafdata])
    return mafdata


t = [] # column 0
data1 = [] # column 1


with open('C:/Users/59201/Desktop/NU/2024 Spring/ME433/ME433_2024SP_Homeworks/HW14/sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
            # read the rows 1 one by one
            t.append(float(row[0])) # leftmost column
            data1.append(float(row[1])) # second column

window_size=2
data2 = mymaf(data1,window_size)


fig, ax1 = plt.subplots(1, 1)
ax1.plot(t,data1,'black')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax1.plot(t,data2,'red')
ax1.set_title('sigA,window_size=%d' % window_size)

plt.show()