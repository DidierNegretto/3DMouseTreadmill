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

#include "mavlink.h"
#include "main.h"
#include "utils.h"

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
 \brief Function for initializing the mouseDriver

 This function initializes
 */
void mouseDriver_init(void);

/* Function for decoding a message */
void mouseDriver_readMsg(const mavlink_message_t msg);

/* Idle function for mouse driver. To be called in the while(1) loop */
void mouseDriver_idle (void);

/* Function called every DT for updating the control signals to motors */
void mouseDriver_controlISR(void);

/* Functions for setting/getting time */
void mouseDriver_setTime (const uint32_t time);
uint32_t mouseDriver_getTime (void);

#endif
