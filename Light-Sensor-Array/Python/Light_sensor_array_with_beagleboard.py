# program to get the serial data from BB-XM
# use this file to collect data

import serial
import time
import re

# make sure the connection names are correct 
sercom=serial.Serial(port=’/dev/ttyUSB0’,baudrate=115200,parity=serial.PARITY_NONE,stopbits=se # NOT SURE IF THERE IS MORE HERE.. 
                                                                                               # CUT-OFF IN FIRAT'S DISSERTATION
sercom.open()
sercom.isOpen()

# make sure to change the filename to correspond to the test coordinate
f=open('single arduino.txt’,’w’)

while True:
# bytesToRead = sercom.inWaiting()
   x=sercom.readline()
   f.write(time.ctime()+’,’+x)
   f.flush()

# print time.ctime()+’,’+x

f.close()
