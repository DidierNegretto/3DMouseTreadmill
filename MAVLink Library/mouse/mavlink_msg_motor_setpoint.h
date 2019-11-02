#pragma once
// MESSAGE MOTOR_SETPOINT PACKING

#define MAVLINK_MSG_ID_MOTOR_SETPOINT 4

MAVPACKED(
typedef struct __mavlink_motor_setpoint_t {
 uint32_t time; /*<  Time from boot of system*/
 float motor_x; /*<  Speed setpoint in x direction*/
 float motor_y; /*<  Speed setpoint in y direction*/
 float motor_z; /*<  Speed setpoint in z direction*/
}) mavlink_motor_setpoint_t;

#define MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN 16
#define MAVLINK_MSG_ID_MOTOR_SETPOINT_MIN_LEN 16
#define MAVLINK_MSG_ID_4_LEN 16
#define MAVLINK_MSG_ID_4_MIN_LEN 16

#define MAVLINK_MSG_ID_MOTOR_SETPOINT_CRC 163
#define MAVLINK_MSG_ID_4_CRC 163



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOTOR_SETPOINT { \
    4, \
    "MOTOR_SETPOINT", \
    4, \
    {  { "time", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motor_setpoint_t, time) }, \
         { "motor_x", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_setpoint_t, motor_x) }, \
         { "motor_y", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motor_setpoint_t, motor_y) }, \
         { "motor_z", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_motor_setpoint_t, motor_z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOTOR_SETPOINT { \
    "MOTOR_SETPOINT", \
    4, \
    {  { "time", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motor_setpoint_t, time) }, \
         { "motor_x", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_setpoint_t, motor_x) }, \
         { "motor_y", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motor_setpoint_t, motor_y) }, \
         { "motor_z", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_motor_setpoint_t, motor_z) }, \
         } \
}
#endif

