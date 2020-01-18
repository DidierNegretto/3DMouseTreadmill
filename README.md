#  3D MOUSE TREADMILL PROJECT
This is the readme that describes the code for the 3D mouse treadmill project at BIOROB, EPFL
First of all the code that is not provided by stm or mavlink or that has someother license is given under the GPL 3 license, which is 
copied below. The code given by stm or mavlink , which include the HAL libraries and the mavlink libraries
comes with its own license.

## GPL 3 License
3D mouse treadmill software

Copyright (C) 2020  Didier Negretto (didier.negretto@epfl.ch)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Folder structure
The folder structure is described below:

1. CodeSTM32: Contains all the code that runs on the stm32 nucleo
board except for the main. This folder is divided in two parts:
    1. src: which contains all the source code that is run on the stm32
    2. test: which contains all the source code for the unit tests

2. docs: this file contains the doxygen file as well as the html output 
produced by doxygen. There you can find all informations on the code and 
how to use it.

3. ARDUINO_signals: contains some files with the signals measured on the
pins of the sensors while in use. If the communication between the board and 
the sensors do not work anymore you can use them to compare.

4. mavlink: contains all the mavlink tools, such as the scripts to generate
new libraries in case you need to modify the one that is used now, as well as the
script to install the pymavlink. For more information on the subject refer to the
report and to https://mavlink.io/en/

5. MAVLink Library: contains the c libraries generated by mavgenerate.py.
If you need to change those libraries, make sure to generate them in the 
MAVLink Library folder.

6. MouseTreadmillPC/python: contains the code to be run on the PC. An extra script (gen_routine.py) to generate 
a routine in routine.py is provided as an exemple. This script can be improved for better 
perfomances in the machine. The plot.py script can be used as inpiration for reading
data from logs, log exemples are given in  MouseTreadmillPC/python/log

7. MouseTreadmillSTM32Project: contains the stm32CubeIDE project. The most important 
things are:
    1. MouseTreadmillSTM32Project/Core/Src/main.c: which is the main run on the 
    stm32.
    2. MouseTreadmillSTM32Project/Core/Inc/main.h: which is the main headers.

8. PCB: contains the PCB Altium documents, which can be used to continue the
design of the PCB.

9. report: contains the report of the semester project

10. resources: contains some usefull documents such as the sensor datasheet
as well as some HAL_library datasheets.

11. mouse.py: is the python library generated from mavlink. To use it correctly
see the report and https://mavlink.io/en/

12. README.md: what you are reading right now, I mean I hope you are reading
it otherwise you'll for sure get into troubles, lose a lot of time, which is
not good.

## Where to find other usefull information

If you need more information (which you do), please have a look at the 
report where you should be able to find useful information for using, improving and
extending this code. Another place thing that will help you is the docs/html/index.html,
which contains all the documetation of the existing code.




