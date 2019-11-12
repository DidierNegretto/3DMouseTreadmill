/*
 * sensorDriver.c
 *
 *  Created on: Nov 11, 2019
 *      Author: Didier
 */

# include "sensorDriver.h"

uint8_t sensorDriver_powerup(void){
	uint8_t value = 0;

	/* Disable the sensor */
	HAL_GPIO_WritePin(CS_0_GPIO_Port, CS_0_Pin, GPIO_PIN_SET);

	/* Make sure all sensor is switched off */
	HAL_GPIO_WritePin(PW_0_GPIO_Port, PW_0_Pin, GPIO_PIN_RESET);
	main_write_sensor(SENSOR_X, 0x00, 0x00);
	HAL_Delay(100);

	/* Gives voltage to sensors */
	HAL_GPIO_WritePin(PW_0_GPIO_Port, PW_0_Pin, GPIO_PIN_SET);
	HAL_Delay(300);

	/* Reset SPI port */
	HAL_GPIO_WritePin(CS_0_GPIO_Port, CS_0_Pin, GPIO_PIN_SET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(CS_0_GPIO_Port, CS_0_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(CS_0_GPIO_Port, CS_0_Pin, GPIO_PIN_SET);
	HAL_Delay(5);

	/* Write to Power_up_Reset register */
	main_write_sensor(SENSOR_X, Power_Up_Reset, 0x5A);

	/* Wait at least 50 ms */
	HAL_Delay(50);

	/* Read from data registers */
	main_read_sensor(SENSOR_X, 0x02);
	main_read_sensor(SENSOR_X, 0x03);
	main_read_sensor(SENSOR_X, 0x04);
	main_read_sensor(SENSOR_X, 0x05);
	main_read_sensor(SENSOR_X, 0x06);

	/* Start ROM Download */
	main_write_sensor(SENSOR_X, Config2, 0x20);
	main_write_sensor(SENSOR_X, SROM_Enable, 0x1d);
	HAL_Delay(10);
	main_write_sensor(SENSOR_X,SROM_Enable, 0x18);
	main_wait_160us();

	/* Burst start with adress */
	HAL_GPIO_WritePin(CS_0_GPIO_Port, CS_0_Pin, GPIO_PIN_RESET);
	main_write_sensor_burst(SROM_Load_Burst);
	for (int i = 0; i < firmware_length; i++ ){
		main_write_sensor_burst(firmware_data[i]);
	}
	HAL_GPIO_WritePin(CS_0_GPIO_Port, CS_0_Pin, GPIO_PIN_SET);
	main_wait_160us();
	main_wait_20us();
	main_wait_20us();

	/* Read SROM_ID for verification */
	value = main_read_sensor(SENSOR_X, SROM_ID);

	/* Write to Config2 for wired mouse */
	main_write_sensor(SENSOR_X, Config2, 0x00);
	return value;
}
void sensorDriver_init(void){
	sensorDriver_powerup();
	/*main_write_sensor(Config2, 0x20);
	main_write_sensor(SROM_Enable, 0x1d);
	for(int i = 0; i< firmware_length;i++){
		main_transmit_spi(firmware_data[i]);
	}*/
}
