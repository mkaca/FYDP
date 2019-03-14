
##### This creates the socket SERVER #####

import socket

s = socket.socket()
print ('socket instance created')

# reserve PORT so that it's not in use by something else:
port = 12459

# Bind it to the port
# Note that we have not typed any IP into the IP field..... we input an empty string ... this makes server
#     listen to requests coming from other computers on network
s.bind(('', port))
print("socket binded to %s"%(port))

# make server listen to requests
s.listen(5)                # where 5 = max number of queued connections
print('socket is listening')

#loops forever until we close socket or interrupt it
#while True:
loop = True
while loop:
	#establish connection with client
	c, addr = s.accept()
	print ('got connection from', addr)

	#send a response to the client and then close
	c.send('Thank you for connecting')
	c.close()
	# then run : telnet localhost 12356 ... in your cmd or terminal
