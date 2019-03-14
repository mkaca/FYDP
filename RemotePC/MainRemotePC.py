
from threading import Thread
from queue import Queue
import time
from PyQt5.QtWidgets import *
import socket

# action to send
actionCode = 0
# Message received from on-board PC
msgRecv = 0

# seconds before TCP times out
timeOut = 10

s = socket.socket()
s.settimeout(timeOut)
print ('global socket instance created')

# reserve PORT so that it's not in use by something else:
port = 12474

######################################################

## Function for decoding string message!!
### Also writes data to a textfile !!!!!!!
#The input to this function will be the encoded data... for example:
#decode("000011123111100001245611110000137891111000014987111100002112111110000222321111000023454111100003156511110000916761111")
# ###
#       FORMAT: 0000XXYYYYY1111, where XX is address, and YYYYYY is data
####
def decode(encoded):

    # divide into segments
    decode =  encoded.split("0000")

    # For storing data in file
    file = open("TestData.txt", "a")
    
    i=0

    while i<len(decode):
        
        if decode[i].startswith('11'):
            result = decode[i]
            end = len(result)
            tc1 = result[2:end-4]
            file.write(str(tc1) + ", ")
            print ("Thermocouple 1: " + tc1)
            
        if decode[i].startswith('12'):
            result = decode[i]
            end = len(result)
            tc2 = result[2:end-4]
            file.write(str(tc2) + ", ")
            print ("Thermocouple 2: " + tc2)  
        
        if decode[i].startswith('13'):
            result = decode[i]
            end = len(result)
            tc3 = result[2:end-4]
            file.write(str(tc3) + ", ")
            print ("Thermocouple 3: " + tc3)
            
        if decode[i].startswith('14'):
            result = decode[i]
            end = len(result)
            tc4 = result[2:end-4]
            file.write(str(tc4) + ", ")
            print ("Thermocouple 4: " + tc4)  
    
        if decode[i].startswith('21'):
            result = decode[i]
            end = len(result)
            O2 = result[2:end-4]
            file.write(str(O2) + ", ")
            print ("O2: " + O2)  
  
        if decode[i].startswith('22'):
            result = decode[i]
            end = len(result)
            CO = result[2:end-4]
            file.write(str(CO) + ", ")
            print ("CO: " + CO)  
            
        if decode[i].startswith('23'):
            result = decode[i]
            end = len(result)
            CO2 = result[2:end-4]
            file.write(str(CO2) + ", ")
            print ("CO2: " + CO2)              
            
        if decode[i].startswith('31'):
            result = decode[i]
            end = len(result)
            posX = result[2:end-4]
            file.write(str(posX) + ", ")
            print ("PositionX: " + posX)

        if decode[i].startswith('32'):
            result = decode[i]
            end = len(result)
            posY = result[2:end-4]
            file.write(str(posY) + ", ")
            print ("PositionY: " + posY)

        if decode[i].startswith('33'):
            result = decode[i]
            end = len(result)
            posYaw = result[2:end-4]
            file.write(str(posYaw) + ", ")
            print ("PositionYaw: " + posYaw)
            
        if decode[i].startswith('91'):
            result = decode[i]
            end = len(result)
            timeStamp = result[2:end-4]
            file.write(str(timeStamp) + ", " + "\n")
            print ("Time: " + timeStamp)    
        
        i+=1
    file.close()
    
    return;


# main thread for controlling TCP comms
def threadTCP(threadname, q, port):
    global actionCode
    global msgRecv
    print("threadTCP: ", actionCode)
    # Bind it to the port
    # Note that we have not typed any IP into the IP field..... we input an empty string ...
    #     this makes server listen to requests coming from other computers on network
    try:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # to prevent binding
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

            #### decode message and save to file
            decode(msgRecv)
            
            print('trying to send data to client')
            c.sendall(str(actionCode))
            needToSend = 0
            time.sleep(0.2)
            # kill socket if UI is killed
            if (actionCode == -1):
                break

    except KeyboardInterrupt:
        print("Ending program")

    if not needToSend:
        msgRecv = c.recv(1024)
        print("FINAL message received and IGNORED: %s" %msgRecv)

    c.send('9') # sends termination ID

    # close connection
    c.shutdown(2)   
    c.close()
    print("Terminated TCP")

###################################################

### Main Thread controlling UI ############

