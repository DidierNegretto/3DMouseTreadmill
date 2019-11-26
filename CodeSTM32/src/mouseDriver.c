/*! \file mouseDriver.c
\brief Implementation of the driver for the mouse treadmil project.

\author Didier Negretto
*/
#ifndef MOUSEDRIVER_C_
#define MOUSEDRIVER_C_

#ifndef TEST
#include "mouseDriver.h"
#else
#include "../test/test_mouseDriver.h"
#endif
/*!
\def K 
\brief Proportional coefficient for motor control.
*/
#define K 10
/*!
\def K
\brief Proportional coefficient for motor control.
*/
#define I 10 
/*!
\def I 
\brief Integral coefficient for motor control.
*/
#define MAX_MOTOR_SIGNAL 100
/*!
\def MAX_MOTOR_SIGNAL
\brief Max value for the motor signal
\attention This value is used to limit the motor speed. If this is changed the motors might break !!

This value limits the motor speed and thus is used to vaoid spinning the motor too fast and break it.
If this value is changed the motor might spin too fast and destroy itself or the gear box. Extreme caution
needs to be taken if this value is modified.
*/
#define MIN_MOTOR_SIGNAL 10
/*!
\def MIN_MOTOR_SIGNAL
\brief Min value for the motor signal. Any value lower than that will cause the motor to stop
*/
#define MAX_MISSING_MEASURES 15
/*!
\def MAX_MISSING_MEASURES
\brief After MAX_MISSING_MEASURES non valid measures from sensors the motors are stopped and mode goes
to stop.
*/
#ifndef TEST
/*!
\var actual_mode
\brief Global variable defining the mode of the machine

This value is updated based on the received messages. When a routine is running it is
only possible to stop the machine.
*/
static uint8_t actual_mode = MOUSE_MODE_STOP;
/*!
\var actual_speed_measure
\brief Global variable for the measured speed

This value is updated based on sensor.
*/
static mavlink_speed_info_t actual_speed_measure;
/*!
\var actual_speed_setpoint
\brief Global variable for the speed setpoint

This value is updated based on messages when the mode is set to SPEED.
*/
static mavlink_speed_setpoint_t actual_speed_setpoint;
/*!
\var actual_motor_signal
\brief Global variable for the speed motor signal

This value is updated based on closed-loop control and the value provided in
\ref actual_speed_setpoint and \ref actual_speed_measure.
It is also possible to overwrite it by sending a mavlink_motor_setpoint_t message if the
mode is set to SPEED.
*/
static mavlink_motor_setpoint_t actual_motor_signal;
/*!
\var points
\brief Global variable for storing the points to be followed in AUTO mode

The maximum amout of points is defined by \ref MAX_POINTS. This array is emptied after
every reset of the system. If not all the points are defined the routine is interrupted as
soon as a point with duration == 0 is detected.
*/
static mavlink_point_t points[255];
/*!
\var actual_point
\brief Global variable for keeping track of the index in the \ref points array.
*/
static uint8_t actual_point = 0;
/*!
\var actual_point_start_time
\brief Global variable for keeping track of the time when the last point in \ref points array started.
*/
static uint32_t actual_point_start_time = 0;
/*!
\var actual_error
\brief Global variable to store and send the last error occured
*/
static mavlink_error_t actual_error;
/*!
\var actual_raw_sensor
\brief Global variable to store and send the row sensor values from X and Y sensors
*/
static mavlink_raw_sensor_t actual_raw_sensor[2];
/*!
\var send_msg
\brief Flag for sending status messages. Those messages are sent with lower freqency.
*/
static int send_msg = 1;
/*!
\fn mouseDriver_initSetpoint
\brief Function that initializes the setpoint to 0

This function modifies \ref actual_speed_setpoint by setting it to 0.
*/
#endif
/*!
\fn mouseDriver_sendMsg(uint32_t msgid)
\param msgid is the ID of the message to be sent.
\brief Function that sends a message given its ID.
\attention This function can be called in interrupts whith a priority lower than 0 (1,2,3,...),
otherwise the HAL_Delay() function stall and the STM32 crashes.

This function access global variables to send information to the computer.
Given one message ID the functions reads the information from a global variable and
sends it using the DMA as soon as the previous messages are sent.
*/
void mouseDriver_sendMsg(uint32_t msgid);
/*!
\fn mouseDriver_initSetpoint
\brief Function that initializes the motor setpoint to 0.

This function initializes \ref actual_speed_setpoint.
*/
void mouseDriver_initSetpoint(void);
/*!
\fn mouseDriver_initMode
\brief Function that initializes the mode to MOUSE_MODE_STOP

This function modifies \ref actual_mode by setting it to MOUSE_MODE_STOP.
*/
void mouseDriver_initMode(void);
/*!
\fn mouseDriver_initPoints
\brief Function that initializes the routine points for AUTO mode to 0.

This function modifies \ref points by setting all their fields to 0.
*/
void mouseDriver_initPoints(void);/*!
\fn mouseDriver_setMode(uint8_t mode)
\param mode is the mode in which the driver should be set.
\brief Function that sets the mode of the machine.

This functions modifies the mode of the machine. Not all transitions are possible,
this functions verifies that the transitions are lawful.
*/
void mouseDriver_setMode(uint8_t mode);


