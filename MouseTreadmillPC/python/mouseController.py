import serial
import os
import sys
import numpy as np
import matplotlib as plt
from appJar import gui
import time
from pymavlink.dialects.v20 import mouse as mouseController

"""
PATH

/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/MouseTreadmillPC/python
"""
POSITIONS = {
    "Port": {"x":0,"y":0,"lx":1,"ly":1},
    "portEntry": {"x":0,"y":1,"lx":3,"ly":1},
    "Stop": {"x":1,"y":2,"lx":1,"ly":1},
    "optionMode0": {"x":0,"y":1,"lx":3,"ly":1},
    "optionMode1": {"x":0,"y":2,"lx":3,"ly":1},
    "optionMode2": {"x":0,"y":3,"lx":1,"ly":1},
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
   
}
MODES = ["STOP", "SPEED", "AUTO"]
MODES_NUM = {"STOP": int(0),"SPEED": int(1),"AUTO": int(2) }
port = "/dev/cu.usbmodem14102"
 

class MyApplication():
     actualMode = 0 
     actualTime = 0 
     actualSpeedSetpoint = [None, None, None]
     actualMotorSetpoint = [None, None, None]
     connection = serial.Serial(port, baudrate = 230400, timeout = 0)
     mavlink = mouseController.MAVLink(file = connection )
     setpointX = 0.0
     setpointY = 0.0

     def commSTM32 (self):
        # Init variables
        m = None

        if self.actualMode == mouseController.MOUSE_MODE_SPEED:
            self.setpointX = self.app.getEntry("speedX")
            self.setpointY = self.app.getEntry("speedY")

        while(self.connection.in_waiting>0):
            # Recive messages
            try:
                m = self.mavlink.parse_char(self.connection.read())
            except:
                pass
            if m:
                print(m)
                if m.name == "HEARTBEAT":
                    self.actualTime = m.time
                    self.actualMode = m.mode
                elif m.name == "SPEED_SETPOINT":
                    self.actualSpeedSetpoint[0] = m.setpoint_x
                    self.actualSpeedSetpoint[1] = m.setpoint_y
                    self.actualSpeedSetpoint[2] = m.setpoint_z
                elif m.name == "MOTOR_SETPOINT":
                    self.actualMotorSetpoint[0] = m.motor_x
                    self.actualMotorSetpoint[1] = m.motor_y
                    self.actualMotorSetpoint[2] = m.motor_z
                else:
                    pass
            m = None
        if self.setpointX is None  or self.setpointY is None:
            pass
        else:
            self.mavlink.speed_setpoint_send(float(self.setpointX), float(self.setpointY), 0.0)

        while(self.connection.out_waiting > 0):
            pass

     def refreshGUI(self):
        self.commSTM32()
        # Refresh status bar
        self.app.setStatusbar("Time: "+str(self.actualTime)+" [ms]", 0)
        self.app.setStatusbar("Modes: "+str(MODES[self.actualMode]), 1)
        # Refresh with data from  
        self.app.setLabel("speedSetpointX", str(self.actualSpeedSetpoint[0]))
        self.app.setLabel("speedSetpointY", str(self.actualSpeedSetpoint[1]))
        self.app.setLabel("motorSetpointX", str(self.actualMotorSetpoint[0]))
        self.app.setLabel("motorSetpointY", str(self.actualMotorSetpoint[1]))

     def setMode(self):
         self.mavlink.mode_selection_send(MODES_NUM[self.app.getRadioButton("optionMode")])        


     def Prepare(self, app):
        
        
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
        app.addLabel("speedYLabel", "Speed Y",POSITIONS["speedYLabel"]["x"],POSITIONS["speedYLabel"]["y"],POSITIONS["speedYLabel"]["lx"],POSITIONS["speedYLabel"]["ly"])
        app.addNumericEntry("speedY",POSITIONS["speedY"]["x"],POSITIONS["speedY"]["y"],POSITIONS["speedY"]["lx"],POSITIONS["speedY"]["ly"])
        app.setEntry("speedY", 0.0)

        # Showing values from STM32
        app.addLabel("speedSetpointLabel", "MCU Setpoint",POSITIONS["speedSetpointLabel"]["x"],POSITIONS["speedSetpointLabel"]["y"],POSITIONS["speedSetpointLabel"]["lx"],POSITIONS["speedSetpointLabel"]["ly"])
        app.addLabel("speedSetpointX", "0",POSITIONS["speedSetpointX"]["x"],POSITIONS["speedSetpointX"]["y"],POSITIONS["speedSetpointX"]["lx"],POSITIONS["speedSetpointX"]["ly"])
        app.addLabel("speedSetpointY", "0",POSITIONS["speedSetpointY"]["x"],POSITIONS["speedSetpointY"]["y"],POSITIONS["speedSetpointY"]["lx"],POSITIONS["speedSetpointY"]["ly"])
        app.addLabel("motorSetpointLabel", "Motors",POSITIONS["motorSetpointLabel"]["x"],POSITIONS["motorSetpointLabel"]["y"],POSITIONS["motorSetpointLabel"]["lx"],POSITIONS["motorSetpointLabel"]["ly"])
        app.addLabel("motorSetpointX", "0",POSITIONS["motorSetpointX"]["x"],POSITIONS["motorSetpointX"]["y"],POSITIONS["motorSetpointX"]["lx"],POSITIONS["motorSetpointX"]["ly"])
        app.addLabel("motorSetpointY", "0",POSITIONS["motorSetpointY"]["x"],POSITIONS["motorSetpointY"]["y"],POSITIONS["motorSetpointY"]["lx"],POSITIONS["motorSetpointY"]["ly"])
        
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




   