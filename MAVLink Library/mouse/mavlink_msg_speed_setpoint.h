#pragma once
// MESSAGE SPEED_SETPOINT PACKING

#define MAVLINK_MSG_ID_SPEED_SETPOINT 2

MAVPACKED(
typedef struct __mavlink_speed_setpoint_t {
 float setpoint_x; /*<  Speed setpoint in x direction*/
 float setpoint_y; /*<  Speed setpoint in y direction*/
}) mavlink_speed_setpoint_t;

#define MAVLINK_MSG_ID_SPEED_SETPOINT_LEN 8
#define MAVLINK_MSG_ID_SPEED_SETPOINT_MIN_LEN 8
#define MAVLINK_MSG_ID_2_LEN 8
#define MAVLINK_MSG_ID_2_MIN_LEN 8

#define MAVLINK_MSG_ID_SPEED_SETPOINT_CRC 38
#define MAVLINK_MSG_ID_2_CRC 38



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SPEED_SETPOINT { \
    2, \
    "SPEED_SETPOINT", \
    2, \
    {  { "setpoint_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_speed_setpoint_t, setpoint_x) }, \
         { "setpoint_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_speed_setpoint_t, setpoint_y) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SPEED_SETPOINT { \
    "SPEED_SETPOINT", \
    2, \
    {  { "setpoint_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_speed_setpoint_t, setpoint_x) }, \
         { "setpoint_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_speed_setpoint_t, setpoint_y) }, \
         } \
}
#endif

/**
 * @brief Pack a speed_setpoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param setpoint_x  Speed setpoint in x direction
 * @param setpoint_y  Speed setpoint in y direction
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speed_setpoint_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float setpoint_x, float setpoint_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPEED_SETPOINT_LEN];
    _mav_put_float(buf, 0, setpoint_x);
    _mav_put_float(buf, 4, setpoint_y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN);
#else
    mavlink_speed_setpoint_t packet;
    packet.setpoint_x = setpoint_x;
    packet.setpoint_y = setpoint_y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SPEED_SETPOINT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SPEED_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_CRC);
}

/**
 * @brief Pack a speed_setpoint message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param setpoint_x  Speed setpoint in x direction
 * @param setpoint_y  Speed setpoint in y direction
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speed_setpoint_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float setpoint_x,float setpoint_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPEED_SETPOINT_LEN];
    _mav_put_float(buf, 0, setpoint_x);
    _mav_put_float(buf, 4, setpoint_y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN);
#else
    mavlink_speed_setpoint_t packet;
    packet.setpoint_x = setpoint_x;
    packet.setpoint_y = setpoint_y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SPEED_SETPOINT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SPEED_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_CRC);
}

/**
 * @brief Encode a speed_setpoint struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param speed_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speed_setpoint_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_speed_setpoint_t* speed_setpoint)
{
    return mavlink_msg_speed_setpoint_pack(system_id, component_id, msg, speed_setpoint->setpoint_x, speed_setpoint->setpoint_y);
}

/**
 * @brief Encode a speed_setpoint struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param speed_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speed_setpoint_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_speed_setpoint_t* speed_setpoint)
{
    return mavlink_msg_speed_setpoint_pack_chan(system_id, component_id, chan, msg, speed_setpoint->setpoint_x, speed_setpoint->setpoint_y);
}

/**
 * @brief Send a speed_setpoint message
 * @param chan MAVLink channel to send the message
 *
 * @param setpoint_x  Speed setpoint in x direction
 * @param setpoint_y  Speed setpoint in y direction
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_speed_setpoint_send(mavlink_channel_t chan, float setpoint_x, float setpoint_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPEED_SETPOINT_LEN];
    _mav_put_float(buf, 0, setpoint_x);
    _mav_put_float(buf, 4, setpoint_y);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_SETPOINT, buf, MAVLINK_MSG_ID_SPEED_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_CRC);
#else
    mavlink_speed_setpoint_t packet;
    packet.setpoint_x = setpoint_x;
    packet.setpoint_y = setpoint_y;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_SETPOINT, (const char *)&packet, MAVLINK_MSG_ID_SPEED_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_CRC);
#endif
}

/**
 * @brief Send a speed_setpoint message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_speed_setpoint_send_struct(mavlink_channel_t chan, const mavlink_speed_setpoint_t* speed_setpoint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_speed_setpoint_send(chan, speed_setpoint->setpoint_x, speed_setpoint->setpoint_y);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_SETPOINT, (const char *)speed_setpoint, MAVLINK_MSG_ID_SPEED_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_CRC);
#endif
}

#if MAVLINK_MSG_ID_SPEED_SETPOINT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_speed_setpoint_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float setpoint_x, float setpoint_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, setpoint_x);
    _mav_put_float(buf, 4, setpoint_y);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_SETPOINT, buf, MAVLINK_MSG_ID_SPEED_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_CRC);
#else
    mavlink_speed_setpoint_t *packet = (mavlink_speed_setpoint_t *)msgbuf;
    packet->setpoint_x = setpoint_x;
    packet->setpoint_y = setpoint_y;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_SETPOINT, (const char *)packet, MAVLINK_MSG_ID_SPEED_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN, MAVLINK_MSG_ID_SPEED_SETPOINT_CRC);
#endif
}
#endif

#endif

// MESSAGE SPEED_SETPOINT UNPACKING


/**
 * @brief Get field setpoint_x from speed_setpoint message
 *
 * @return  Speed setpoint in x direction
 */
static inline float mavlink_msg_speed_setpoint_get_setpoint_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field setpoint_y from speed_setpoint message
 *
 * @return  Speed setpoint in y direction
 */
static inline float mavlink_msg_speed_setpoint_get_setpoint_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a speed_setpoint message into a struct
 *
 * @param msg The message to decode
 * @param speed_setpoint C-struct to decode the message contents into
 */
static inline void mavlink_msg_speed_setpoint_decode(const mavlink_message_t* msg, mavlink_speed_setpoint_t* speed_setpoint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    speed_setpoint->setpoint_x = mavlink_msg_speed_setpoint_get_setpoint_x(msg);
    speed_setpoint->setpoint_y = mavlink_msg_speed_setpoint_get_setpoint_y(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SPEED_SETPOINT_LEN? msg->len : MAVLINK_MSG_ID_SPEED_SETPOINT_LEN;
        memset(speed_setpoint, 0, MAVLINK_MSG_ID_SPEED_SETPOINT_LEN);
    memcpy(speed_setpoint, _MAV_PAYLOAD(msg), len);
#endif
}
