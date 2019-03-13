from threading import Thread
from queue import Queue
import time

a = 2

def thread1(threadname, q):
    global a
    for _ in range(5):
        a += 7
        q.put(a)
        time.sleep(1)
        print("thread2: ", a)

def thread2(threadname, q):
    global a
    for _ in range(5):
        a += 1
        q.put(a)
        time.sleep(0.5)
        print("thread2: ", a)
    q.put(None) # Poison pill

queue = Queue()
thread1 = Thread( target=thread1, args=("Thread-1", queue) )
thread2 = Thread( target=thread2, args=("Thread-2", queue) )

thread1.start()
thread2.start()
thread1.join()
thread2.join()

print(a)