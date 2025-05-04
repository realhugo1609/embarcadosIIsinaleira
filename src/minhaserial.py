'''
import serial
ser = serial.Serial('COM5', 115200)  # open serial port
print(ser.name)         # check which port was really used
ser.write(b'hello')     # write a string
ser.close()             # close port
'''

import serial
import time
ser = serial.Serial("COM5", 115200)
   
# Send character 'S' to start the program
#while True:
#ser.write(bytearray('S','utf-8'))
#i = i+1

#time.sleep(2) # Wait 2 seconds
#print("PYTHON TERMINOU")


while True:
  bs = ser.readline()
  print(bs)

ser.close()