import serial
import os
import sys
import numpy as np
#import matplotlib as plt
from appJar import gui
import time
from tqdm import tqdm
import routine as mouseRoutine
from pymavlink.dialects.v20 import mouse as mouseController

"""
PATH

/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/MouseTreadmillPC/python
"""
POSITIONS = {
    "Port": {"x":0,"y":0,"lx":1,"ly":1},
    "portEntry": {"x":0,"y":1,"lx":3,"ly":1},
    "Stop": {"x":1,"y":2,"lx":1,"ly":1},
    "optionMode0": {"x":0,"y":1,"lx":2,"ly":1},
    "optionMode1": {"x":0,"y":3,"lx":2,"ly":1},
    "optionMode2": {"x":0,"y":5,"lx":2,"ly":1},
    "optionModeLabel": {"x":0,"y":0,"lx":1,"ly":1},
    "speedXLabel": {"x":1,"y":0,"lx":1,"ly":1},
    "speedX": {"x":2,"y":0,"lx":1,"ly":1},
    "speedYLabel": {"x":1,"y":1,"lx":1,"ly":1},
    "speedY": {"x":2,"y":1,"lx":1,"ly":1},
    "speedSetpointLabel": {"x":3,"y":2,"lx":1,"ly":1},
    "speedSetpointX": {"x":3,"y":0,"lx":1,"ly":1},
    "speedSetpointY": {"x":3,"y":1,"lx":1,"ly":1},
    "motorSetpointLabel": {"x":4,"y":2,"lx":1,"ly":1},
    "motorSetpointX": {"x":4,"y":0,"lx":1,"ly":1},
    "motorSetpointY": {"x":4,"y":1,"lx":1,"ly":1},
    "plot" : {"x":4,"y":1,"lx":1,"ly":1},
    "resetPlot" : {"x":1,"y":3,"lx":2,"ly":1},
   
}
MODES = ["STOP", "SPEED","AUTO","RUNNING"]
MODES_NUM = {"STOP": int(0),"SPEED": int(1),"AUTO": int(2),"RUNNING": int(3) }
DATA = { "HEARTBEAT": {"time": [], "mode": []}, 
         "SPEED_SETPOINT": {"time": [], "setpoint_x": [], "setpoint_y": [], "start": 0}, 
         "SPEED_INFO":  {"time": [], "speed_x": [], "speed_y": [], "start": 0}, 
         "MOTOR_SETPOINT": {"time": [], "motor_x": [], "motor_y": [], "start": 0} 
         }
MAX_SAMPLES_ON_SCREEN = 200
port = "/dev/cu.usbmodem14102"
 

