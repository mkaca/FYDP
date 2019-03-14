from threading import Thread
from queue import Queue
import time
from PyQt5.QtWidgets import *

actionCode = 0

def thread1(threadname, q):
    global actionCode
    for _ in range(5):
        actionCode += 7
        q.put(actionCode)
        time.sleep(1)
        print("thread2: ", actionCode)

def thread2(threadname, q):
    global actionCode
    for _ in range(5):
        actionCode += 1
        q.put(actionCode)
        time.sleep(0.2)
        print("thread2: ", actionCode)
    q.put(None) # Poison pill

def thread3(threadname, q):
    global actionCode
    for _ in range(10):
        print("thread3: ", actionCode)
        time.sleep(1)

def thread4(threadname, q):
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
        #createUI(self.actionParam)
        print ("Exiting thread4")

queue = Queue()
"""
thread1 = Thread( target=thread1, args=("Thread-1", queue) )
thread2 = Thread( target=thread2, args=("Thread-2", queue) )

thread1.start()
thread2.start()
thread1.join()
thread2.join()
"""

thread3 = Thread( target=thread3, args=("Thread-3 TCP", queue) )
thread4 = Thread( target=thread4, args=("Thread-4 UI", queue) )

thread3.start()
thread4.start()
thread3.join()
thread4.join()


time.sleep(3)

print(actionCode)