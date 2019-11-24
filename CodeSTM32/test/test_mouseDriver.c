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
    actual_motor_signal.motor_x = 10;
    actual_motor_signal.motor_y = 10;

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
    test &= display((actual_motor_signal.motor_x  == 0)&& (actual_motor_signal.motor_y  == 0), "actual_motor_signal initialization");

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
bool test_mouseDriver_control_idle(void){
    bool test = false;
    stop_motor = 0;
    actual_motor_signal.motor_x = 10;
    actual_motor_signal.motor_y = 10;
    actual_mode = MOUSE_MODE_STOP;

    /* Case actual mode == STOP */
    printf("if (actual_mode ==  MOUSE_MODE_STOP)\n");
    mouseDriver_control_idle();
    test &= display((actual_motor_signal.motor_x  == 0)&& (actual_motor_signal.motor_y  == 0), "actual_motor_signal reset");
    test &= display(stop_motor == 1, "motor stop");

    /* Case actual mode == SPEED */
    actual_mode = MOUSE_MODE_SPEED;
    stop_motor = 1;
    actual_speed_setpoint.setpoint_y = 0;
    actual_speed_setpoint.setpoint_x = MAX_MOTOR_SIGNAL * 1000;
    printf("if (actual_mode ==  MOUSE_MODE_SPEED)\n");
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_x speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display(actual_motor_signal.motor_x <= MAX_MOTOR_SIGNAL, "motor_x with MAX_MOTOR_SIGNAL limit");

    stop_motor = 1;
    actual_speed_setpoint.setpoint_x = 0;
    actual_speed_setpoint.setpoint_y = MAX_MOTOR_SIGNAL * 1000;
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_y speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display(actual_motor_signal.motor_y <= MAX_MOTOR_SIGNAL, "motor_y with MAX_MOTOR_SIGNAL limit");

    actual_speed_setpoint.setpoint_x = MAX_MOTOR_SIGNAL * 1000;
    actual_speed_setpoint.setpoint_y = MAX_MOTOR_SIGNAL * 1000;
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_y and motor_x speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display((actual_motor_signal.motor_y <= MAX_MOTOR_SIGNAL) && (actual_motor_signal.motor_x <= MAX_MOTOR_SIGNAL), "motor_y and motor_x with MAX_MOTOR_SIGNAL limit");

    /* Case actual mode == SPEED */
    actual_mode = MOUSE_MODE_AUTO_RUN;
    stop_motor = 1;
    actual_speed_setpoint.setpoint_y = 0;
    actual_speed_setpoint.setpoint_x = MAX_MOTOR_SIGNAL * 1000;
    printf("if (actual_mode ==  MOUSE_MODE_AUTO_RUN)\n");
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_x speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display(actual_motor_signal.motor_x <= MAX_MOTOR_SIGNAL, "motor_x with MAX_MOTOR_SIGNAL limit");

    stop_motor = 1;
    actual_speed_setpoint.setpoint_x = 0;
    actual_speed_setpoint.setpoint_y = MAX_MOTOR_SIGNAL * 1000;
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_y speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display(actual_motor_signal.motor_y <= MAX_MOTOR_SIGNAL, "motor_y with MAX_MOTOR_SIGNAL limit");

    actual_speed_setpoint.setpoint_x = MAX_MOTOR_SIGNAL * 1000;
    actual_speed_setpoint.setpoint_y = MAX_MOTOR_SIGNAL * 1000;
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_y and motor_x speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display((actual_motor_signal.motor_y <= MAX_MOTOR_SIGNAL) && (actual_motor_signal.motor_x <= MAX_MOTOR_SIGNAL), "motor_y and motor_x with MAX_MOTOR_SIGNAL limit");



    return test;
}


#endif /* TEST_MOUSEDRIVER_C_ */
