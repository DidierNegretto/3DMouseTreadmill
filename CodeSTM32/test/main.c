/*
 * main.c
 *
 *  Created on: Nov 24, 2019
 *      Author: Didier
 */

#include "test_mouseDriver.h"
#include "test_sensorDriver.h"

int main(void){

    bool test = false;

    printf("=====================================================\n");
    printf("***********TESTING CODE FOR MOUSE TREADMILL *********\n");
    printf("=====================================================\n\n");
    printf("-----------------------------------------------------\n");
    printf("TESTING mouseDriver.c\n");
    printf("TESTING mouseDriver_init()\n");
    test = test_mouseDriver_init();
    printf("TESTING mouseDriver_idle()\n");
    test &= test_mouseDriver_idle();
    printf("TESTING mouseDriver_getTime()\n");
    test &= test_mouseDriver_getTime();
    printf("TESTING mouseDriver_send_status_msg()\n");
    test &= test_mouseDriver_send_status_msg();
    printf("TESTING mouseDriver_control_idle()\n");
    test &= test_mouseDriver_control_idle();

    /*printf("-----------------------------------------------------\n");
    printf("TESTING mouseDriver.c\n");
    if (! test_mouseDriver_init()) printf(RED"ERRORS IN mouseDriver_init\n"END);*/

    return 0;
}
