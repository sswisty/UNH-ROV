# LIGHT SENSORY ARRAY DATA COLLECTION
# Code initallly developed by Firat Eren for PhD thesis
# Implemented by Shawn Swist

# This code is meant to read the values from 25 photodiodes in order to determine
# the position relative to a light source.

import serial
import time
import re

# Check the connection names of the two arduinos
# **if the name is not known type "ls /dev/tty.*" into the terminal **
# ** or look in the arduino sketch port. This should be in quotes **
# The baudrate must also match that of the arduino sketch

arduino1 = serial.Serial('/dev/cu.usbmodemfa130000.1', baudrate = 9600)
arduino2 = serial.Serial('/dev/cu.usbmodemfd120000.1',baudrate = 9600)

# We want to save the data into a .txt file for the matlab code to process

name = raw_input('What do you want to save the data as?  ')+'.txt'

f = open(name,'w')

while True:
    # The data collection will happen until we close the sketch

    # Read data from arduinos 1 and 2 (the ! helps with the arduino communication)
    arduino1.write("!")
    data1 = arduino1.readline()
    
    arduino2.write("!")
    data2 = arduino2.readline()

    time.sleep(0.1)

    alldata = data1+data2

    #f.write(time.ctime()+','+alldata) # This was the code Firat used..
    f.write(alldata)                   # However I am going to eliminate the time
                                       # This will make it easier to read the
                                       # data in Matlab
    f.flush()

f.close
    
