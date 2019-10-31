import serial
import os
import sys
import numpy as np
import matplotlib as plt
from pymavlink.dialects.v20 import mouse as mouseController

mouseController
a = MAVLINK_MSG_ID_BAD_DATA

port = "/dev/cu.usbmodem14102"
connection = serial.Serial(port, baudrate = 230400, timeout = 2)
mavlink = mouseController.MAVLink(file = connection )
mode = 0 
actualTime = 0  

while(True):
    try:
        m = mavlink.parse_char(connection.read())
    except:
        pass

    if m:
        if m.name == "HEARTBEAT":
            actualTime = m.time
            print(m)
            if m.mode == 0:
                mavlink.mode_selection_send(1)
            else:
                mavlink.mode_selection_send(0)
        elif m.name == "SPEED_INFO":
            pass
    
    
    m = None
   