def threadUI(threadname, q):
        print ("Starting thread4")
        global actionCode
        app = QApplication([])
        app.setStyle('Fusion')
        window = QWidget()
        window.resize(800,800)
        window.setWindowTitle("Robot Control")
        layout = QGridLayout()
        app.setStyleSheet("QPushButton { margin: 5ex; }")

        #actionCode = 0

        buttonF = QPushButton('Forward')
        buttonRv = QPushButton('Reverse')
        buttonL = QPushButton('Left')
        buttonR = QPushButton('Right')
        buttonCW = QPushButton('Turn CW')
        buttonCCW = QPushButton('Turn CCW')
        buttonS = QPushButton('STOP')
        buttonTerminate = QPushButton('TERMINATE')

        buttonF.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
        buttonRv.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
        buttonL.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
        buttonR.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
        buttonCW.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
        buttonCCW.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
        buttonS.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)
        buttonTerminate.setSizePolicy(QSizePolicy.Preferred,QSizePolicy.Preferred)

        buttonF.setStyleSheet('QPushButton {background-color: #A3C1DA; color: purple;}')
        buttonRv.setStyleSheet('QPushButton {background-color: #A3C1DA; color: purple;}')
        buttonL.setStyleSheet('QPushButton {background-color: #A3C1DA; color: purple;}')
        buttonR.setStyleSheet('QPushButton {background-color: #A3C1DA; color: purple;}')
        buttonCW.setStyleSheet('QPushButton {background-color: #D7C4DA; color: purple;}')
        buttonCCW.setStyleSheet('QPushButton {background-color: #D7C4DA; color: purple;}')
        buttonS.setStyleSheet('QPushButton {background-color: #B22222; color: white; }')
        buttonTerminate.setStyleSheet('QPushButton {background-color: #CC0000; color: white; }')

        font = buttonF.font()
        font.setPointSize(24)
        buttonF.setFont(font)
        buttonRv.setFont(font)
        buttonL.setFont(font)
        buttonR.setFont(font)
        buttonS.setFont(font)
        buttonCCW.setFont(font)
        buttonCW.setFont(font)
        buttonTerminate.setFont(font)

        def on_forward_button_clicked():
            global actionCode
            actionCode = 1
            print (actionCode)
        def on_reverse_button_clicked():
            global actionCode
            actionCode = 2
        def on_left_button_clicked():
            global actionCode
            actionCode = 3
        def on_right_button_clicked():
            global actionCode
            actionCode = 4
            print (actionCode)
        def on_CW_button_clicked():
            global actionCode
            actionCode = 5
        def on_CCW_button_clicked():
            global actionCode
            actionCode = 6
        def on_stop_button_clicked():
            global actionCode
            actionCode = 0
        def on_terminate_button_clicked():
            global actionCode
            actionCode = 9

        buttonF.clicked.connect(on_forward_button_clicked)
        buttonRv.clicked.connect(on_reverse_button_clicked)
        buttonL.clicked.connect(on_left_button_clicked)
        buttonR.clicked.connect(on_right_button_clicked)
        buttonCW.clicked.connect(on_CW_button_clicked)
        buttonCCW.clicked.connect(on_CCW_button_clicked)
        buttonS.clicked.connect(on_stop_button_clicked)
        buttonTerminate.clicked.connect(on_terminate_button_clicked)


        layout.setRowMinimumHeight(3,100)

        layout.addWidget(buttonF,1,3)
        layout.addWidget(buttonRv,3,3)
        layout.addWidget(buttonL,2,1)
        layout.addWidget(buttonR,2,5)
        layout.addWidget(buttonCW,0,1)
        layout.addWidget(buttonCCW,0,5)
        layout.addWidget(buttonS,2,3)
        layout.addWidget(buttonTerminate,4,5)

        window.setLayout(layout)
        window.show()
        app.exec_()
        #createUI(self.actionParam)
        #actionCode = -1
        print ("Exiting UI Thread")


## thread logic here

queue = Queue()

#thread3 = Thread( target=thread3, args=("Thread-3 TCP", queue) )
threadTCP = Thread( target=threadTCP, args=("Thread-4 UI", queue, port) )
threadUI = Thread( target=threadUI, args=("Thread-4 UI", queue) )

#thread3.start()
threadTCP.start()
threadUI.start()
#thread3.join()
threadTCP.join()
threadUI.join()


# wait for 2 seconds for everything to settle
time.sleep(2)

#verify actionCode changed
print(actionCode)