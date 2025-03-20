## this transmits 23 characters in uart from a buffer directory

import serial
import datetime

ser = serial.Serial('/dev/ttyUSB0', 9600)  # open serial port
lastUpdate = datetime.datetime.now() - datetime.timedelta(seconds = 60)  # initialize lastUpdate and make 
                                                                       # the first ser.write now  

while True:
    if (datetime.datetime.now() - lastUpdate).seconds >= 60:
        with open("buffer.txt", "r") as buffer:
            message = buffer.read()
        message = bytes(message,'utf-8')
        ser.write(message)     # write a string
        #ser.close()             # close port             ????????????
        lastUpdate = datetime.datetime.now()
