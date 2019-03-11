9600: with 200 ms sleep in python code and 12 ms delay in arduino code (from 'serial available' to message sent via println)...5 or 10ms write delay

57600: with 70 ms sleep in python code and 1 ms sec delay in arduino code... 1ms write delay 

115200: not reliable with same settings as 57600... so should use 57600

use ardser.py file for proper communication... PySerialListener has a slightly different format but is cleaner with times


