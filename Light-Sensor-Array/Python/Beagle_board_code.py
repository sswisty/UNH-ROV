# code to read serial out of arduino
import serial
import re
import time

# Note the device names. And the baud rate must match that of the arduinos/computer codes
ser = serial.Serial('/dev/ttyACM0’, baudrate = 9600)
ser2 = serial.Serial('/dev/ttyACM1’, baudrate = 9600)
pc = serial.Serial('/dev/ttyO2’, baudrate = 115200 )

while True:
    ser.write("!")
    data1=ser.readline()
    ser2.write("!")
    data2=ser2.readline()
    time.sleep(0.1)
    pc.write(data1+data2)
