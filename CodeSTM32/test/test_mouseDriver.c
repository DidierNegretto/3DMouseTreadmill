/*
 * test_mouseDriver.c
 *
 *  Created on: Nov 24, 2019
 *      Author: Didier
 */
#include "test_mouseDriver.h"
#include "mock_mouseDriver.h"
#include "display.h"
#include "mouseDriver.c"


bool test_mouseDriver_init(void){

    bool test = 1;

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

    test &= display(actual_mode == 0, "actual_mode initialization");
    test &= display(actual_point == 0, "actual_point initialization");
    test &= display(actual_point_start_time == 0, "actual_point_start_time initialization");
    test &= display((actual_speed_setpoint.setpoint_y  == 0)&& (actual_speed_setpoint.setpoint_x  == 0), "actual_speed_setpoint initialization");
    bool test_sub = 1;
    for(int i = 0; i < MAX_POINTS; i++){
        test_sub &= ((points[i].duration == 0) && (points[i].setpoint_x == 0) &&
                    (points[i].setpoint_y == 0) && (points[i].point_id == 0));
    }
    test &= display(test_sub, "points initialized correctly");
    test &= display(sensor_init == 1, "sensor_init initialization");
    test &= display(stop_motor == 1, "stop_motor initialization");
    test &= display((actual_motor_signal.motor_x  == 0)&& (actual_motor_signal.motor_y  == 0), "actual_motor_signal initialization");

    return test;
}

