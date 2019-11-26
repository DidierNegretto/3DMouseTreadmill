/*! \file mouseDriver.h
\brief Header of the driver for the mouse treadmil project.

\author Didier Negretto
*/

/*
 * Code used for driving the 3D mouse treadmill
 * Author: Didier Negretto
 *
 */

#pragma once
#ifndef MOUSEDRIVER_N_H
/*!
\def MOUSEDRIVER_N_H
\brief To avoid double includes
*/
#define MOUSEDRIVER_N_H

#ifndef TEST
#include "mavlink.h"
#include "utils.h"
#include "sensorDriver.h"
#endif

#include <math.h>
/* Constants for MALINK functions*/

/*!
\def SYS_ID
\brief System ID for MAVLink
*/
#define SYS_ID 0
/*!
\def COMP_ID
\brief Component ID for MAVLink
*/
#define COMP_ID 0
/* maximum size of the trasmit buffer */
/*!
\def MAX_BYTE_BUFFER_SIZE
\brief MAX size of transmit buffer in bytes
*/
#define MAX_BYTE_BUFFER_SIZE 500

/*!
\def MAX_POINTS
\brief MAX amount of points that can be defined in AUTO mode
*/
#define MAX_POINTS 255


/*!
\fn mouseDriver_init
\brief Function that initializes the driver of the mouse treadmill.

This functions initialites the mouse treadmill driver. It initializes the sensors as well.
*/
void mouseDriver_init(void);



/*!
\fn mouseDriver_control_idle
\brief Function doing the control on the motors.
\attention This function is in charge of generating the control signals for the
motors. If it is modified, make sure to respect the specifications of the motor
to avoid damaging or destroing them !!

This function is called periodially to update the control signal for the motors.
*/
void mouseDriver_control_idle(void);

/*!
\fn mouseDriver_send_status_msg
\brief Function generating the signal for sending messages.

This function is called periodially to set the flag for sending status messages.
*/
void mouseDriver_send_status_msg(void);

/*!
\fn mouseDriver_readMsg(const mavlink_message_t msg)
\param msg MAVLink message to be decoded
\brief Function that reads one message.

This function is called in main.c. Depending on the received message different actions are taken.
*/
void mouseDriver_readMsg(const mavlink_message_t msg);

/*!
\fn mouseDriver_getTime
\return The actual time in ms from boot of the system.
\brief Function that gets the time of the system from boot.
*/
uint32_t mouseDriver_getTime (void);

/*!
\fn mouseDriver_idle
\brief Idle function for the mouse treadmill driver.
\note This function needs to be called periodically to ensure a correct behaviour.

This is the idle function of the mouse treadmill. It reads values from the sensors,
calls \ref mouseDriver_control_idle, and sends high frequency messages (not the status ones).
*/
void mouseDriver_idle (void);


#endif
