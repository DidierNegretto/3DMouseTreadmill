import os
import sys
import matplotlib.pyplot as plt
from matplotlib.gridspec import GridSpec
import numpy as np
import json

files = ["log_0.01_speed_y.txt","log_0.02_speed_y.txt","log_0.03_speed_y.txt","log_0.04_speed_y.txt", "log_0.05_speed_y.txt"]
start_time = [2063500, 2173590, 2275030, 15595, 110351]
stop_time =  [2123700, 2238690, 2354990, 74673, 141685]
log = []
path = "../../report/fig/"
start_time = np.array(start_time)
stop_time = np.array(stop_time)
print((stop_time-start_time)/1000)
print()
for i in range(5):
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
            if data[0] == "RAW_SENSOR":
                if int(stuff[1][1]) == 1:
                    log[i][data[0]][stuff[j][0]].append(float(stuff[j][1]))
            else:
                log[i][data[0]][stuff[j][0]].append(float(stuff[j][1]))

# =============================================================================

fig = plt.figure()
ax = []
ax.append(fig.add_subplot(231))
ax.append(fig.add_subplot(232))
ax.append(fig.add_subplot(233))
ax.append(fig.add_subplot(234))
ax.append(fig.add_subplot(235))

t_sensor = {"data" : [], "mean": [], "min": [], "max": [],"std": [], "median": []}
squal = {"data" : [], "mean": [], "min": [], "max": [],"std": [], "median": []}

for i in range(5):
    t = [el for el in log[i]["RAW_SENSOR"]["time"] if (el>start_time[i] and el<stop_time[i])]
    t_sensor["data"].append(np.array(t))
    start_index = log[i]["RAW_SENSOR"]["time"].index(t[0])
    end_index = log[i]["RAW_SENSOR"]["time"].index(t[-1])
    y = log[i]["RAW_SENSOR"]["squal"][start_index:end_index+1]
    squal["data"].append(np.array(y))
    squal["min"].append(np.amin(squal["data"][i]))
    squal["max"].append(np.amax(squal["data"][i]))
    squal["mean"].append(np.mean(squal["data"][i]))
    squal["std"].append(np.std(squal["data"][i]))
    squal["median"].append(np.median(squal["data"][i]))
    ax[i].plot(t,y)

# =============================================================================

fig = plt.figure()
ax = []
ax.append(fig.add_subplot(231))
ax.append(fig.add_subplot(232))
ax.append(fig.add_subplot(233))
ax.append(fig.add_subplot(234))
ax.append(fig.add_subplot(235))

t_speed = {"data" : [], "mean": [], "min": [], "max": [],"std": [], "median": []}
speed = {"data" : [], "mean": [], "min": [], "max": [],"std": [], "median": []}

for i in range(5):
    t = [el for el in log[i]["SPEED_INFO"]["time_y"] if (el>start_time[i] and el<stop_time[i])]
    t_speed["data"].append(np.array(t))
    start_index = log[i]["SPEED_INFO"]["time_y"].index(t[0])
    end_index = log[i]["SPEED_INFO"]["time_y"].index(t[-1])
    y = log[i]["SPEED_INFO"]["speed_y"][start_index:end_index+1]
    speed["data"].append(np.array(y))
    speed["min"].append(np.amin(speed["data"][i]))
    speed["max"].append(np.amax(speed["data"][i]))
    speed["mean"].append(np.mean(speed["data"][i]))
    speed["std"].append(np.std(speed["data"][i]))
    speed["median"].append(np.median(speed["data"][i]))
    ax[i].plot(t, y)

# =============================================================================

fig = plt.figure(tight_layout = True)
ax = []
meanp = []
meanm = []
x = [0.01, 0.02, 0.03, 0.04, 0.05]
y_ticks = []

ax.append(fig.add_subplot(111))
ax[0].set_xticks(x)
ax[0].set_title("Measured speed for different speed setpoints")
ax[0].plot(x, x, "r.", label = "reference")
y_ticks.extend(speed["median"])
ax[0].plot(x, speed["mean"], "k.", label = "mean", ms = 3)
ax[0].plot(x, speed["median"], "k_", label = "median")
meanp = (np.array(speed["mean"])+np.array(speed["std"]))
ax[0].plot(x, meanp, "kx", label = "std")
meanm = (np.array(speed["mean"])-np.array(speed["std"]))
ax[0].plot(x, meanm, "kx")

ax[0].plot(x, speed["max"], "kv", label = "min/max")
ax[0].plot(x, speed["min"], "k^")