void mouseDriver_initSetpoint(void){
	actual_speed_setpoint.setpoint_x = 0;
	actual_speed_setpoint.setpoint_y = 0;
}
void mouseDriver_initMode(void){
	actual_mode = MOUSE_MODE_STOP;
}
void mouseDriver_initPoints(void){
	for(int i=0; i<MAX_POINTS; i++){
		points[i].duration = 0;
		points[i].setpoint_x = 0;
		points[i].setpoint_y = 0;
		points[i].point_id = 0;
	}
	actual_point = 0;
	actual_point_start_time = 0;
}
void mouseDriver_initMotorSignal(void){
    actual_motor_signal.motor_x = 0;
    actual_motor_signal.motor_y = 0;
}
void mouseDriver_init(void){
	mouseDriver_initMode();
	mouseDriver_initSetpoint();
	mouseDriver_initPoints();
	mouseDriver_initMotorSignal();

	/* Init sensor as well */
	sensorDriver_init();
	main_stop_motors();
}
uint32_t mouseDriver_getTime (void){
	return (HAL_GetTick());
}
void mouseDriver_send_status_msg(void){
	send_msg = 1;
}
void mouseDriver_control_idle(void){
	static int count = 0;
	if (actual_speed_measure.valid == 0){
		count ++;
		if(count >= MAX_MISSING_MEASURES){
			main_stop_motors();
			mouseDriver_setMode(MOUSE_MODE_STOP);
		}
		return;
	}
	if (actual_mode == MOUSE_MODE_SPEED || actual_mode == MOUSE_MODE_AUTO_RUN){
		actual_motor_signal.time = mouseDriver_getTime();
		actual_motor_signal.motor_x = (float)K*(actual_speed_setpoint.setpoint_x-actual_speed_measure.speed_x);
		actual_motor_signal.motor_y = (float)K*(actual_speed_setpoint.setpoint_y-actual_speed_measure.speed_y);

		if (actual_motor_signal.motor_x > MAX_MOTOR_SIGNAL){
		    actual_motor_signal.motor_x = MAX_MOTOR_SIGNAL;
		}
		if(actual_motor_signal.motor_y  > MAX_MOTOR_SIGNAL){
            actual_motor_signal.motor_y = MAX_MOTOR_SIGNAL;
        }

		main_set_motors_speed(actual_motor_signal);
		count = 0;
	}
	else{
		actual_motor_signal.motor_x = 0;
		actual_motor_signal.motor_y = 0;
		main_stop_motors();
	}
}

