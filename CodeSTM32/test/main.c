/*! \file main.c
\brief Main for unit testss
\author Didier Negretto

This main is compiled and run after the compilation of the stm32 project
This main runs the unit tests and prints which tests are passed and which are not
\attention  The bash script for the automatic unit testing after compilation
was written for MAC and may not work on LINUX or Windows. To solve this issue
modify CodeSTM32/src/build.sh
*/

#include "test_mouseDriver.h"
#include "test_sensorDriver.h"

int main(void){

    bool test = 1;

    printf("=====================================================\n");
    printf("***********TESTING CODE FOR MOUSE TREADMILL *********\n");
    printf("=====================================================\n\n");
    printf("-----------------------------------------------------\n");
    printf("TESTING mouseDriver.c\n");
    printf("TESTING mouseDriver_init()\n");
    test &= test_mouseDriver_init();
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


    if (test == 1){
        printf("ALL TEST PASSED SUCCESSUFULLY\n");
    }
    else{
        printf("=====================================================\n");
        printf("!!!!!!!!!!!! SOME TESTS NOT PASSED !!!!!!!!!!!!!!!!!!\n");
        printf("=====================================================\n\n");

    }
    return test;
}
