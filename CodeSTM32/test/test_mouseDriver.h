/*
 * test.h
 *
 *  Created on: Nov 24, 2019
 *      Author: Didier
 */

#ifndef TEST_MOUSEDRIVER_H_
#define TEST_MOUSEDRIVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "mavlink.h"


#define MAX_POINTS 255

/* Define mock variables for testing */
static int send_msg = 1;
static uint8_t actual_mode = MOUSE_MODE_STOP;
static mavlink_speed_setpoint_t actual_speed_setpoint;
static mavlink_speed_info_t actual_speed_measure;
static mavlink_motor_setpoint_t actual_motor_signal;
static mavlink_point_t points[255];
static uint8_t actual_point = 0;
static uint32_t actual_point_start_time = 0;
static mavlink_error_t actual_error;
static mavlink_raw_sensor_t actual_raw_sensor[2];


/* Define testing functions*/
bool test_mouseDriver_init(void);
bool test_mouseDriver_idle(void);
bool test_mouseDriver_getTime(void);
bool test_mouseDriver_send_status_msg(void);

#endif /* TEST_MOUSEDRIVER_H_ */
