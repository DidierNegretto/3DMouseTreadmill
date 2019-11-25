/*
 * mock_mouseDriver.h
 *
 *  Created on: Nov 24, 2019
 *      Author: Didier
 */

#ifndef MOCK_MOUSEDRIVER_H_
#define MOCK_MOUSEDRIVER_H_

#define HAL_BUSY  0
#define SYS_ID 0
#define COMP_ID 0
#define MAX_BYTE_BUFFER_SIZE 500
#define MAX_POINTS 255


static int stop_motor = 0;
static int sensor_init = 0;
static int sensor_read_x = 0;
static int sensor_read_y = 0;


/* Define mock functions */
void sensorDriver_init(void){sensor_init = 1; };
uint32_t HAL_GetTick(void){
    static uint32_t i = 0;
    i++;
    return i;
};
void main_set_motors_speed(mavlink_motor_setpoint_t actual_motor_signal){stop_motor = 0;};
void main_stop_motors(void){stop_motor = 1;};
void sensorDrive_motion_read(uint8_t sensor_id, mavlink_raw_sensor_t * sensor_data){
    if (sensor_id == SENSOR_X){
        sensor_read_x = 1;
    }
    if (sensor_id == SENSOR_Y){
        sensor_read_y = 1;
    }
    actual_raw_sensor->delta_x = 0;
    actual_raw_sensor->delta_y = 0;

};
int main_get_huart_tx_state(void){
    return 1;
}

void HAL_Delay(int delay){
    return;
}
void main_transmit_buffer(uint8_t * outbuffer, int msg_size){};
#endif /* MOCK_MOUSEDRIVER_H_ */