import os
import sys
import matplotlib as plt
import numpy as np
import json

files = ["log_0.01_speed_y.txt","log_0.02_speed_y.txt","log_0.03_speed_y.txt","log_0.04_speed_y.txt"]
start_time = []
stop_time = []
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

    

print(log[1]["RAW_SENSOR"]['time'])





