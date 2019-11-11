/*
 * sensorDriver.c
 *
 *  Created on: Nov 11, 2019
 *      Author: Didier
 */

# include "sensorDriver.h"

void sensorDriver_init(void){
	main_write_sensor(Config2, 0x20);
	main_write_sensor(SROM_Enable, 0x1d);
	for(int i = 0; i< firmware_length;i++){
		main_transmit_spi(firmware_data[i]);
	}
}
