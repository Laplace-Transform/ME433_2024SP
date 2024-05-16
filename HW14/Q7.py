import matplotlib.pyplot as plt
import numpy as np
import csv

h = [
    0.029183359514055443,
    0.029779744780144553,
    0.030341314035934788,
    0.030866756254078743,
    0.031354842164334006,
    0.031804427695546707,
    0.032214457182525101,
    0.032583966327994970,
    0.032912084910572369,
    0.033198039230461426,
    0.033441154285384696,
    0.033640855670076741,
    0.033796671193517147,
    0.033908232208942304,
    0.033975274652555849,
    0.033997639787750347,
    0.033975274652555849,
    0.033908232208942304,
    0.033796671193517147,
    0.033640855670076741,
    0.033441154285384696,
    0.033198039230461426,
    0.032912084910572369,
    0.032583966327994970,
    0.032214457182525101,
    0.031804427695546707,
    0.031354842164334006,
    0.030866756254078743,
    0.030341314035934788,
    0.029779744780144553,
    0.029183359514055443,
]


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

def myFIR(data,coef):
    window_size = len(coef)-1
    FIRdata = np.zeros(window_size)

    for i in range(len(data)):
        window = np.append(FIRdata[-window_size:],data[i])

        average = np.sum(np.multiply(window,coef))
        FIRdata = np.append([FIRdata],[average])
    
    print(FIRdata)
    return FIRdata[window_size:]


t = [] # column 0
data1 = [] # column 1


with open('C:/Users/59201/Desktop/NU/2024 Spring/ME433/ME433_2024SP_Homeworks/HW14/sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
            # read the rows 1 one by one
            t.append(float(row[0])) # leftmost column
            data1.append(float(row[1])) # second column

data2 =  myFIR(data1,h)

fig, ax1 = plt.subplots(1, 1)
ax1.plot(t,data1,'black')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax1.plot(t,data2,'red')
ax1.set_title('sigA,Cutoff = 100Hz,Transition = 300Hz, method = Rectangular')


plt.show()