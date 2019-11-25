/*
 * mock_sensorDriver.h
 *
 *  Created on: Nov 25, 2019
 *      Author: Didier
 */

#ifndef MOCK_SENSORDRIVER_H_
#define MOCK_SENSORDRIVER_H_

typedef struct SENSOR{
    int cs_port;
    uint8_t cs_pin;
    int pw_port;
    uint8_t pw_pin;
    uint8_t status;
} sensor_t;

#define CS_0_GPIO_Port 0
#define CS_0_Pin 0
#define PW_0_GPIO_Port 0
#define PW_0_Pin 0

#define CS_1_GPIO_Port 1
#define CS_1_Pin 1
#define PW_1_GPIO_Port 1
#define PW_1_Pin 1

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0

static int firmware_length = 3;
static int firmware_data[3] = {1,2,3};

static inline void main_wait_160us(void){};
static inline void main_wait_20us(void){};
static inline uint8_t main_read_sensor(sensor_t sensor, uint8_t adress ){return adress;};
static inline void main_write_sensor(sensor_t sensor, uint8_t adress, uint8_t value){};
static inline void main_read_sensor_motion_burst(uint8_t* buffer){};
static inline void main_write_sensor_burst(uint8_t adress){};
static inline void HAL_Delay(int delay){};
static inline void HAL_GPIO_WritePin(int port, int pin, int state){};
static inline uint32_t mouseDriver_getTime(void){
   static uint32_t i = 0;
   i++;
   return i;
}

#endif /* MOCK_SENSORDRIVER_H_ */
