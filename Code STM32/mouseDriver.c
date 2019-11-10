/*! \file mouseDriver.c
\brief Implementation of the driver for the mouse treadmil project.

\author Didier Negretto
*/
#include "mouseDriver.h"
/*!
\var actual_time
\brief Global variable for time keeping

This value is periodically updated.
*/
static uint32_t actual_time = 0;
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
static mavlink_point_t points[MAX_POINTS];
/*!
\var actual_point
\brief Global variable for keeping track of the index in the \ref points array.
*/
static uint8_t actual_point = 0;
/*!
\var actual_point_start_time
\brief Global variable for keeping track of the time when the last point in \ref points array started.
*/
static uint8_t actual_point_start_time = 0;
/*!
\var actual_error
\brief Global variable to store and send the last error occured
*/
static mavlink_error_t actual_error;

/* Private functions for mouseDriver.c*/
/* Private Init functions */

void mouseDriver_initSetpoint(void){
	actual_speed_setpoint.setpoint_x = 0;
	actual_speed_setpoint.setpoint_y = 0;
}

void mouseDriver_initTime(void){
	actual_time = 0;
}

void mouseDriver_initMode(void){
	actual_mode = MOUSE_MODE_STOP;
}

void mouseDriver_getSpeedFromSensors(void){
	actual_speed_measure.speed_x = 1;
	actual_speed_measure.speed_y = 2;
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
/* Private set/get functions */
void mouseDriver_setSetpoint(const mavlink_speed_setpoint_t speed){
	actual_speed_setpoint = speed;
}

void mouseDriver_setMode(uint8_t mode){
	if (mode == MOUSE_MODE_STOP){
		main_stop_motors();
		actual_mode = MOUSE_MODE_STOP;
	}
	if (actual_mode == MOUSE_MODE_AUTO_LOAD && mode == MOUSE_MODE_AUTO_RUN ){
		actual_point = 0;
		actual_mode = mode;
	}

	if (actual_mode != MOUSE_MODE_AUTO_RUN)
		actual_mode = mode;
}

/* Private message functions */
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
				actual_speed_measure.time = actual_time;
			/* DEMO CODE END*/
			mavlink_msg_speed_info_encode(SYS_ID,COMP_ID, &msg, &actual_speed_measure);
			msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
			main_transmit_buffer(outBuffer, msg_size);
			break;
		case MAVLINK_MSG_ID_ERROR:
			mavlink_msg_error_encode(SYS_ID,COMP_ID,&msg,&actual_error);
			msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
			main_transmit_buffer(outBuffer, msg_size);
		default:
			break;
	}
}

/* Private Idle functions */

/* END of private functions */

/* Init functions */
void mouseDriver_init(void){
	mouseDriver_initTime();
	mouseDriver_initMode();
	mouseDriver_getSpeedFromSensors();
	mouseDriver_initSetpoint();
	mouseDriver_initPoints();
}
/* Function set/get */
void mouseDriver_setTime (const uint32_t time){
	actual_time = time;
}

uint32_t mouseDriver_getTime (void){
	return actual_time;
}
/* Message related functions */
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

	default:
		break;
	};
}

/* Idle functions */
void mouseDriver_idle (void){
	/* DEMO CODE INIT*/
		actual_motor_signal.time = mouseDriver_getTime();
	/* DEMO CODE END*/

	switch(actual_mode){
	case MOUSE_MODE_STOP:
		mouseDriver_initSetpoint();
		actual_motor_signal.motor_x = 0;
		actual_motor_signal.motor_y = 0;
		main_stop_motors();
		mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_SETPOINT);
		mouseDriver_sendMsg(MAVLINK_MSG_ID_MOTOR_SETPOINT);
		mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_INFO);
		break;
	case MOUSE_MODE_SPEED:
		/* BEGIN Code for DEMO */
			actual_motor_signal.motor_x = actual_speed_setpoint.setpoint_x;
			actual_motor_signal.motor_y = actual_speed_setpoint.setpoint_y;
		/* END Code for DEMO */
		main_set_motors_speed(actual_motor_signal);
		mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_SETPOINT);
		mouseDriver_sendMsg(MAVLINK_MSG_ID_MOTOR_SETPOINT);
		mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_INFO);
		break;
	case MOUSE_MODE_AUTO_LOAD:
		if (actual_point == 255){
			actual_error.error = MOUSE_ROUTINE_TOO_LONG;
			actual_error.time = mouseDriver_getTime();
		}
		break;
	case MOUSE_MODE_AUTO_RUN:

		if ((points[actual_point].duration == 0) || (actual_point == 255)){
			actual_mode = MOUSE_MODE_AUTO_LOAD;
			actual_point = 0;
		}
		break;
	default:
		break;
	}
	mouseDriver_sendMsg(MAVLINK_MSG_ID_HEARTBEAT);


}

/* ISR Functions */
void mouseDriver_controlISR(void){

}

