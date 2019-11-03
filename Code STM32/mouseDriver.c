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
	static uint8_t outBuffer[MAX_BYTE_BUFFER_SIZE];
	static uint16_t msg_size = 0;

	if (tx_finish == 1){
		switch(msgid){
		case MAVLINK_MSG_ID_HEARTBEAT:
			mavlink_msg_heartbeat_pack(SYS_ID,COMP_ID, &msg, actual_mode, actual_time);
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
			mavlink_msg_speed_info_encode(SYS_ID,COMP_ID, &msg, &actual_speed_measure);
			msg_size = mavlink_msg_to_send_buffer(outBuffer, &msg);
			main_transmit_buffer(outBuffer, msg_size);
			break;
		default:
			break;
		}
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
		if (actual_mode == MOUSE_MODE_SPEED)
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
	actual_motor_signal.time = actual_time;

	switch(actual_mode){
	case MOUSE_MODE_STOP:
		mouseDriver_initSetpoint();
		actual_motor_signal.motor_x = 0;
		actual_motor_signal.motor_y = 0;
		main_stop_motors();
		break;
	case MOUSE_MODE_SPEED:
		/* BEGIN Code for DEMO */
		actual_motor_signal.motor_x = actual_speed_setpoint.setpoint_x;
		actual_motor_signal.motor_y = actual_speed_setpoint.setpoint_y;
		/* END Code for DEMO */
		main_set_motors_speed(actual_motor_signal);
		break;
	case MOUSE_MODE_AUTO:
		break;
	}
	mouseDriver_sendMsg(MAVLINK_MSG_ID_HEARTBEAT);
	HAL_Delay(10);
	mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_SETPOINT);
	HAL_Delay(10);
	mouseDriver_sendMsg(MAVLINK_MSG_ID_MOTOR_SETPOINT);
	HAL_Delay(10);
	mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_INFO);
	HAL_Delay(10);

}

/* ISR Functions */
void mouseDriver_controlISR(void){

}

