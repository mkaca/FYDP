#!/usr/bin/python
import serial
import time

#The following line is for serial over GPIO
#port = '/dev/ttyACM0'  # change this depending on port   # LINUX
port = 'COM9'    # WINDOWS
 

ser = serial.Serial(port,57600,timeout=5)
time.sleep(2) # wait for Arduino

i = 0

while (i < 100):
    # Serial write section

    setTempCar1 = 63
    ser.flush()
    setTemp1 = str(setTempCar1)
    print ("Python value sent: ")
    print (setTemp1)
    ser.write(str.encode(setTemp1))
    time.sleep(0.07) # 70 ms to ensure all bytes are sent

    # Serial read section
    print('waity boys',ser.inWaiting())
    msg = ser.read(ser.inWaiting()) # read all characters in buffer
    print ("Message from arduino: ")
    print (msg)
    print (' ')
    i = i + 1
else:
    print ("Exiting")
exit()

################ TO DOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO ######################## : MODIFY VALUES TO DECREASE TEST TIME...
## THEN ADD IMU AND SEE HOW FAST YOU TRANSMIT DATA