#!/usr/bin/python

"""
This code is used to control the onboard PC..... 
script will run on start-up of linux machine
"""

"""
##### LOGIC: #######

Establish correct netmask and ip address of machine (if needed)

Send action message to arduino via Serial
Wait for arduino to send message (with data) via Serial
Send data to remote PC via TCP 
Wait for action from remote PC via TCP

"""

import serial
import time
import socket
import subprocess

#initial action message : STOP motor
actionCode = 0

# TCP socket init
s = socket.socket()
tCPPort = 12476
s.settimeout(10) # increase to like 120 after testing is done

timeOutDuration = 5 # 5s for serial timeout (reading data)

# serial init
#serialPort = '/dev/ttyACM0'  # change this depending on port   # LINUX
#serialPort = 'COM9'    # WINDOWS
serialPort = '/dev/ttyACM0'
k = 0
sjoin = ''
ser = 0
commNotFound = 1

# sets our network ip address
#subprocess.call(['sudo', 'ifconfig', 'enp1s0' , '169.254.244.185', \
#   'netmask', '255.255.255.0'])

### Connect to appropriate serial port 
while commNotFound:
    try:
        serialPortBase = '/dev/ttyACM'
        serialPort = sjoin.join((serialPortBase,str(k)))
        subprocess.call(['sudo', 'chmod', '777', serialPort])
        ser = serial.Serial(serialPort,57600,timeout=5)
        commNotFound = 0
        print('found serial port')
    except serial.SerialException as serErr:
        print("port %s not found" %serialPort)
        k += 1
        if (k > 10):
            print ("NO PORT AVAILABLE!!!!")
            exit()

time.sleep(1) # wait 1s for Arduino

try:
    # try to connect
    s.connect(('169.254.244.191', tCPPort))
    print ("connected successfully")

    """
    # sync segment
    try:
        print(s.recv(1024))
    except socket.error as exc:
        s.sendall('???') # send a smart value here
    """

    #while (actionCode > 0):
    for _ in range(10):   # this part is for TESTING ONLY

        # Serial write section
        ser.flush() # flush serial to clean up pipeline

        # send action message to arduino
        ser.write(str.encode(str(actionCode)))
        print ("Python value sent to Ard: ")
        time.sleep(0.08) # wait 80 ms to ensure all bytes are sent

        # Serial read section

        # Wait for connection to become available
        #print('Waiting for Arduino Serial',ser.inWaiting())

        # read all characters in buffer and converts to a string
        msg = 0
        # ensure message lenght is not 0
        msgEmpty = 1
        startTime = time.time()
        while msgEmpty and time.time()-startTime < timeOutDuration:
            msg = ser.read(ser.inWaiting())
            if (len(msg) == 0):
                print("message empty")
            else:
                print("message not empty YAY")
                msgEmpty = 0
            time.sleep(0.1)

        msg = str.decode(msg)
        #msg = str(2222124532111122221154311112222914839521111) 
        msg = str(msg)

        print ("Message from arduino: ")
        print (msg)
        print (' ')

        # Sends data via tCP to remote PC
        print ("Trying to send data to remote PC")
        s.sendall(msg)
        time.sleep(0.05)

        # receives data from TCP
        print ("Trying to receive data from remote PC")
        recvdMessg = s.recv(1024) # type = string
        time.sleep(0.05)
        print (recvdMessg)
        if len(recvdMessg) < 5:
            global actionCode
            actionCode = recvdMessg
        print ("Message received: %s" %actionCode)

        # Check for termination code
        if (str(actionCode) == ("-1")):
            print ("received termination code")
            ser.flush()
            ser.write(str.encode(str(actionCode)))
            break

        time.sleep(0.001) # waits 1 ms

except socket.error as exc:
    print("SOcket error ignored: %s" % exc)


# exits code (upon condition... so if actionCode is -1 (from remote PC))
#   or if TCP times out for whatever reason
s.shutdown(2)
s.close() # close socket
print ("Socket successfully shut down")

print ("Exiting")
exit()

