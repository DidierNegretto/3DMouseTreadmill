/*
 * Code used for driving the 3D mouse treadmill
 * Author: Didier Negretto
 *
 */

#pragma once
#ifndef MOUSEDRIVER_N_H
#define MOUSEDRIVER_N_H

#include "mavlink.h"
#include "main.h"
#include "utils.h"

/* Constants for MALINK functions*/
#define SYS_ID 0
#define COMP_ID 0

/* maximum size of the trasmit buffer */
#define BUFFER_SIZE 50
/* time enlapsed between two calls to mouseDriver_controlISR in 0.1s */
#define DT 1
#define PRESCALER 8000
#define CLOCK_FREQ 80000000
#define COUNTER_PERIOD ((CLOCK_FREQ/(PRESCALER))*DT*0.1)


/* Function for initializing the mouseDriver*/
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
