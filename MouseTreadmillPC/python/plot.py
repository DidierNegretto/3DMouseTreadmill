import os
import sys
import matplotlib.pyplot as plt
import numpy as np
import json

files = ["log_0.01_speed_y.txt","log_0.02_speed_y.txt","log_0.03_speed_y.txt","log_0.04_speed_y.txt"]
start_time = [2063500, 2173590, 2275030, 15595]
stop_time =  [2123700, 2238690, 2354990, 74673]
log = []

for i in range(4):
    log.append(dict())
    log[i]["filename"] = "log/"+files[i]
    log[i]["SPEED_INFO"] = {}
    log[i]["MOTOR_SETPOINT"] = {}
    log[i]["SPEED_SETPOINT"] = {}
    log[i]["HEARTBEAT"] = {}
    log[i]["RAW_SENSOR"] = {}


    f =  open(log[i]["filename"], 'r')
    lines = f.readlines()
    for line in lines:
        data = line
        data = data.split(' ',1)

        stuff = data[1].split(',')
        for j in range(len(stuff)):
            stuff[j] = stuff[j].split(':')
        stuff[0][0] = stuff[0][0].replace('{','')
        stuff[-1][-1] = stuff[-1][-1].replace('}\n','')
        for j in range(len(stuff)-1):
            stuff[j][0] = stuff[j][0].replace(' ','')
            if stuff[j][0] not in log[i][data[0]]:
                log[i][data[0]][stuff[j][0]] = []
            log[i][data[0]][stuff[j][0]].append(float(stuff[j][1]))

fig = plt.figure()
ax = []
ax.append(fig.add_subplot(221))
ax.append(fig.add_subplot(222))
ax.append(fig.add_subplot(223))
ax.append(fig.add_subplot(224))

for i in range(4):
    ax[i].plot(log[i]["SPEED_INFO"]["time_y"], log[i]["SPEED_INFO"]["speed_y"])

fig = plt.figure()
ax = []
ax.append(fig.add_subplot(221))
ax.append(fig.add_subplot(222))
ax.append(fig.add_subplot(223))
ax.append(fig.add_subplot(224))

for i in range(4):
    t = [el for el in log[i]["SPEED_INFO"]["time_y"] if (el>start_time[i] and el<stop_time[i])]
    start_index = log[i]["SPEED_INFO"]["time_y"].index(t[0])
    end_index = log[i]["SPEED_INFO"]["time_y"].index(t[-1])
    y = log[i]["SPEED_INFO"]["speed_y"][start_index:end_index+1]
    ax[i].plot(t, y)
    
plt.show()