bool test_mouseDriver_idle(void){
    bool test = false;
    actual_speed_measure.speed_x = -10;
    actual_speed_measure.speed_y = -10;
    actual_speed_measure.valid = 1;
    actual_speed_setpoint.setpoint_x = MAX_MOTOR_SIGNAL * 1000;
    actual_speed_setpoint.setpoint_y = MAX_MOTOR_SIGNAL * 1000;
    actual_point_start_time = 0;
    actual_point = 0;
    points[0].duration = 100;
    points[0].setpoint_x = 10;
    points[0].setpoint_y = 10;
    points[0].point_id = 0;

    /* Test reading of sensors in SPEED mode */
    actual_mode = MOUSE_MODE_SPEED;
    sensor_read_x = 0;
    sensor_read_y = 0;
    stop_motor = 1;
    mouseDriver_idle();
    test = display(sensor_read_x == 1, "read sensor x in MOUSE_MODE_SPEED");
    test &= display(sensor_read_y == 1, "read sensor y in MOUSE_MODE_SPEED");
    test &= display(stop_motor == 0, "motor started in MOUSE_MODE_SPEED");

    /* Test reading of sensors in MOUSE_MODE_AUTO_RUN mode */
    actual_mode = MOUSE_MODE_AUTO_RUN;
    sensor_read_x = 0;
    sensor_read_y = 0;
    stop_motor = 1;
    mouseDriver_idle();
    test &= display(sensor_read_x == 1, "read sensor x in MOUSE_MODE_AUTO_RUN");
    test &= display(sensor_read_y == 1, "read sensor y in MOUSE_MODE_AUTO_RUN");
    test &= display(stop_motor == 0, "motor started in MOUSE_MODE_AUTO_RUN");
    return test;
}
bool test_mouseDriver_getTime(void){
    bool test = 1;
    uint32_t start = HAL_GetTick();
    test &= mouseDriver_getTime() == start+1;
    test &= mouseDriver_getTime() == start+2;
    test &= mouseDriver_getTime() == start+3;
    test &= mouseDriver_getTime() == start+4;
    test &= mouseDriver_getTime() == start+5;
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
    bool test = 1;
    stop_motor = 0;
    actual_speed_measure.speed_x = -10;
    actual_speed_measure.speed_y = -10;
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
    actual_motor_signal.motor_x = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_y = MAX_MOTOR_SIGNAL * 1000;
    printf("if (actual_mode ==  MOUSE_MODE_SPEED)\n");
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_x speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display(actual_motor_signal.motor_x <= MAX_MOTOR_SIGNAL, "motor_x with MAX_MOTOR_SIGNAL limit");

    stop_motor = 1;
    actual_speed_setpoint.setpoint_x = 0;
    actual_speed_setpoint.setpoint_y = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_x = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_y = MAX_MOTOR_SIGNAL * 1000;
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_y speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display(actual_motor_signal.motor_y <= MAX_MOTOR_SIGNAL, "motor_y with MAX_MOTOR_SIGNAL limit");

    actual_speed_setpoint.setpoint_x = MAX_MOTOR_SIGNAL * 1000;
    actual_speed_setpoint.setpoint_y = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_x = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_y = MAX_MOTOR_SIGNAL * 1000;
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_y and motor_x speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display((actual_motor_signal.motor_y <= MAX_MOTOR_SIGNAL) && (actual_motor_signal.motor_x <= MAX_MOTOR_SIGNAL), "motor_y and motor_x with MAX_MOTOR_SIGNAL limit");

    /* Reaction to invalid measures */
    actual_speed_setpoint.setpoint_x = 0;
    actual_speed_setpoint.setpoint_y = 0;
    actual_speed_measure.speed_x = 1000;
    actual_speed_measure.speed_y = 1000;
    actual_motor_signal.motor_x = 10;
    actual_motor_signal.motor_y = 10;
    bool test_stop = true;
    actual_speed_measure.valid = 0;
    for(int i = 0;i < MAX_MISSING_MEASURES-1; i++ ){
        test_stop &= (actual_motor_signal.motor_x == 10);
        test_stop &= (actual_motor_signal.motor_y == 10);
        mouseDriver_control_idle();
    }
    mouseDriver_control_idle();
    test &= display(test_stop, "constant motor signal if invalid measure");
    test &= display(actual_mode == MOUSE_MODE_STOP, "stop motor after too many invalid measures");



    /* Case actual mode == SPEED */
    actual_mode = MOUSE_MODE_AUTO_RUN;
    stop_motor = 1;
    actual_speed_setpoint.setpoint_y = 0;
    actual_speed_setpoint.setpoint_x = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_x = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_y = MAX_MOTOR_SIGNAL * 1000;
    actual_speed_measure.valid = 1;
    printf("if (actual_mode ==  MOUSE_MODE_AUTO_RUN)\n");
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_x speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display(actual_motor_signal.motor_x <= MAX_MOTOR_SIGNAL, "motor_x with MAX_MOTOR_SIGNAL limit");

    stop_motor = 1;
    actual_speed_setpoint.setpoint_x = 0;
    actual_speed_setpoint.setpoint_y = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_x = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_y = MAX_MOTOR_SIGNAL * 1000;
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_y speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display(actual_motor_signal.motor_y <= MAX_MOTOR_SIGNAL, "motor_y with MAX_MOTOR_SIGNAL limit");

    actual_speed_setpoint.setpoint_x = MAX_MOTOR_SIGNAL * 1000;
    actual_speed_setpoint.setpoint_y = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_x = MAX_MOTOR_SIGNAL * 1000;
    actual_motor_signal.motor_y = MAX_MOTOR_SIGNAL * 1000;
    mouseDriver_control_idle();
    test &= display(stop_motor == 0, "motor_y and motor_x speed changed");
    for(int i = 0; i < 100; i++)
        mouseDriver_control_idle();
    test &= display((actual_motor_signal.motor_y <= MAX_MOTOR_SIGNAL) && (actual_motor_signal.motor_x <= MAX_MOTOR_SIGNAL), "motor_y and motor_x with MAX_MOTOR_SIGNAL limit");

    test_stop = true;
    actual_speed_measure.valid = 0;
    actual_motor_signal.motor_x = 10;
    actual_motor_signal.motor_y = 10;
    for(int i = 0;i < MAX_MISSING_MEASURES-1; i++ ){
        test_stop &= (actual_motor_signal.motor_x == 10);
        test_stop &= (actual_motor_signal.motor_y == 10);
        mouseDriver_control_idle();
    }
    mouseDriver_control_idle();
    test &= display(test_stop, "constant motor signal if invalid measure");
    test &= display(actual_mode == MOUSE_MODE_STOP, "stop motor after too many invalid measures");

    return test;
}

