import serial
import time

ser = serial.Serial(port='/dev/cu.usbmodem14201', baudrate=9600, timeout=1)  # Adjust the port. Use "ls /dev/tty.*" in root to find port
time.sleep(2)  # Wait for the connection to initialize

default_pos = [90,115,150,100,90,90,0] #Should result in everything pointing upwards

def jointSend(joint_vals):
    joint_vals_copy = joint_vals[:]
    message = ','.join(map(str,joint_vals_copy))
    ser.write(('J' + message + '\n').encode('utf-8'))  # Send the message
    print("J"+message + "\n")
    time.sleep(2)
    #To do: make it check for complete msg
    

def sweep(joint_list, joint_index, start_val, end_val):
    joint_list_copy = joint_list[:]
    #move to start val
    joint_list_copy[joint_index] = start_val
    jointSend(joint_list_copy)
    #move to end val
    joint_list_copy[joint_index] = end_val
    jointSend(joint_list_copy)
    #go back to original pos
    jointSend(joint_list)

sweep(default_pos,0,0,180)
sweep(default_pos,1,25,205) #end points should align with x axis
sweep(default_pos,2,60,240)
sweep(default_pos,3,10,190) #10 deg is actually 0 for this motor
sweep(default_pos,4,0,180)
sweep(default_pos,5,0,180)
sweep(default_pos,6,0,1)