for i in range(5):
    ax[0].plot([x[i], x[i]], [speed["max"][i], meanp[i]], "k" )
    ax[0].plot([x[i], x[i]], [speed["min"][i], meanm[i]], "k" )
    #ax[0].plot([x[i], x[i]], [, meanm[i]], "c-" )


ax[0].set_xlabel("Speed setpoint [m/s]")
ax[0].set_ylabel("Measured speed [m/s]")

ax[0].legend()


plt.savefig(path+"steady_state.pdf")

# =============================================================================

for i in range(5):
    fig = plt.figure(figsize=(13, 4))#, tight_layout = True)
    gs = GridSpec(nrows = 1, ncols = 3,wspace=0.0, figure = fig)

    ax = []

    ax.append(fig.add_subplot(gs[0, :-1]))
    ax.append(fig.add_subplot(gs[0, -1], sharey = ax[0]))
    plt.setp(ax[1].get_yticklabels(), visible=False)
    ax[1].tick_params(size=0)

    ax[0].set_title("Speed error at speed = "+str(x[i])+" [m/s]")
    ax[1].set_title("Speed error distribution at speed = "+str(x[i])+" [m/s]")

    ax[0].plot(t_speed["data"][i], speed["data"][i]-x[i], "k-", lw = 0.01)

    ax[0].set_xlabel("Time [ms]")
    ax[0].set_ylabel("Speed error [m/s]")
    ax[1].set_xlabel("Number of occurencies [ ]")
    ax[1].hist(speed["data"][i]-x[i],bins =18 , orientation = 'horizontal', histtype = 'step', ec = 'k')
    #ax[1].set_yticks([])
    titicaca = ax[0].get_xticks()
    titicaca = titicaca[1:-2]
    ax[0].set_xticks(titicaca)
    print("%.2f"%x[i]+"&"+"%.4f"%speed["mean"][i]+"&"+"%.4f"%speed["median"][i]+"&"+"%.4f"%speed["std"][i]+"&"+"%.4f"%speed["min"][i]+"&"+"%.4f"%speed["max"][i]+"&"+"$[\\frac{m}{s}]$"+"\\\\"+"\\hline")

    plt.savefig(path+"speed_error_"+str(i)+".pdf")

# =============================================================================

timestamp = []
for i in range(5):
    timestamp.extend(t_speed["data"][i])
timestamp = np.array(timestamp)
dt = timestamp-np.roll(timestamp,1)

dt = [el for el in dt if (el>0 and el<100)]
dt = np.array(dt)
dt = dt/1000
dt = 1/dt
x = np.arange(0,len(dt))

fig = plt.figure(figsize=(13, 4), tight_layout = True)
gs = GridSpec(nrows = 1, ncols = 3,hspace=0.0, figure = fig)

ax = []

ax.append(fig.add_subplot(gs[0, :-1]))
ax.append(fig.add_subplot(gs[0, -1]))#, sharey=ax[0]))

ax[0].plot(x, dt, "k.", lw = 0.01)

ax[0].set_xlabel("Time [ms]")
ax[0].set_ylabel("Frequency [Hz]")
ax[0].set_yticks([np.amax(dt), np.amin(dt)])
ax[1].set_xlabel("Number of occurencies [ ]")
res = ax[1].hist(dt,bins =18 , orientation = 'horizontal', histtype = 'step', ec = 'k')

ax[1].set_yticks([])
ax[1].set_xticks([res[0][0], res[0][-1] ])

print("Mean frequency = "+str(np.mean(dt)))
print("STD on frequency = "+str(np.std(dt)))
plt.savefig(path+"freq.pdf")

# =============================================================================

fig = plt.figure()
ax = []
meanp = []
meanm = []
x = [0.01, 0.02, 0.03, 0.04, 0.05]
y_ticks = []

ax.append(fig.add_subplot(111))
ax[0].set_xticks(x)
y_ticks.extend(speed["std"])
ax[0].plot(x, speed["std"], "k.--", label = "mean")

ax[0].set_xlabel("Reference speed [m/s]")
ax[0].set_ylabel("Standard deviation [m/s]")

ax[0].legend()


plt.savefig(path+"std_speed.pdf")

