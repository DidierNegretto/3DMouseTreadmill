/*
 * test.h
 *
 *  Created on: Nov 24, 2019
 *      Author: Didier
 */

#ifndef TEST_MOUSEDRIVER_H_
#define TEST_MOUSEDRIVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "mavlink.h"

/* Define testing functions*/
bool test_mouseDriver_init(void);
bool test_mouseDriver_idle(void);
bool test_mouseDriver_getTime(void);
bool test_mouseDriver_send_status_msg(void);
bool test_mouseDriver_control_idle(void);

#endif /* TEST_MOUSEDRIVER_H_ */
