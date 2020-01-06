/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mouseDriver.h"
#include "mavlink.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/**
 * A structure to represent one sensor
 */
typedef struct SENSOR{
  /*@{*/
	GPIO_TypeDef * cs_port; /**< the chip select port for the sensor */
	uint8_t cs_pin; /**< the chip select pin for the sensor */
	GPIO_TypeDef * pw_port; /**< the power port for the sensor */
	uint8_t pw_pin; /**< the power pin for the sensor */
	uint8_t status; /**< the sensor status. This is the SROM_ID after the upload of the
  firmware. This value should not be 0 otherwise the upload of the SROM is failed. */
  /*@}*/
} sensor_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/*!
\fn main_transmit_buffer(uint8_t *outBuffer, uint16_t msg_size)
\param outBuffer buffer to be transmitted over UART
\param msg_size size of the buffer
\brief This function sends the buffer using UART.

\attention The transmission is done using a DMA. Before sending a message 
it is important to check that the previous one has been sent. This can be done 
using \ref main_get_huart_tx_state .
*/
void main_transmit_buffer(uint8_t *outBuffer, uint16_t msg_size);
/*!
\fn main_stop_motors()
\brief This function stops the motors

The PWM duty cycle is set to 0% for the two motors
\note The PWM duty cycle is represented by a uint type. 
The min/max of that value are defined by how the timer is 
setup in the microcontroller. The max value can be limited
by limitations in the motors or in the mechanical build of the 
machine 
*/
void main_stop_motors(void);
/*!
\fn main_set_motors_speed(mavlink_motor_setpoint_t motor )
\param motor PWM duty cycle for the two motors 
\brief This sets the motor duty cycle to one specified in the
motor parameter

The PWM duty cycle is set to 0% for the two motors
\note The PWM duty cycle is represented by a uint type. 
The min/max of that value are defined by how the timer is 
setup in the microcontroller. The max value can be limited
by limitations in the motors or in the mechanical build of the 
machine 
*/ 
void main_set_motors_speed(mavlink_motor_setpoint_t motor );
/*!
\fn main_get_huart_tx_state()
\return the HAL_state of UART transmit
\brief Function used to verify if the channel for writing the buffer is available or busy.
*/
int main_get_huart_tx_state(void);
/*!
\fn main_write_sensor(sensor_t sensor, uint8_t adress, uint8_t data)
\param sensor sensor to which we want to write
\param adress adress of the register to be modified
\param data data to written in the given sensor and register
\brief This function writes a byte in a given register of a given sensor.

\note The writing is done by generating proper signals in the pins. For more details
on the sensor register and timing diagrams see resources/sensorDatasheet.pdf
*/
void main_write_sensor (sensor_t sensor, uint8_t adress, uint8_t data);
/*!
\fn main_read_sensor(sensor_t sensor, uint8_t adress)
\param sensor sensor from which we want to read
\param adress adress of the register to be read
\return the value in the given register and sensor
\brief This function reads a byte in a given register of a given sensor.

\note The reading is done by generating proper signals in the pins. For more details
on the sensor register and timing diagrams see resources/sensorDatasheet.pdf
*/
uint8_t main_read_sensor (sensor_t sensor, uint8_t adress );
/*!
\deprecated
\fn main_transmit_spi(uint8_t data)
\param data data to be transmitted on the spi2
\brief This function transmit one byte on the spi2 
*/
void main_transmit_spi(uint8_t data);
/*!
\fn main_wait_160us()
\brief function used to wait around 160 [us].
\note the wait is achieved by toggling the green LED.
*/
void main_wait_160us(void);
/*!
\fn main_wait_20us()
\brief function used to wait around 20 [us].
\note the wait is achieved by toggling the green LED.
*/
void main_wait_20us(void);
/*!
\fn main_write_sensor_burst(uint8_t data)
\param data by to be written during the burst
\brief function used during a write burst
\attention Use this function only during a burst write.
*/
void main_write_sensor_burst(uint8_t data);
/*!
\fn main_read_sensor_motion_burst(uint8_t *data )
\param data pointer on a table of uint8_t used to store the
data read from a motion read burst
\brief function used to do a burst read for the motion read burst
as specified in resources/resources/sensorDatasheet.pdf

\attention Use this function only during a motion read burst.
\note The data received from the motion read burst are raw datas and have
to be treated to obtain meaningfull values and verify that the sensor is not
lifted and the surface quality is good enough to consider the measure as valid.
*/
void main_read_sensor_motion_burst(uint8_t *data );
/*
 * PW_0 is power pin for sensor X	(PB_0)
 * PW_1 is the power pin for sensor Y (PA_4)
 * CS_0 is the chip select for sensor X (PC_0)
 * CS_1 is the chip select for sensor Y (PC_1)
 */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DT_HEART 200
#define PRESCALER_HEART 1000
#define CLOCK_FREQ 80000000
#define COUNTER_PERIOD_HEART ((CLOCK_FREQ/(PRESCALER_HEART))*0.001*DT_HEART)
#define PRESCALER_PWM 1000
#define COUNTER_PERIOD_PWM 255
#define PULSE_PWM 10
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define CS_0_Pin GPIO_PIN_0
#define CS_0_GPIO_Port GPIOC
#define CS_1_Pin GPIO_PIN_1
#define CS_1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define PW_1_Pin GPIO_PIN_4
#define PW_1_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define PW_0_Pin GPIO_PIN_0
#define PW_0_GPIO_Port GPIOB
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