/**
 * @brief Pack a motor_setpoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time  Time from boot of system
 * @param motor_x  Speed setpoint in x direction
 * @param motor_y  Speed setpoint in y direction
 * @param motor_z  Speed setpoint in z direction
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_setpoint_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time, float motor_x, float motor_y, float motor_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN];
    _mav_put_uint32_t(buf, 0, time);
    _mav_put_float(buf, 4, motor_x);
    _mav_put_float(buf, 8, motor_y);
    _mav_put_float(buf, 12, motor_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN);
#else
    mavlink_motor_setpoint_t packet;
    packet.time = time;
    packet.motor_x = motor_x;
    packet.motor_y = motor_y;
    packet.motor_z = motor_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_SETPOINT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOTOR_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_CRC);
}

/**
 * @brief Pack a motor_setpoint message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time  Time from boot of system
 * @param motor_x  Speed setpoint in x direction
 * @param motor_y  Speed setpoint in y direction
 * @param motor_z  Speed setpoint in z direction
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_setpoint_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time,float motor_x,float motor_y,float motor_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN];
    _mav_put_uint32_t(buf, 0, time);
    _mav_put_float(buf, 4, motor_x);
    _mav_put_float(buf, 8, motor_y);
    _mav_put_float(buf, 12, motor_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN);
#else
    mavlink_motor_setpoint_t packet;
    packet.time = time;
    packet.motor_x = motor_x;
    packet.motor_y = motor_y;
    packet.motor_z = motor_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_SETPOINT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOTOR_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_CRC);
}

/**
 * @brief Encode a motor_setpoint struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motor_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_setpoint_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motor_setpoint_t* motor_setpoint)
{
    return mavlink_msg_motor_setpoint_pack(system_id, component_id, msg, motor_setpoint->time, motor_setpoint->motor_x, motor_setpoint->motor_y, motor_setpoint->motor_z);
}

/**
 * @brief Encode a motor_setpoint struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_setpoint_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motor_setpoint_t* motor_setpoint)
{
    return mavlink_msg_motor_setpoint_pack_chan(system_id, component_id, chan, msg, motor_setpoint->time, motor_setpoint->motor_x, motor_setpoint->motor_y, motor_setpoint->motor_z);
}

/**
 * @brief Send a motor_setpoint message
 * @param chan MAVLink channel to send the message
 *
 * @param time  Time from boot of system
 * @param motor_x  Speed setpoint in x direction
 * @param motor_y  Speed setpoint in y direction
 * @param motor_z  Speed setpoint in z direction
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motor_setpoint_send(mavlink_channel_t chan, uint32_t time, float motor_x, float motor_y, float motor_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN];
    _mav_put_uint32_t(buf, 0, time);
    _mav_put_float(buf, 4, motor_x);
    _mav_put_float(buf, 8, motor_y);
    _mav_put_float(buf, 12, motor_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETPOINT, buf, MAVLINK_MSG_ID_MOTOR_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_CRC);
#else
    mavlink_motor_setpoint_t packet;
    packet.time = time;
    packet.motor_x = motor_x;
    packet.motor_y = motor_y;
    packet.motor_z = motor_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETPOINT, (const char *)&packet, MAVLINK_MSG_ID_MOTOR_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_CRC);
#endif
}

/**
 * @brief Send a motor_setpoint message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motor_setpoint_send_struct(mavlink_channel_t chan, const mavlink_motor_setpoint_t* motor_setpoint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motor_setpoint_send(chan, motor_setpoint->time, motor_setpoint->motor_x, motor_setpoint->motor_y, motor_setpoint->motor_z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETPOINT, (const char *)motor_setpoint, MAVLINK_MSG_ID_MOTOR_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_CRC);
#endif
}

#if MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motor_setpoint_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time, float motor_x, float motor_y, float motor_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, time);
    _mav_put_float(buf, 4, motor_x);
    _mav_put_float(buf, 8, motor_y);
    _mav_put_float(buf, 12, motor_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETPOINT, buf, MAVLINK_MSG_ID_MOTOR_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_CRC);
#else
    mavlink_motor_setpoint_t *packet = (mavlink_motor_setpoint_t *)msgbuf;
    packet->time = time;
    packet->motor_x = motor_x;
    packet->motor_y = motor_y;
    packet->motor_z = motor_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETPOINT, (const char *)packet, MAVLINK_MSG_ID_MOTOR_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN, MAVLINK_MSG_ID_MOTOR_SETPOINT_CRC);
#endif
}
#endif

#endif

// MESSAGE MOTOR_SETPOINT UNPACKING


/**
 * @brief Get field time from motor_setpoint message
 *
 * @return  Time from boot of system
 */
static inline uint32_t mavlink_msg_motor_setpoint_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field motor_x from motor_setpoint message
 *
 * @return  Speed setpoint in x direction
 */
static inline float mavlink_msg_motor_setpoint_get_motor_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field motor_y from motor_setpoint message
 *
 * @return  Speed setpoint in y direction
 */
static inline float mavlink_msg_motor_setpoint_get_motor_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field motor_z from motor_setpoint message
 *
 * @return  Speed setpoint in z direction
 */
static inline float mavlink_msg_motor_setpoint_get_motor_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a motor_setpoint message into a struct
 *
 * @param msg The message to decode
 * @param motor_setpoint C-struct to decode the message contents into
 */
static inline void mavlink_msg_motor_setpoint_decode(const mavlink_message_t* msg, mavlink_motor_setpoint_t* motor_setpoint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motor_setpoint->time = mavlink_msg_motor_setpoint_get_time(msg);
    motor_setpoint->motor_x = mavlink_msg_motor_setpoint_get_motor_x(msg);
    motor_setpoint->motor_y = mavlink_msg_motor_setpoint_get_motor_y(msg);
    motor_setpoint->motor_z = mavlink_msg_motor_setpoint_get_motor_z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN? msg->len : MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN;
        memset(motor_setpoint, 0, MAVLINK_MSG_ID_MOTOR_SETPOINT_LEN);
    memcpy(motor_setpoint, _MAV_PAYLOAD(msg), len);
#endif
}
