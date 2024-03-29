/*! \file sensorDriver.h
\brief Header of the sensor driver for the mouse treadmil project.

\author Didier Negretto
*/
#pragma once

#ifndef SENSORDRIVER_H_
#define SENSORDRIVER_H_

#ifndef TEST
#include "main.h"
#include "mavlink.h"
#include "sensorSROM.h"
#endif

/* BEGIN DEFINES FOR SENSOR INTERNAL REGISTERS */
#define Product_ID  0x00
#define Revision_ID 0x01
#define Motion  0x02
#define Delta_X_L 0x03
#define Delta_X_H 0x04
#define Delta_Y_L 0x05
#define Delta_Y_H 0x06
#define SQUAL 0x07
#define Raw_Data_Sum  0x08
#define Maximum_Raw_data  0x09
#define Minimum_Raw_data  0x0A
#define Shutter_Lower 0x0B
#define Shutter_Upper 0x0C
#define Control 0x0D
#define Config1 0x0F
#define Config2 0x10
#define Angle_Tune  0x11
#define Frame_Capture 0x12
#define SROM_Enable 0x13
#define Run_Downshift 0x14
#define Rest1_Rate_Lower  0x15
#define Rest1_Rate_Upper  0x16
#define Rest1_Downshift 0x17
#define Rest2_Rate_Lower  0x18
#define Rest2_Rate_Upper  0x19
#define Rest2_Downshift 0x1A
#define Rest3_Rate_Lower  0x1B
#define Rest3_Rate_Upper  0x1C
#define Observation 0x24
#define Data_Out_Lower  0x25
#define Data_Out_Upper  0x26
#define Raw_Data_Dump 0x29
#define SROM_ID 0x2A
#define Min_SQ_Run  0x2B
#define Raw_Data_Threshold  0x2C
#define Config5 0x2F
#define Power_Up_Reset  0x3A
#define Shutdown  0x3B
#define Inverse_Product_ID  0x3F
#define LiftCutoff_Tune3  0x41
#define Angle_Snap  0x42
#define LiftCutoff_Tune1  0x4A
#define Motion_Burst  0x50
#define LiftCutoff_Tune_Timeout 0x58
#define LiftCutoff_Tune_Min_Length  0x5A
#define SROM_Load_Burst 0x62
#define Lift_Config 0x63
#define Raw_Data_Burst  0x64
#define LiftCutoff_Tune2  0x65
/* END DEFINES FOR SENSOR INTERNAL REGISTERS */

#include <mavlink_msg_raw_sensor.h>
#include <stdint.h>

/* DEFINES FOR BURST READ (only usefull data) */
#define MOTION 0
#define OBSERVATION 1
#define DELTA_X_L 2
#define DELTA_X_H 3
#define DELTA_Y_L 4
#define DELTA_Y_H 5
#define SQUAL_READ 6

/*!
\def SQUAL_THRESH
\brief Threshold value on SQUAL to consider the measure valid.
*/
#define SQUAL_THRESH 16

/*!
\def RESOLUTION
\brief Resolution of the sensor in Count per Inch (CPI)
\note This value needs to be updated if the resolution of the sensors is changed,

This value is used to convert the raw sensor value in counts to meter per second.
*/
#define RESOLUTION 5000

/*!
\def INCH2METER
\brief Conversion factor to convert inches in meters.
*/
#define INCH2METER 0.0254

/*!
\fn sensorDriver_init
\brief Initializes all sensors.

This functions powers down the sensor and does the powering up routine.
\note This routine takes a long time, so it is done only at start up.
*/
void sensorDriver_init(void);

/*!
\fn sensorDriver_motion_read_speed(mavlink_raw_sensor_t sensor_data[2], mavlink_speed_info_t * speed_info)
\param sensor_data[2] array for the raw values of the 2 sensors
\param speed_info pointer to a mavlink_speed_info_t
\brief Function for reading the raw data and speed measures from the sensors.
\attention The speed_info.time_x/y is used to compute speed. This value should NOT BE MODIFIED by
the caller function

This function reads values from the sensors and puts them in the given pointers.
It also flags invalid readings, so that \ref mouseDriver_control_idle do not use them.
*/
void sensorDriver_motion_read_speed(mavlink_raw_sensor_t sensor_data[2], mavlink_speed_info_t * speed_info);

#endif
