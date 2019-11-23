/*
 * sensorDriver.c
 *
 *  Created on: Nov 11, 2019
 *      Author: Didier
 */

# include "sensorDriver.h"

/* Define sensors */
static sensor_t sensor_x = {CS_0_GPIO_Port,CS_0_Pin,PW_0_GPIO_Port,PW_0_Pin,0};
static sensor_t sensor_y = {CS_1_GPIO_Port,CS_1_Pin,PW_1_GPIO_Port,PW_1_Pin,0};

/* PRIVATE functions */
void sensorDriver_powerup(sensor_t sensor){
	/* Disable the sensor */
	HAL_GPIO_WritePin(sensor.cs_port, sensor.cs_pin, GPIO_PIN_SET);

	/* Make sure all sensor is switched off */
	HAL_GPIO_WritePin(sensor.pw_port, sensor.pw_pin, GPIO_PIN_RESET);
	main_write_sensor(sensor, 0x00, 0x00);
	HAL_Delay(100);

	/* Gives voltage to sensors */
	HAL_GPIO_WritePin(sensor.pw_port, sensor.pw_pin , GPIO_PIN_SET);
	HAL_Delay(300);

	/* Reset SPI port */
	HAL_GPIO_WritePin(sensor.cs_port, sensor.cs_pin,  GPIO_PIN_SET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(sensor.cs_port, sensor.cs_pin,  GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(sensor.cs_port, sensor.cs_pin,  GPIO_PIN_SET);
	HAL_Delay(5);

	/* Write to Power_up_Reset register */
	main_write_sensor(sensor, Power_Up_Reset, 0x5A);

	/* Wait at least 50 ms */
	HAL_Delay(50);

	/* Read from data registers */
	main_read_sensor(sensor, 0x02);
	main_read_sensor(sensor, 0x03);
	main_read_sensor(sensor, 0x04);
	main_read_sensor(sensor, 0x05);
	main_read_sensor(sensor, 0x06);

	/* Start ROM Download */
	main_write_sensor(sensor, Config2, 0x20);
	main_write_sensor(sensor, SROM_Enable, 0x1d);
	HAL_Delay(10);
	main_write_sensor(sensor,SROM_Enable, 0x18);
	main_wait_160us();
	main_wait_20us();

	/* Burst start with adress */
	HAL_GPIO_WritePin(sensor.cs_port, sensor.cs_pin, GPIO_PIN_RESET);
	main_write_sensor_burst(SROM_Load_Burst|0x80);
	for (int i = 0; i < firmware_length; i++ ){
		main_write_sensor_burst(firmware_data[i]);
	}
	HAL_GPIO_WritePin(sensor.cs_port, sensor.cs_pin, GPIO_PIN_SET);
	main_wait_160us();
	main_wait_20us();
	main_wait_20us();

	/* Read SROM_ID for verification */
	sensor.status = main_read_sensor(sensor, SROM_ID);

	/* Write to Config2 for wired mouse */
	main_write_sensor(sensor, Config2, 0x00);
}

/* Public functions */
void sensorDriver_init(void){
	sensorDriver_powerup(sensor_x);
	sensorDriver_powerup(sensor_y);
}

void sensorDrive_motion_read(uint8_t sensor_id, mavlink_raw_sensor_t * sensor_data){
	uint8_t data[12];
	int16_t temp = 0;
	sensor_t sensor;

	if (sensor_id == SENSOR_X) sensor = sensor_x;
	else if (sensor_id == SENSOR_Y) sensor = sensor_y;
	else return;
	sensor_data->sensor_id = sensor_id;

	/* write to motion burst adress */
	main_write_sensor(sensor, Motion_Burst, 0xbb);

	/* Prepare for burst */
	HAL_GPIO_WritePin(sensor.cs_port, sensor.cs_pin, GPIO_PIN_RESET);
	sensor_data->time = mouseDriver_getTime();
	main_write_sensor_burst(Motion_Burst);
	/* Start burst */
	main_read_sensor_motion_burst(data);
	HAL_GPIO_WritePin(sensor.cs_port, sensor.cs_pin, GPIO_PIN_SET);
	/* END of burst */
	main_wait_20us();

	/* Read other register for stopping burst mode */
	sensor_data->product_id = main_read_sensor(sensor,  Product_ID);

	/* TWO's Complement */
	temp = (data[DELTA_X_H]<<8) | (data[DELTA_X_L]);
	temp = ~temp + 1;
	sensor_data->delta_x = temp;
	temp = (data[DELTA_Y_H]<<8) | (data[DELTA_Y_L]);
	temp = ~temp +1;
	sensor_data->delta_y = temp;

	sensor_data->squal = data[SQUAL_READ];
	sensor_data->lift = (data[MOTION] & 0x08) >> 3;
}
