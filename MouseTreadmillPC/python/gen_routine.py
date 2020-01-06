import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import time
import json
from tqdm import tqdm

MAX_POINTS = 201 # Number of maximum points in the routine you would like to use
ROUTINE_NAME = "ROUTINE"
ROUTINE_FILE = "routine_sin.py" # Where to store the new routine
TIME_LENGHT = 40000 # Total time lenght of the routine in ms
MAX_SPEED = 2
'''ATTENTION : the time difference between two data points MUST BE INTEGER !
    NOTE: the very last point is not exercuted.
'''


t = np.linspace(0,TIME_LENGHT,MAX_POINTS)
t_ref = np.linspace(0,TIME_LENGHT,10*MAX_POINTS)
print(t[1]-t[0])

# MODIFY THESE LINES FOR A DIFFERENT ROUTINE
vy = MAX_SPEED * np.sin(2*3.1415/10000*t)          
vy_ref = MAX_SPEED * np.sin(2*3.1415/10000*t_ref) 
vx = MAX_SPEED * np.cos(2*3.1415/10000*t)          
vx_ref = MAX_SPEED * np.cos(2*3.1415/10000*t_ref) 

# PLOTTING
plt.plot(vx,vy, 'rx', label = "Descrete", ms = 4)
plt.plot(vx_ref,vy_ref, 'b', label = "Reference", ms = 1)
plt.legend()
plt.xlabel("vx [m/s]")
plt.ylabel("vy [m/s]")
plt.axis('equal')
plt.show()

# SAVE AS ROUTINE
duration = np.array(np.roll(t,-1)-t)
duration[-1] = 0
duration = duration.astype(int)
setpoint_x = np.array(vx)
routine = {
    "duration":list(duration),
    "setpoint_x":list(vx),
    "setpoint_y":list(vy)
}
f = open(ROUTINE_FILE, 'w+')
f.write(ROUTINE_NAME+" = {\n")
f.write("\t"+'"'+"duration"+'"'+": "+ str(routine["duration"])+",\n")
f.write("\t"+'"'+"setpoint_x"+'"'+": "+ str(routine["setpoint_x"])+",\n")
f.write("\t"+'"'+"setpoint_y"+'"'+": "+ str(routine["setpoint_y"])+",\n")
f.write("}")
f.close()

