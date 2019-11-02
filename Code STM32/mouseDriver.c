#include "mouseDriver.h"

static uint32_t actual_time = 0;
static uint8_t actual_mode = MOUSE_MODE_STOP;
static mavlink_speed_info_t actual_speed_measure;
static mavlink_speed_setpoint_t actual_speed_setpoint;
static mavlink_motor_setpoint_t actual_motor_signal;

/* Private functions for mouseDriver.c*/
/* Private Init functions */
void mouseDriver_initSetpoint(void){
	actual_speed_setpoint.setpoint_x = 0;
	actual_speed_setpoint.setpoint_y = 0;
	actual_speed_setpoint.setpoint_z = 0;
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
	actual_speed_measure.speed_z = 3;
}

/* Private set/get functions */
void mouseDriver_setSetpoint(const mavlink_speed_setpoint_t speed){
	actual_speed_setpoint = speed;
}

void mouseDriver_setMode(uint8_t mode){
	actual_mode = mode;
}

/* Private message functions */
void mouseDriver_sendMsg(uint32_t msgid){
	mavlink_message_t msg;
	uint16_t len = 0;
	static uint8_t outbuffer[MAX_BYTE_BUFFER_SIZE];
	switch(msgid){
	case MAVLINK_MSG_ID_HEARTBEAT:
		mavlink_msg_heartbeat_pack(SYS_ID,COMP_ID, &msg, actual_mode, actual_time);
		len = mavlink_msg_to_send_buffer(outbuffer, &msg);
		main_transmit_buffer(outbuffer, len);
		break;
	case MAVLINK_MSG_ID_SPEED_SETPOINT:
		mavlink_msg_speed_setpoint_encode(SYS_ID,COMP_ID, &msg, &actual_speed_setpoint);
		len = mavlink_msg_to_send_buffer(outbuffer, &msg);
		main_transmit_buffer(outbuffer, len);
		break;
	case MAVLINK_MSG_ID_MOTOR_SETPOINT:
		mavlink_msg_motor_setpoint_encode(SYS_ID,COMP_ID, &msg, &actual_motor_signal);
		len = mavlink_msg_to_send_buffer(outbuffer, &msg);
		main_transmit_buffer(outbuffer, len);
		break;
	case MAVLINK_MSG_ID_SPEED_INFO:
		mavlink_msg_speed_info_encode(SYS_ID,COMP_ID, &msg, &actual_speed_measure);
		len = mavlink_msg_to_send_buffer(outbuffer, &msg);
		main_transmit_buffer(outbuffer, len);
		break;
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
		mavlink_msg_speed_setpoint_decode(&msg, &actual_speed_setpoint);
		break;

	case MAVLINK_MSG_ID_MOTOR_SETPOINT:
		mavlink_msg_speed_setpoint_decode(&msg, &actual_speed_setpoint);
		break;

	default:
		break;
	};
}

/* Idle functions */
void mouseDriver_idle (void){
	static mavlink_motor_setpoint_t motor;
	motor.time = actual_time;
	motor.motor_x = 10;
	motor.motor_y = 20;

	switch(actual_mode){
	case MOUSE_MODE_STOP:
		mouseDriver_initSetpoint();
		main_stop_motors();
		break;
	case MOUSE_MODE_SPEED:
		main_set_motors_speed(motor);
		break;
	case MOUSE_MODE_AUTO:
		break;
	}
	mouseDriver_sendMsg(MAVLINK_MSG_ID_HEARTBEAT);
	mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_SETPOINT);
	mouseDriver_sendMsg(MAVLINK_MSG_ID_MOTOR_SETPOINT);
	mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_INFO);
	/*if (tx_finish == 1){
		tx_finish = 0;
		main_transmit_buffer_IT();
	}*/
}

/* ISR Functions */
void mouseDriver_controlISR(void){

}

