#include "mouseDriver.h"

static uint32_t actualTime = 0;
static uint8_t actualMode = MOUSE_MODE_STOP;
static mavlink_speed_info_t actualSpeed;
static mavlink_speed_setpoint_t actualSpeedSetpoint;

/* Private functions for mouseDriver.c*/
/* Private Init functions */
void mouseDriver_initSetpoint(void){
	actualSpeedSetpoint.setpoint_x = 0;
	actualSpeedSetpoint.setpoint_y = 0;
	actualSpeedSetpoint.setpoint_z = 0;
}

void mouseDriver_initTime(void){
	actualTime = 0;
}

void mouseDriver_initMode(void){
	actualMode = MOUSE_MODE_STOP;
}

void mouseDriver_getSpeedFromSensors(void){
	actualSpeed.speed_x = 1;
	actualSpeed.speed_y = 2;
	actualSpeed.speed_z = 3;
}

/* Private set/get functions */
void mouseDriver_setSetpoint(const mavlink_speed_setpoint_t speed){
	actualSpeedSetpoint = speed;
}

void mouseDriver_setMode(uint8_t mode){
	actualMode = mode;
}

/* Private message functions */
void mouseDriver_sendMsg(uint32_t msgid){
	uint8_t outBuffer[BUFFER_SIZE];
	mavlink_message_t outmsg;
	uint32_t len;
	outmsg.msgid = -1;

	switch(msgid){
	case MAVLINK_MSG_ID_HEARTBEAT:
		mavlink_msg_heartbeat_pack(SYS_ID,COMP_ID, &outmsg, actualMode, actualTime);
		len = mavlink_msg_to_send_buffer(outBuffer, &outmsg);
		main_transmitBuffer(outBuffer, (uint32_t)len);
		break;
	case MAVLINK_MSG_ID_SPEED_SETPOINT:
		mavlink_msg_speed_setpoint_encode(SYS_ID,COMP_ID, &outmsg, &actualSpeedSetpoint);
		len = mavlink_msg_to_send_buffer(outBuffer, &outmsg);
		main_transmitBuffer(outBuffer, (uint32_t)len);
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
	actualTime = time;
}

uint32_t mouseDriver_getTime (void){
	return actualTime;
}
/* Message related functions */
void mouseDriver_readMsg(const mavlink_message_t msg){

	switch(msg.msgid){

	case MAVLINK_MSG_ID_MODE_SELECTION:
		mouseDriver_setMode( mavlink_msg_mode_selection_get_mode(&msg));
		break;

	case MAVLINK_MSG_ID_SPEED_SETPOINT:
		mavlink_msg_speed_setpoint_decode(&msg, &actualSpeedSetpoint);
		break;

	default:
		break;
	};
}

/* Idle functions */
void mouseDriver_idle (void){

	switch(actualMode){
	case MOUSE_MODE_STOP:
		mouseDriver_initSetpoint();
		break;
	case MOUSE_MODE_SPEED:
		break;
	case MOUSE_MODE_AUTO:
		break;
	}
	mouseDriver_sendMsg(MAVLINK_MSG_ID_HEARTBEAT);
}

/* ISR Functions */
void mouseDriver_controlISR(void){

}

