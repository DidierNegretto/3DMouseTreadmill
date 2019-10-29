/*
 * Code used for driving the 3D mouse treadmill
 * Author: Didier Negretto
 *
 */

#pragma once
#ifndef MOUSEDRIVER_N_H
#define MOUSEDRIVER_N_H

#define SYS_ID 0
#define COMP_ID 0
#define BUFFER_SIZE 40

#include "mavlink.h"
#include "main.h"
#include "utils.h"

/* Function for initializing the mouseDriver*/
void mouseDriver_init(void);

/* Function for setting time in the mouseDriver, time is used for the timestamps */
void mouseDriver_setTime (const uint32_t time);

/* Function for getting the measured speed from the sensors */
mavlink_speed_info_t mouseDriver_getActualSpeed(void);

/* Function for setting the setpoint of the mouse treadmill */
void mouseDriver_setSetpoint(const mavlink_speed_setpoint_t speed);

/* Function for decoding a message */
void mouseDriver_readMsg(const mavlink_message_t msg);

/* Function for sending a specific message from ID */
void mouseDriver_sendMsg(uint32_t msgid);

#endif
