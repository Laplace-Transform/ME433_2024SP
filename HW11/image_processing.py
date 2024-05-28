from PIL import Image
import numpy as np
img_data = Image.open("C:/Users/59201/Desktop/NU/2024 Spring/ME433/ME433_2024SP_Homeworks/HW11/test.jpg")
img_data = img_data.convert('RGB')


import matplotlib.pyplot as plt
width, height = img_data.size
print(str(width)+" "+str(height))

index = []
sum = []
index_high = []

for i in range(width):
    r, g, b = img_data.getpixel((i, 45))
    index.append(i)

    sum.append(r+g+b)
    
for i in range(width):
    if sum[i] >= (min(sum)+max(sum))/2:
        index_high.append(i)

print((min(sum)+max(sum))/2)

print(np.average(index_high))
print(np.average(index_high)/width)

img_data.show()
plt.plot(index,sum,'k-')
plt.show()