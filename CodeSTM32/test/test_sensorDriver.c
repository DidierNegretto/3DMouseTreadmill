/*
 * test_sensorDriver.c
 *
 *  Created on: Nov 25, 2019
 *      Author: Didier
 */

#include "test_sensorDriver.h"
#include "mock_sensorDriver.h"
#include "display.h"
#include "sensorDriver.c"

bool test_sensorDriver_init(void){
    display(0,"TEST SENSOR DRIVER");
}
