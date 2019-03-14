
##### This creates the socket SERVER #####

import socket
#import cv2
import time


##### UI STUFF GOES HERE #####################

from PyQt5.QtWidgets import QApplication, QLabel



######### TCP STUFF GOES HERE #####################

s = socket.socket()
print ('socket instance created')

# reserve PORT so that it's not in use by something else:
port = 12464

# Bind it to the port
# Note that we have not typed any IP into the IP field..... we input an empty string ... this makes server
#     listen to requests coming from other computers on network
try:
	s.bind(('', port))
except socket.error as exc:
	print ("Caught exception socket.error : %s" % exc)

print("socket binded to %s"%(port))

# make server listen to requests
s.listen(5)                # where 5 = max number of queued connections
print('socket is listening')


try:
	#establish connection with client
	c, addr = s.accept()
	c.send('Thank you for connecting')  
	print ('got connection from', addr)
except KeyboardInterrupt:
	print("No connection established. Terminating :( ")
	s.close()
	exit()

# flag for identifying if I'm waiting to send or recieve message
needToSend = 0
try:
	loop = True
	while loop:	
		# obtain sensor data
		print('trying to recv data from client')
		msgRecv = c.recv(1024)
		print("Message received from Client: %s" %msgRecv)
		needToSend = 1

		# decode sensor info 
		# store data in a file

		# change the below line to something like 
		#		01230123 or whatever that means send me more data!
		print('trying to send data to client')
		c.sendall("Get me more data!!!")
		needToSend = 0
		time.sleep(2)

except KeyboardInterrupt:
	print("Ending program")

if not needToSend:
	msgRecv = c.recv(1024)
	print("FINAL message received and IGNORED: %s" %msgRecv)

c.send('0000') # sends termination ID

# close connection
c.shutdown(2)	
c.close()
print("Terminated TCP")
# then run : telnet localhost 12356 ... in your cmd or terminal

