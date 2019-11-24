/*
 * mock_mouseDriver.h
 *
 *  Created on: Nov 24, 2019
 *      Author: Didier
 */

#ifndef MOCK_MOUSEDRIVER_H_
#define MOCK_MOUSEDRIVER_H_

static int stop_motor = 0;
static int sensor_init = 0;

/* Define mock functions */
void sensorDriver_init(void){sensor_init = 1; };
uint32_t HAL_GetTick(void){
    static uint32_t i = 0;
    i++;
    return i;
};

void main_set_motors_speed(mavlink_motor_setpoint_t actual_motor_signal){stop_motor = 0;};
void main_stop_motors(void){stop_motor = 1;};
void sensorDrive_motion_read(uint8_t sensor_id, mavlink_raw_sensor_t * sensor_data){};
void mouseDriver_sendMsg(uint32_t msgid){};


#endif /* MOCK_MOUSEDRIVER_H_ */
