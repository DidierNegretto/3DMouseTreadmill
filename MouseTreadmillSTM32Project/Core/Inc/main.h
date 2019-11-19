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
typedef struct SENSOR{
	GPIO_TypeDef * cs_port;
	uint8_t cs_pin;
	GPIO_TypeDef * pw_port;
	uint8_t pw_pin;
	uint8_t status;
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
void main_transmit_buffer(uint8_t *outBuffer, uint16_t msg_size);
void main_stop_motors(void);
void main_set_motors_speed(mavlink_motor_setpoint_t motor );
int main_get_huart_tx_state(void);
void main_write_sensor (sensor_t sensor, uint8_t adress, uint8_t data);
uint8_t main_read_sensor (sensor_t sensor, uint8_t adress );
void main_transmit_spi(uint8_t data);
void main_wait_160us(void);
void main_wait_20us(void);
void main_write_sensor_burst(uint8_t data);
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
#define PRESCALER_PWM 9
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
