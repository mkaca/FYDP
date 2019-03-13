import threading
import time
from PyQt5.QtWidgets import *

exitFlag = 0
actionCode = 0

class myThreadPrint (threading.Thread):
   def __init__(self, threadID, name, counter):
      threading.Thread.__init__(self)
      self.threadID = threadID
      self.name = name
      self.counter = counter
   def run(self):
      print ("Starting " + self.name)
      print_time(self.name, 5, self.counter)
      print ("Exiting " + self.name)

# Don't actually need this since one is supposed to run pyQt as main thread!!!!
class myThreadUI (threading.Thread):
   def __init__(self, threadID, name, actionParam):
      threading.Thread.__init__(self)
      self.threadID = threadID
      self.name = name
      self.actionParam = actionParam
   def run(self):
      print ("Starting " + self.name)
      createUI(self.actionParam)
      print ("Exiting " + self.name)

def print_time(threadName, counter, delay):
   while counter:
      if exitFlag:
         threadName.exit()
      time.sleep(delay)
      print ("%s: %s" % (threadName, time.ctime(time.time())))
      counter -= 1


######################################################

class myThreadTCP (threading.Thread):
   def __init__(self, threadID, name, actionParam):
      threading.Thread.__init__(self)
      self.threadID = threadID
      self.name = name
      self.actionParam = actionParam
   def run(self):
      print ("Starting " + self.name)
      createUI(self.actionParam)
      print ("Exiting " + self.name)




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






###################################################


def createUI(actionParam):
	app = QApplication([])
	app.setStyle('Fusion')
	window = QWidget()
	window.resize(800,800)
	window.setWindowTitle("Robot Control")
	layout = QGridLayout()
	app.setStyleSheet("QPushButton { margin: 5ex; }")

	actionCode = 0

	buttonF = QPushButton('Forward')
	buttonRv = QPushButton('Reverse')
	buttonL = QPushButton('Left')
	buttonR = QPushButton('Right')
	buttonCW = QPushButton('Turn CW')
	buttonCCW = QPushButton('Turn CCW')
	buttonS = QPushButton('STOP')

	buttonF.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
	buttonRv.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
	buttonL.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
	buttonR.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
	buttonCW.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
	buttonCCW.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
	buttonS.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)

	buttonF.setStyleSheet('QPushButton {background-color: #A3C1DA; color: purple;}')
	buttonRv.setStyleSheet('QPushButton {background-color: #A3C1DA; color: purple;}')
	buttonL.setStyleSheet('QPushButton {background-color: #A3C1DA; color: purple;}')
	buttonR.setStyleSheet('QPushButton {background-color: #A3C1DA; color: purple;}')
	buttonCW.setStyleSheet('QPushButton {background-color: #D7C4DA; color: purple;}')
	buttonCCW.setStyleSheet('QPushButton {background-color: #D7C4DA; color: purple;}')
	buttonS.setStyleSheet('QPushButton {background-color: #B22222; color: white; }')

	font = buttonF.font()
	font.setPointSize(24)
	buttonF.setFont(font)
	buttonRv.setFont(font)
	buttonL.setFont(font)
	buttonR.setFont(font)
	buttonS.setFont(font)
	buttonCCW.setFont(font)
	buttonCW.setFont(font)

	def on_forward_button_clicked():
	    actionParam = 1
	    print (actionParam)
	def on_reverse_button_clicked():
	    actionParam = 2
	def on_left_button_clicked():
	    actionParam = 3
	def on_right_button_clicked():
	    actionParam = 4
	    print (actionParam)
	def on_CW_button_clicked():
	    actionParam = 5
	def on_CCW_button_clicked():
	    actionParam = 6
	def on_stop_button_clicked():
	    actionParam = 0

	buttonF.clicked.connect(on_forward_button_clicked)
	buttonRv.clicked.connect(on_reverse_button_clicked)
	buttonL.clicked.connect(on_left_button_clicked)
	buttonR.clicked.connect(on_right_button_clicked)
	buttonCW.clicked.connect(on_CW_button_clicked)
	buttonCCW.clicked.connect(on_CCW_button_clicked)
	buttonS.clicked.connect(on_stop_button_clicked)

	layout.setRowMinimumHeight(3,100)

	layout.addWidget(buttonF,1,3)
	layout.addWidget(buttonRv,3,3)
	layout.addWidget(buttonL,2,1)
	layout.addWidget(buttonR,2,5)
	layout.addWidget(buttonCW,0,1)
	layout.addWidget(buttonCCW,0,5)
	layout.addWidget(buttonS,2,3)

	window.setLayout(layout)
	window.show()
	app.exec_()


# Create new threads
thread1 = myThreadPrint(1, "Thread-1", 1)
thread2 = myThreadPrint(2, "Thread-2", 2)

thread3 = myThreadUI(3, "THread-2UI", actionCode)

# Start new Threads
thread1.start()
thread2.start()
#thread3.start()

createUI(actionCode)

print ("Exiting Main Thread")