import socket

s = socket.socket()
port = 12460
#s.connect(('127.0.0.1',port))
#s.connect(('172.217.164.100',port))
s.connect(('mskaca.c.googlers.com',port))

s.sendall(b'Hello Server Mans')

print(s.recv(1024))
s.close


