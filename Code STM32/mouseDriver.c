#include "mouseDriver.h"

static uint32_t actualTime = 0;
static mavlink_speed_info_t actualSpeed;
static mavlink_speed_setpoint_t actualSpeedSetpoint;


void mouseDriver_init(void){
	actualTime = 0;
	actualSpeed.mode = MOUSE_MODE_STOP;
	actualSpeed.speed_x = 0;
	actualSpeed.speed_y = 0;
	actualSpeed.speed_z = 0;
	actualSpeedSetpoint.mode = MOUSE_MODE_STOP;
	actualSpeedSetpoint.setpoint_x = 0;
	actualSpeedSetpoint.setpoint_y = 0;
	actualSpeedSetpoint.setpoint_z = 0;
}

void mouseDriver_setTime (const uint32_t time){
	actualTime = time;
}

void mouseDriver_setSetpoint(const mavlink_speed_setpoint_t speed){
	actualSpeedSetpoint = speed;
	actualSpeed.mode = speed.mode;
}

mavlink_speed_info_t mouseDriver_getActualSpeed(void){
	return actualSpeed;
}

void mouseDriver_readMsg(const mavlink_message_t msg){

	switch(msg.msgid){

	case MAVLINK_MSG_ID_MODE_SELECTION:
		actualSpeedSetpoint.mode = mavlink_msg_mode_selection_get_mode(&msg);
		actualSpeed.mode = actualSpeedSetpoint.mode;
		mouseDriver_sendMsg(MAVLINK_MSG_ID_HEARTBEAT);
		break;

	case MAVLINK_MSG_ID_SPEED_SETPOINT:
		mavlink_msg_speed_setpoint_decode(&msg, &actualSpeedSetpoint);
		actualSpeed.mode = actualSpeedSetpoint.mode;
		mouseDriver_sendMsg(MAVLINK_MSG_ID_SPEED_SETPOINT);
		break;

	default:
		break;
	};
}

void mouseDriver_sendMsg(uint32_t msgid){
	uint8_t outBuffer[BUFFER_SIZE];
	mavlink_message_t outmsg;
	uint32_t len;
	outmsg.msgid = -1;

	switch(msgid){
	case MAVLINK_MSG_ID_HEARTBEAT:
		mavlink_msg_heartbeat_pack(SYS_ID,COMP_ID, &outmsg, actualSpeedSetpoint.mode, actualTime);
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

