import csv
import matplotlib.pyplot as plt # for plotting
import numpy as np # for sine function

t = [] # column 0
data1 = [] # column 1


with open('C:/Users/59201/Desktop/NU/2024 Spring/ME433/ME433_2024SP_Homeworks/HW14/sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
            # read the rows 1 one by one
            t.append(float(row[0])) # leftmost column
            data1.append(float(row[1])) # second column

plt.plot(t,data1)
plt.xlabel('Time [s]')
plt.ylabel('Signal')
plt.title('Signal vs Time')
plt.show()
