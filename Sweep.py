import serial
import time

ser = serial.Serial(port='/dev/tty.usbmodem14101', baudrate=9600, timeout=1)  # Adjust the port. Use "ls /dev/tty.*" in root to find port
time.sleep(2)  # Wait for the connection to initialize

default_pos = [90,90,90,90,90,90,0]

def jointSend(joint_vals):
    joint_vals_copy = joint_vals[:]
    message = ','.join(map(str,joint_vals_copy))
    ser.write(('J' + message + '\n').encode('utf-8'))  # Send the message
    print("J"+message + "\n")
    time.sleep(2)
    #To do: make it check for complete msg
    

def sweep(joint_list, joint_index, start_val, end_val):
    joint_list_copy = joint_list[:]
    for i in range(start_val,end_val+1,60):
        joint_list_copy[joint_index] = i
        print(joint_list_copy)
        jointSend(joint_list_copy)
    print(joint_list)
    jointSend(joint_list)

sweep(default_pos,0,0,180)
sweep(default_pos,1,90,150)
sweep(default_pos,2,30,210)
sweep(default_pos,3,0,270)
sweep(default_pos,4,0,180)
sweep(default_pos,5,0,180)

