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

/* Define mock functions */
static inline void sensorDriver_init(void){sensor_init = 1; };
static inline uint32_t HAL_GetTick(void){
    static uint32_t i = 0;
    i++;
    return i;
};
static inline void main_set_motors_speed(mavlink_motor_setpoint_t actual_motor_signal){stop_motor = 0;};
static inline void main_stop_motors(void){stop_motor = 1;};
static inline void sensorDrive_motion_read(uint8_t sensor_id, mavlink_raw_sensor_t * sensor_data){
    if (sensor_id == SENSOR_X){
        sensor_read_x = 1;
    }
    if (sensor_id == SENSOR_Y){
        sensor_read_y = 1;
    }
    actual_raw_sensor->delta_x = 0;
    actual_raw_sensor->delta_y = 0;

};
static inline int main_get_huart_tx_state(void){
    return 1;
}

static inline void HAL_Delay(int delay){
    return;
}
static inline void main_transmit_buffer(uint8_t * outbuffer, int msg_size){};

#endif /* MOCK_MOUSEDRIVER_H_ */