class MyApplication():
     actualMode = 0 
     actualTime = 0 
     actualSpeedSetpoint = [None, None]
     actualMotorSetpoint = [None, None]
     actualSpeedInfo = [None, None] 
     connection = serial.Serial(port, baudrate = 230400, timeout = 50)
     mavlink = mouseController.MAVLink(file = connection )
     setpointX = 0.0
     setpointY = 0.0

     def commSTM32 (self):
        # Init variables
        m = None
        while(self.connection.in_waiting>0):
            # Recive messages
            try:
                m = self.mavlink.parse_char(self.connection.read())
            except:
                pass
            if m:
                #print(m)
                if m.name == "HEARTBEAT":
                    self.actualTime = m.time
                    self.actualMode = m.mode
                    DATA["HEARTBEAT"]["time"].append(self.actualTime)
                    DATA["HEARTBEAT"]["mode"].append(self.actualMode)
                elif m.name == "SPEED_SETPOINT":
                    self.actualSpeedSetpoint[0] = m.setpoint_x
                    self.actualSpeedSetpoint[1] = m.setpoint_y
                    DATA["SPEED_SETPOINT"]["time"].append(self.actualTime)
                    DATA["SPEED_SETPOINT"]["setpoint_x"].append(self.actualSpeedSetpoint[0])
                    DATA["SPEED_SETPOINT"]["setpoint_y"].append(self.actualSpeedSetpoint[1])
                    #DATA["SPEED_SETPOINT"]["setpoint_z"].append(self.actualSpeedSetpoint[2])
                elif m.name == "MOTOR_SETPOINT":
                    self.actualMotorSetpoint[0] = m.motor_x
                    self.actualMotorSetpoint[1] = m.motor_y
                    DATA["MOTOR_SETPOINT"]["time"].append(m.time)
                    DATA["MOTOR_SETPOINT"]["motor_x"].append(self.actualMotorSetpoint[0])
                    DATA["MOTOR_SETPOINT"]["motor_y"].append(self.actualMotorSetpoint[1])
                    #DATA["SPEED_SETPOINT"]["motor_z"].append(self.actualMotorSetpoint[2])
                elif m.name == "SPEED_INFO":
                    self.actualSpeedInfo[0] = m.speed_x
                    self.actualSpeedInfo[1] = m.speed_y
                    DATA["SPEED_INFO"]["time"].append(m.time)
                    DATA["SPEED_INFO"]["speed_x"].append(self.actualSpeedInfo[0])
                    DATA["SPEED_INFO"]["speed_y"].append(self.actualSpeedInfo[1])
                    #DATA["SPEED_SETPOINT"]["speed_z"].append(self.actualSpeedInfo[2])
                elif m.name == "POINT":
                    print(m)
                else:
                    pass
            m = None
     def refreshPlot(self):
       
        # Clear plot
        for i in range(3):
            self.ax[i].clear()
        
        # Define labels
        """
        self.ax[2].set_xlabel("Time")
        self.ax[2].set_ylabel("Measured speed [m/s]")
        self.ax[1].set_ylabel("Speed setpoint [m/s]")
        self.ax[0].set_ylabel("Motor signal [ ]")
        """
        
        # Limit max amout of points on one graph
        if len(DATA["SPEED_INFO"]["time"][DATA["SPEED_INFO"]["start"]:])-1>MAX_SAMPLES_ON_SCREEN:
            DATA["SPEED_INFO"]["start"] = -MAX_SAMPLES_ON_SCREEN
            DATA["SPEED_SETPOINT"]["start"] = -MAX_SAMPLES_ON_SCREEN
            DATA["MOTOR_SETPOINT"]["start"] = -MAX_SAMPLES_ON_SCREEN

        # Re-plot all graphs
        self.ax[2].plot(DATA["SPEED_INFO"]["time"][DATA["SPEED_INFO"]["start"]:], DATA["SPEED_INFO"]["speed_x"][DATA["SPEED_INFO"]["start"]:], 'b.')
        self.ax[2].plot(DATA["SPEED_INFO"]["time"][DATA["SPEED_INFO"]["start"]:], DATA["SPEED_INFO"]["speed_y"][DATA["SPEED_INFO"]["start"]:], 'r.')
        self.ax[1].plot(DATA["SPEED_SETPOINT"]["time"][DATA["SPEED_SETPOINT"]["start"]:], DATA["SPEED_SETPOINT"]["setpoint_x"][DATA["SPEED_SETPOINT"]["start"]:],'b.')
        self.ax[1].plot(DATA["SPEED_SETPOINT"]["time"][DATA["SPEED_SETPOINT"]["start"]:], DATA["SPEED_SETPOINT"]["setpoint_y"][DATA["SPEED_SETPOINT"]["start"]:],'r.')
        self.ax[0].plot(DATA["MOTOR_SETPOINT"]["time"][DATA["MOTOR_SETPOINT"]["start"]:], DATA["MOTOR_SETPOINT"]["motor_x"][DATA["MOTOR_SETPOINT"]["start"]:],'b.')
        self.ax[0].plot(DATA["MOTOR_SETPOINT"]["time"][DATA["MOTOR_SETPOINT"]["start"]:], DATA["MOTOR_SETPOINT"]["motor_y"][DATA["MOTOR_SETPOINT"]["start"]:],'r.')
        self.ax[0].set_adjustable('box',True)
        self.app.refreshPlot("plot")
     
     def resetPlot(self):
        DATA["SPEED_INFO"]["start"] = len(DATA["SPEED_INFO"]["time"])-3
        DATA["SPEED_SETPOINT"]["start"] = len(DATA["SPEED_SETPOINT"]["time"])-3
        DATA["MOTOR_SETPOINT"]["start"] = len(DATA["MOTOR_SETPOINT"]["time"])-3
        
     def refreshGUI(self):
        self.commSTM32()
        
        # Refresh status bar
        self.app.setStatusbar("Time: "+str(self.actualTime)+" [ms]", 0)
        self.app.setStatusbar("Modes: "+str(MODES[self.actualMode]), 1)
        self.refreshPlot()
        """
        self.app.setLabel("speedSetpointX", str(self.actualSpeedSetpoint[0]))
        self.app.setLabel("speedSetpointY", str(self.actualSpeedSetpoint[1]))
        self.app.setLabel("motorSetpointX", str(self.actualMotorSetpoint[0]))
        self.app.setLabel("motorSetpointY", str(self.actualMotorSetpoint[1]))
        """

     def setMode(self):
         self.mavlink.mode_selection_send(MODES_NUM[self.app.getRadioButton("optionMode")]) 
         while(self.connection.out_waiting > 0):
            time.sleep(0.001)
         time.sleep(0.001)
         if self.actualMode == mouseController.MOUSE_MODE_STOP:
             self.setpointX = 0
             self.setpointY = 0

     
     def setSpeedX(self):
        if self.actualMode == mouseController.MOUSE_MODE_SPEED:
            self.setpointX = self.app.getEntry("speedX")
            if self.setpointX is None or  self.setpointY is None :
                pass
            else:
                self.mavlink.speed_setpoint_send(float(self.setpointX), float(self.setpointY))
                while(self.connection.out_waiting > 0):
                    time.sleep(0.001)
                time.sleep(0.001)
    
     def setSpeedY(self):
        if self.actualMode == mouseController.MOUSE_MODE_SPEED:
            self.setpointY = self.app.getEntry("speedY")
            if self.setpointX is None or  self.setpointY is None :
                pass
            else:
                self.mavlink.speed_setpoint_send(float(self.setpointX), float(self.setpointY))
            while(self.connection.out_waiting > 0):
                time.sleep(0.001)
            time.sleep(0.001)

     def loadRoutine(self):
        if self.actualMode == mouseController.MOUSE_MODE_AUTO_LOAD:
            if (len(mouseRoutine.ROUTINE["duration"])>254 or len(mouseRoutine.ROUTINE["setpoint_x"])>254 or len(mouseRoutine.ROUTINE["setpoint_y"])>254):
                raise ValueError("mouseRoutine too long")
            if not (len(mouseRoutine.ROUTINE["duration"]) == len(mouseRoutine.ROUTINE["setpoint_x"]) == len(mouseRoutine.ROUTINE["setpoint_y"])):
                raise ValueError("not all components of mouseRoutine have the same lenght")
            
            
            # TODO add verification on max speed and min speed
            
            
            for i in tqdm(range(len(mouseRoutine.ROUTINE["duration"]))):
                self.mavlink.point_send(mouseRoutine.ROUTINE["duration"][i],i,mouseRoutine.ROUTINE["setpoint_x"][i], mouseRoutine.ROUTINE["setpoint_y"][i])
                stop = True
                while(self.connection.in_waiting>0 or stop):
                    # Recive messages
                    try:
                        m = self.mavlink.parse_char(self.connection.read())
                    except:
                        pass
                    if m:
                        #print(m)
                        if m.name == "POINT_LOADED":
                            if m.point_id == i:
                                stop = False
                            else:
                                raise Exception("ERROR LOADING DATA, wrong msg_id received")
                



            
               
     def runRoutine(self):
        if self.actualMode == mouseController.MOUSE_MODE_AUTO_LOAD:
            self.mavlink.mode_selection_send(mouseController.MOUSE_MODE_AUTO_RUN)
            while(self.connection.out_waiting > 0):
                time.sleep(0.001)
            time.sleep(0.001)

     def Prepare(self, app):
        self.ax = []
        
        app.setTitle("Mouse treadmill GUI")
        app.setFont(16)

        """
        # Entry for port. Set to default value 
        app.addLabel("Port","Port",POSITIONS["Port"]["x"],POSITIONS["Port"]["y"],POSITIONS["Port"]["lx"],POSITIONS["Port"]["ly"])
        app.addEntry("portEntry",POSITIONS["portEntry"]["x"],POSITIONS["portEntry"]["y"],POSITIONS["portEntry"]["lx"],POSITIONS["portEntry"]["ly"])
        app.setEntry("portEntry", "/dev/cu.usbmodem14102")


        # Button for stop mode
        app.addButton("Stop", self.stopMode, POSITIONS["Stop"]["x"],POSITIONS["Stop"]["y"],POSITIONS["Stop"]["lx"],POSITIONS["Stop"]["ly"])
        """

        # Mode Selection
        app.addLabel("optionModeLabel","Mode",POSITIONS["optionModeLabel"]["x"],POSITIONS["optionModeLabel"]["y"],POSITIONS["optionModeLabel"]["lx"],POSITIONS["optionModeLabel"]["ly"])
        app.addRadioButton("optionMode",MODES[0],POSITIONS["optionMode0"]["x"],POSITIONS["optionMode0"]["y"],POSITIONS["optionMode0"]["lx"],POSITIONS["optionMode0"]["ly"])
        app.addRadioButton("optionMode",MODES[1],POSITIONS["optionMode1"]["x"],POSITIONS["optionMode1"]["y"],POSITIONS["optionMode1"]["lx"],POSITIONS["optionMode1"]["ly"])
        app.addRadioButton("optionMode",MODES[2],POSITIONS["optionMode2"]["x"],POSITIONS["optionMode2"]["y"],POSITIONS["optionMode2"]["lx"],POSITIONS["optionMode2"]["ly"])
        app.setRadioButtonChangeFunction("optionMode",self.setMode)

        # Speed entry
        app.addLabel("speedXLabel", "Speed X", POSITIONS["speedXLabel"]["x"],POSITIONS["speedXLabel"]["y"],POSITIONS["speedXLabel"]["lx"],POSITIONS["speedXLabel"]["ly"])
        app.addNumericEntry("speedX",POSITIONS["speedX"]["x"],POSITIONS["speedX"]["y"],POSITIONS["speedX"]["lx"],POSITIONS["speedX"]["ly"])
        app.setEntry("speedX", 0.0)
        app.setEntryChangeFunction("speedX", self.setSpeedX)
        app.addLabel("speedYLabel", "Speed Y",POSITIONS["speedYLabel"]["x"],POSITIONS["speedYLabel"]["y"],POSITIONS["speedYLabel"]["lx"],POSITIONS["speedYLabel"]["ly"])
        app.addNumericEntry("speedY",POSITIONS["speedY"]["x"],POSITIONS["speedY"]["y"],POSITIONS["speedY"]["lx"],POSITIONS["speedY"]["ly"])
        app.setEntry("speedY", 0.0)
        app.setEntryChangeFunction("speedY", self.setSpeedY)
       

        # Showing values from STM32
        """
        app.addLabel("speedSetpointLabel", "MCU Setpoint",POSITIONS["speedSetpointLabel"]["x"],POSITIONS["speedSetpointLabel"]["y"],POSITIONS["speedSetpointLabel"]["lx"],POSITIONS["speedSetpointLabel"]["ly"])
        app.addLabel("speedSetpointX", "0",POSITIONS["speedSetpointX"]["x"],POSITIONS["speedSetpointX"]["y"],POSITIONS["speedSetpointX"]["lx"],POSITIONS["speedSetpointX"]["ly"])
        app.addLabel("speedSetpointY", "0",POSITIONS["speedSetpointY"]["x"],POSITIONS["speedSetpointY"]["y"],POSITIONS["speedSetpointY"]["lx"],POSITIONS["speedSetpointY"]["ly"])
        app.addLabel("motorSetpointLabel", "Motors",POSITIONS["motorSetpointLabel"]["x"],POSITIONS["motorSetpointLabel"]["y"],POSITIONS["motorSetpointLabel"]["lx"],POSITIONS["motorSetpointLabel"]["ly"])
        app.addLabel("motorSetpointX", "0",POSITIONS["motorSetpointX"]["x"],POSITIONS["motorSetpointX"]["y"],POSITIONS["motorSetpointX"]["lx"],POSITIONS["motorSetpointX"]["ly"])
        app.addLabel("motorSetpointY", "0",POSITIONS["motorSetpointY"]["x"],POSITIONS["motorSetpointY"]["y"],POSITIONS["motorSetpointY"]["lx"],POSITIONS["motorSetpointY"]["ly"])
        """

        # Real-time data plotting
        self.fig = app.addPlotFig("plot",row = None, column = 0,colspan = 4, showNav = True )
        self.ax.append(self.fig.add_subplot(311)) 
        self.ax.append(self.fig.add_subplot(312)) 
        self.ax.append(self.fig.add_subplot(313)) 
        
        # Reset plot button
        self.app.addButton("resetPlot", self.resetPlot, POSITIONS["resetPlot"]["x"],POSITIONS["resetPlot"]["y"],POSITIONS["resetPlot"]["lx"],POSITIONS["resetPlot"]["ly"])
        self.app.addButton("loadData", self.loadRoutine, POSITIONS["resetPlot"]["x"]+1,POSITIONS["resetPlot"]["y"],POSITIONS["resetPlot"]["lx"],POSITIONS["resetPlot"]["ly"])
        self.app.addButton("RUN", self.runRoutine, POSITIONS["resetPlot"]["x"]+1,POSITIONS["resetPlot"]["y"]+1,POSITIONS["resetPlot"]["lx"],POSITIONS["resetPlot"]["ly"])
       
        # Add status bar
        app.addStatusbar(fields = 2, side=None)
        app.setStatusbar("Time: 0", 0)
        app.setStatusbar("Mode: "+MODES[0], 1)

        # refresh funciton
        app.setPollTime(100)
        app.registerEvent(self.refreshGUI)

        # Thread for communication
        #app.thread(self.commSTM32)
        return app
     # Build and Start your application
     def Start(self):
        app = gui()

        self.app = app
        
        # Run the prebuild method that adds items to the UI
        self.app = self.Prepare(self.app)
                
        # Start appJar
        self.app.go()

if __name__ == '__main__':
    print("============================================================")
    print("Running GUI for mouse treadmill")
    print("============================================================")

    # Create an instance of your application
    App = MyApplication()
    # Start your app !
    App.Start()




   