# =============================================================================
print("POS ERROR")
pos_error = {"data" : [], "mean": [], "min": [], "max": [],"std": [], "median": []}
for i in range(5):
    fig = plt.figure(figsize=(13, 4))#, tight_layout = True)
    gs = GridSpec(nrows = 1, ncols = 3,wspace=0.0, figure = fig)

    ax = []

    ax.append(fig.add_subplot(gs[0, :-1]))
    ax.append(fig.add_subplot(gs[0, -1]))#, sharey=ax[0]))
    plt.setp(ax[1].get_yticklabels(), visible=False)
    ax[1].tick_params(size=0)

    ref_pos = []
    pos = {"data":[], "time":[]}
    pos["data"].append(0)
    ref_pos.append(0)
    for j in range(1,len(speed["data"][i])-1):
        pos["data"].append(speed["data"][i][j]*(t_speed["data"][i][j]-t_speed["data"][i][j-1])/1000+ref_pos[j-1])
        ref_pos.append(x[i]*(t_speed["data"][i][j]-t_speed["data"][i][j-1]) /1000+ ref_pos[j-1])
    
    pos_error["data"].append((np.array(ref_pos)-np.array(pos["data"]))*1000)
    ax[0].plot(t_speed["data"][i][0:-1], pos_error["data"][i], 'k-', lw = 0.01)
    res = ax[1].hist(pos_error["data"][i],bins =18 , orientation = 'horizontal', histtype = 'step', ec = 'k')
    
    ax[0].set_title("Position error at speed = "+str(x[i])+" [m/s]")
    ax[1].set_title("Position error distribution at speed = "+str(x[i])+" [m/s]")

    ax[1].set_xlabel("Number of occurencies [ ]")
    ax[1].set_yticks([])
    #ax[1].set_xticks(res[0] )
    ax[0].set_xlabel("Time [ms]")
    ax[0].set_ylabel("Position error [mm]")
    titicaca = ax[0].get_xticks()
    titicaca = titicaca[1:-2]
    ax[0].set_xticks(titicaca)
    
    plt.savefig(path+"pos_error_"+str(i)+".pdf")

    pos_error["min"].append(np.amin(pos_error["data"][i]))
    pos_error["max"].append(np.amax(pos_error["data"][i]))
    pos_error["mean"].append(np.mean(pos_error["data"][i]))
    pos_error["std"].append(np.std(pos_error["data"][i]))
    pos_error["median"].append(np.median(pos_error["data"][i]))
    print('{0:0.4}'.format(x[i])+" $[\\frac{m}{s}]$"+"&"+'{0:1.4e}'.format((pos_error["mean"][i]/1000))+"&"+'{0:1.4e}'.format((pos_error["median"][i]/1000))+"&"+'{0:1.4e}'.format((pos_error["std"][i]/1000))+"&"+'{0:1.4e}'.format((pos_error["min"][i]/1000))+"&"+'{0:1.4e}'.format((pos_error["max"][i]/1000))+"&"+"$[m]$"+"\\\\"+"\\hline")

# =============================================================================
plt.close("all")
fig = plt.figure()
ax = []
asgard = [0,0,0,0,0]
ax.append(fig.add_subplot(111))
ax[0].set_xticks(x)
ax[0].set_title("Position error for different speed setpoints")
ax[0].plot(x,asgard, "r.", label = "reference")
y_ticks.extend(pos_error["median"])
ax[0].plot(x, pos_error["mean"], "k.", label = "mean", ms = 3)
ax[0].plot(x, pos_error["median"], "k_", label = "median")
meanp = (np.array(pos_error["mean"])+np.array(pos_error["std"]))
ax[0].plot(x, meanp, "kx", label = "std")
meanm = (np.array(pos_error["mean"])-np.array(pos_error["std"]))
ax[0].plot(x, meanm, "kx")

ax[0].plot(x, pos_error["max"], "kv", label = "min/max")
ax[0].plot(x, pos_error["min"], "k^")

for i in range(5):
    ax[0].plot([x[i], x[i]], [pos_error["max"][i], meanp[i]], "k" )
    ax[0].plot([x[i], x[i]], [pos_error["min"][i], meanm[i]], "k" )
    #ax[0].plot([x[i], x[i]], [, meanm[i]], "c-" )

ax[0].set_xlabel("Reference speed [m/s]")
ax[0].set_ylabel("Position error [mm]")

ax[0].legend()


plt.savefig(path+"pos_error_comp.pdf")
# =============================================================================
plt.close("all")

fig = plt.figure()
ax = []
meanp = []
meanm = []
x = [0.01, 0.02, 0.03, 0.04, 0.05]
y_ticks = []

ax.append(fig.add_subplot(111))
ax[0].set_xticks(x)
y_ticks.extend(pos_error["std"])
ax[0].plot(x, pos_error["std"], "k.--", label = "mean")

ax[0].set_xlabel("Reference speed [m/s]")
ax[0].set_ylabel("Position Standard deviation [mm]")

ax[0].legend()

#plt.show()




