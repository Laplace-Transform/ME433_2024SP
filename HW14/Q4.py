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
    print(Fs)
    return abs(Y),frq

t = [] # column 0
data1 = [] # column 1


with open('C:/Users/59201/Desktop/NU/2024 Spring/ME433/ME433_2024SP_Homeworks/HW14/sigD.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
            # read the rows 1 one by one
            t.append(float(row[0])) # leftmost column
            data1.append(float(row[1])) # second column



[Y,freqency] = myfft(data1,t)


fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,data1,'black')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(freqency,Y,'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()