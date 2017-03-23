import numpy as np
import matplotlib.pyplot as plt
#import matplotlib.pyplot as plt2
#import matplotlib.pyplot as plt3

import os.path

plt.ion()

temp = []
hum = []
lum = []
timeStamp =[]


scriptpath = os.path.dirname(__file__)
filename = os.path.join(scriptpath, 'test.txt')

def readDataintoArray():
    with open(filename,"r") as f:
        for line in f:
            data = line.rstrip('\n').split(',')
            timeStamp.append(data[0])
            temp.append(data[1])
            hum.append(data[2])
            lum.append(data[3])
            print("updated Arrays")

def updateData():
    with open(filename,"a") as f:
        f.write(  str(abs(int(timeStamp[len(timeStamp)-1])+1)) +","+ str(abs(int(temp[len(temp)-1])+1)) +","+ str(abs(int(hum[len(hum)-1])+1)) +","+str(abs(int(lum[len(lum)-1])+1)) +"\n")
    print("updated data")

readDataintoArray()

while True:
    plt.subplot(131)
    plt.scatter(timeStamp, temp)
    plt.subplot(132)
    plt.scatter(timeStamp,hum)
    plt.subplot(133)
    plt.scatter(timeStamp,lum)
    plt.pause(0.05)
    updateData()
    readDataintoArray()

while True:
    plt.pause(0.05)