void mouseDriver_setMode(uint8_t mode){
    if (mode == MOUSE_MODE_STOP){
        main_stop_motors();
        actual_point = 0;
        actual_mode = MOUSE_MODE_STOP;
        mouseDriver_initMotorSignal();
    }
    if (mode == MOUSE_MODE_AUTO_LOAD){
        actual_mode = mode;
        mouseDriver_sendMsg(MAVLINK_MSG_ID_HEARTBEAT);
    }
    if (actual_mode == MOUSE_MODE_AUTO_LOAD && mode == MOUSE_MODE_AUTO_RUN ){
        actual_point = 0;
        actual_point_start_time = mouseDriver_getTime();
        actual_speed_setpoint.setpoint_x = points[0].setpoint_x;
        actual_speed_setpoint.setpoint_y = points[0].setpoint_y;
        actual_mode = mode;
    }

    if (actual_mode != MOUSE_MODE_AUTO_RUN)
        actual_mode = mode;
}
void mouseDriver_sendMsg(uint32_t msgid){
    mavlink_message_t msg;
    static uint8_t outBuffer[MAX_BYTE_BUFFER_SIZE];
    static uint16_t msg_size = 0;

    while (main_get_huart_tx_state() == HAL_BUSY){
        /*Wait for other messages to be sent*/
        HAL_Delay(1);
    }

    switch(msgid){
        case MAVLINK_MSG_ID_HEARTBEAT:
            mavlink_msg_heartbeat_pack(SYS_ID,COMP_ID, &msg, actual_mode, mouseDriver_getTime());
            msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
            main_transmit_buffer(outBuffer, msg_size);
            break;
        case MAVLINK_MSG_ID_SPEED_SETPOINT:
            mavlink_msg_speed_setpoint_encode(SYS_ID,COMP_ID, &msg, &actual_speed_setpoint);
            msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
            main_transmit_buffer(outBuffer, msg_size);
            break;
        case MAVLINK_MSG_ID_MOTOR_SETPOINT:
            mavlink_msg_motor_setpoint_encode(SYS_ID,COMP_ID, &msg, &actual_motor_signal);
            msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
            main_transmit_buffer(outBuffer, msg_size);
            break;
        case MAVLINK_MSG_ID_SPEED_INFO:
            /* DEMO CODE INIT*/
                actual_speed_measure.time_x = mouseDriver_getTime();
            /* DEMO CODE END*/
            mavlink_msg_speed_info_encode(SYS_ID,COMP_ID, &msg, &actual_speed_measure);
            msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
            main_transmit_buffer(outBuffer, msg_size);
            break;
        case MAVLINK_MSG_ID_ERROR:
            mavlink_msg_error_encode(SYS_ID,COMP_ID,&msg,&actual_error);
            msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
            main_transmit_buffer(outBuffer, msg_size);
            break;
        case MAVLINK_MSG_ID_POINT_LOADED:
            mavlink_msg_point_loaded_pack(SYS_ID,COMP_ID,&msg,actual_point);
            msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
            main_transmit_buffer(outBuffer, msg_size);
            break;
        case MAVLINK_MSG_ID_POINT:
            mavlink_msg_point_encode(SYS_ID,COMP_ID,&msg,&points[actual_point]);
            msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
            main_transmit_buffer(outBuffer, msg_size);
            break;
        case MAVLINK_MSG_ID_RAW_SENSOR:
            mavlink_msg_raw_sensor_encode(SYS_ID,COMP_ID,&msg,&actual_raw_sensor[0]);
            msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
            main_transmit_buffer(outBuffer, msg_size);
            mavlink_msg_raw_sensor_encode(SYS_ID,COMP_ID,&msg,&actual_raw_sensor[1]);
            msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
            main_transmit_buffer(outBuffer, msg_size);
            break;
        default:
            break;
    }
}
void mouseDriver_idle (void){
    uint64_t difference = 0;
    sensorDriver_motion_read_speed(actual_raw_sensor, &actual_speed_measure);
    switch(actual_mode){
    case MOUSE_MODE_STOP:
        mouseDriver_initSetpoint();
        mouseDriver_initMotorSignal();
        actual_motor_signal.time = mouseDriver_getTime();
        main_stop_motors();
        mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_INFO);

        break;
    case MOUSE_MODE_SPEED:
        mouseDriver_control_idle();
        mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_INFO);
        mouseDriver_sendMsg(MAVLINK_MSG_ID_MOTOR_SETPOINT);

        break;
    case MOUSE_MODE_AUTO_LOAD:
        if (actual_point == 255){
            actual_error.error = MOUSE_ROUTINE_TOO_LONG;
            actual_error.time = mouseDriver_getTime();
            mouseDriver_sendMsg(MAVLINK_MSG_ID_ERROR);
        }
        break;
    case MOUSE_MODE_AUTO_RUN:
        difference = mouseDriver_getTime()-actual_point_start_time;
        if (difference >= points[actual_point].duration){
            if (actual_point < MAX_POINTS-1){
                actual_point++;

                if(points[actual_point].duration == 0){
                    actual_point = 0;
                }
                actual_speed_setpoint.setpoint_x = points[actual_point].setpoint_x;
                actual_speed_setpoint.setpoint_y = points[actual_point].setpoint_y;
                actual_point_start_time = mouseDriver_getTime();
            }
        }
        if (actual_point == MAX_POINTS){
            mouseDriver_setMode(MOUSE_MODE_AUTO_LOAD);
        }
        mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_INFO);
        mouseDriver_sendMsg(MAVLINK_MSG_ID_MOTOR_SETPOINT);
        mouseDriver_control_idle();
        break;
    default:
        break;
    }
    if (send_msg == 1){
        send_msg = 0;
        mouseDriver_sendMsg(MAVLINK_MSG_ID_HEARTBEAT);
        if(actual_mode != MOUSE_MODE_AUTO_LOAD){
            mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_SETPOINT);
            mouseDriver_sendMsg(MAVLINK_MSG_ID_RAW_SENSOR);
            mouseDriver_sendMsg(MAVLINK_MSG_ID_MOTOR_SETPOINT);
        }
    }

}
void mouseDriver_readMsg(const mavlink_message_t msg){

    switch(msg.msgid){

    case MAVLINK_MSG_ID_MODE_SELECTION:
        mouseDriver_setMode( mavlink_msg_mode_selection_get_mode(&msg));
        break;

    case MAVLINK_MSG_ID_SPEED_SETPOINT:
        if (actual_mode == MOUSE_MODE_SPEED)
            mavlink_msg_speed_setpoint_decode(&msg, &actual_speed_setpoint);
        break;

    case MAVLINK_MSG_ID_MOTOR_SETPOINT:
        if (actual_mode == MOUSE_MODE_SPEED)
            mavlink_msg_speed_setpoint_decode(&msg, &actual_speed_setpoint);
        break;
    case MAVLINK_MSG_ID_POINT:
        if(actual_mode == MOUSE_MODE_AUTO_LOAD){
            mavlink_msg_point_decode(&msg, &points[actual_point]);
            if (actual_point == 255){
                actual_error.error = MOUSE_ROUTINE_TOO_LONG;
                actual_error.time = mouseDriver_getTime();
                mouseDriver_sendMsg(MAVLINK_MSG_ID_ERROR);
            }
            mouseDriver_sendMsg(MAVLINK_MSG_ID_POINT_LOADED);
            actual_point ++;

        }
        break;
    default:
        break;
    };
}
#endif
