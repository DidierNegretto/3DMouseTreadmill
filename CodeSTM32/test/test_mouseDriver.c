/*
 * test_mouseDriver.c
 *
 *  Created on: Nov 24, 2019
 *      Author: Didier
 */

#ifndef TEST_MOUSEDRIVER_C_
#define TEST_MOUSEDRIVER_C_


#include "test_mouseDriver.h"
#include "mock_mouseDriver.h"
#include "display.h"
#include "mouseDriver.c"


bool test_mouseDriver_init(void){

    bool test = false;

    actual_mode = 5;
    for(int i = 0; i < MAX_POINTS; i++){
        points[i].duration = i;
        points[i].setpoint_x = i;
        points[i].setpoint_y = i;
        points[i].point_id = i;
    }
    actual_point = 10;
    actual_point_start_time = 10;
    actual_speed_setpoint.setpoint_x = 10;
    actual_speed_setpoint.setpoint_y = 10;
    sensor_init = 0;
    stop_motor = 0;

    mouseDriver_init();

    test = display(actual_mode == 0, "actual_mode initialization");
    test &= display(actual_point == 0, "actual_point initialization");
    test &= display(actual_point_start_time == 0, "actual_point_start_time initialization");
    test &= display((actual_speed_setpoint.setpoint_y  == 0)&& (actual_speed_setpoint.setpoint_x  == 0), "actual_speed_setpoint initialization");
    for(int i = 0; i < MAX_POINTS; i++){
        test &= ((points[i].duration == 0) && (points[i].setpoint_x == 0) &&
                    (points[i].setpoint_y == 0) && (points[i].point_id == 0));
    }
    test &= display(sensor_init == 1, "sensor_init initialization");
    test &= display(stop_motor == 1, "stop_motor initialization");

    return test;
}

bool test_mouseDriver_idle(void){
    bool test = false;
    /* TO DO */
    return test;
}
bool test_mouseDriver_getTime(void){
    bool test = false;

    test = mouseDriver_getTime() == 1;
    test &= mouseDriver_getTime() == 2;
    test &= mouseDriver_getTime() == 3;
    test &= mouseDriver_getTime() == 4;
    test &= mouseDriver_getTime() == 5;
    display(test, "time update");

    return test;
}
bool test_mouseDriver_send_status_msg(void){
    bool test = false;
    send_msg = 0;

    mouseDriver_send_status_msg();

    test = send_msg;
    display(test, "status message send request");
    return test;
}


#endif /* TEST_MOUSEDRIVER_C_ */
