#pragma once
// MESSAGE SPEED_INFO PACKING

#define MAVLINK_MSG_ID_SPEED_INFO 1

MAVPACKED(
typedef struct __mavlink_speed_info_t {
 uint32_t time_x; /*<  Time from boot of system for speed_x measure*/
 uint32_t time_y; /*<  Time from boot of system for speed_y measure*/
 float speed_x; /*<  Speed in x direction*/
 float speed_y; /*<  Speed in y direction*/
 uint8_t valid; /*<  0 if data are not valid, 1 if data are valid */
}) mavlink_speed_info_t;

#define MAVLINK_MSG_ID_SPEED_INFO_LEN 17
#define MAVLINK_MSG_ID_SPEED_INFO_MIN_LEN 17
#define MAVLINK_MSG_ID_1_LEN 17
#define MAVLINK_MSG_ID_1_MIN_LEN 17

#define MAVLINK_MSG_ID_SPEED_INFO_CRC 243
#define MAVLINK_MSG_ID_1_CRC 243



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SPEED_INFO { \
    1, \
    "SPEED_INFO", \
    5, \
    {  { "time_x", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_speed_info_t, time_x) }, \
         { "time_y", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_speed_info_t, time_y) }, \
         { "speed_x", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_speed_info_t, speed_x) }, \
         { "speed_y", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_speed_info_t, speed_y) }, \
         { "valid", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_speed_info_t, valid) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SPEED_INFO { \
    "SPEED_INFO", \
    5, \
    {  { "time_x", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_speed_info_t, time_x) }, \
         { "time_y", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_speed_info_t, time_y) }, \
         { "speed_x", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_speed_info_t, speed_x) }, \
         { "speed_y", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_speed_info_t, speed_y) }, \
         { "valid", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_speed_info_t, valid) }, \
         } \
}
#endif

/**
 * @brief Pack a speed_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_x  Time from boot of system for speed_x measure
 * @param time_y  Time from boot of system for speed_y measure
 * @param speed_x  Speed in x direction
 * @param speed_y  Speed in y direction
 * @param valid  0 if data are not valid, 1 if data are valid 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speed_info_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time_x, uint32_t time_y, float speed_x, float speed_y, uint8_t valid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPEED_INFO_LEN];
    _mav_put_uint32_t(buf, 0, time_x);
    _mav_put_uint32_t(buf, 4, time_y);
    _mav_put_float(buf, 8, speed_x);
    _mav_put_float(buf, 12, speed_y);
    _mav_put_uint8_t(buf, 16, valid);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SPEED_INFO_LEN);
#else
    mavlink_speed_info_t packet;
    packet.time_x = time_x;
    packet.time_y = time_y;
    packet.speed_x = speed_x;
    packet.speed_y = speed_y;
    packet.valid = valid;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SPEED_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SPEED_INFO;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SPEED_INFO_MIN_LEN, MAVLINK_MSG_ID_SPEED_INFO_LEN, MAVLINK_MSG_ID_SPEED_INFO_CRC);
}

/**
 * @brief Pack a speed_info message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_x  Time from boot of system for speed_x measure
 * @param time_y  Time from boot of system for speed_y measure
 * @param speed_x  Speed in x direction
 * @param speed_y  Speed in y direction
 * @param valid  0 if data are not valid, 1 if data are valid 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speed_info_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time_x,uint32_t time_y,float speed_x,float speed_y,uint8_t valid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPEED_INFO_LEN];
    _mav_put_uint32_t(buf, 0, time_x);
    _mav_put_uint32_t(buf, 4, time_y);
    _mav_put_float(buf, 8, speed_x);
    _mav_put_float(buf, 12, speed_y);
    _mav_put_uint8_t(buf, 16, valid);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SPEED_INFO_LEN);
#else
    mavlink_speed_info_t packet;
    packet.time_x = time_x;
    packet.time_y = time_y;
    packet.speed_x = speed_x;
    packet.speed_y = speed_y;
    packet.valid = valid;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SPEED_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SPEED_INFO;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SPEED_INFO_MIN_LEN, MAVLINK_MSG_ID_SPEED_INFO_LEN, MAVLINK_MSG_ID_SPEED_INFO_CRC);
}

/**
 * @brief Encode a speed_info struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param speed_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speed_info_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_speed_info_t* speed_info)
{
    return mavlink_msg_speed_info_pack(system_id, component_id, msg, speed_info->time_x, speed_info->time_y, speed_info->speed_x, speed_info->speed_y, speed_info->valid);
}

/**
 * @brief Encode a speed_info struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param speed_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speed_info_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_speed_info_t* speed_info)
{
    return mavlink_msg_speed_info_pack_chan(system_id, component_id, chan, msg, speed_info->time_x, speed_info->time_y, speed_info->speed_x, speed_info->speed_y, speed_info->valid);
}

/**
 * @brief Send a speed_info message
 * @param chan MAVLink channel to send the message
 *
 * @param time_x  Time from boot of system for speed_x measure
 * @param time_y  Time from boot of system for speed_y measure
 * @param speed_x  Speed in x direction
 * @param speed_y  Speed in y direction
 * @param valid  0 if data are not valid, 1 if data are valid 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_speed_info_send(mavlink_channel_t chan, uint32_t time_x, uint32_t time_y, float speed_x, float speed_y, uint8_t valid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPEED_INFO_LEN];
    _mav_put_uint32_t(buf, 0, time_x);
    _mav_put_uint32_t(buf, 4, time_y);
    _mav_put_float(buf, 8, speed_x);
    _mav_put_float(buf, 12, speed_y);
    _mav_put_uint8_t(buf, 16, valid);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_INFO, buf, MAVLINK_MSG_ID_SPEED_INFO_MIN_LEN, MAVLINK_MSG_ID_SPEED_INFO_LEN, MAVLINK_MSG_ID_SPEED_INFO_CRC);
#else
    mavlink_speed_info_t packet;
    packet.time_x = time_x;
    packet.time_y = time_y;
    packet.speed_x = speed_x;
    packet.speed_y = speed_y;
    packet.valid = valid;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_INFO, (const char *)&packet, MAVLINK_MSG_ID_SPEED_INFO_MIN_LEN, MAVLINK_MSG_ID_SPEED_INFO_LEN, MAVLINK_MSG_ID_SPEED_INFO_CRC);
#endif
}

/**
 * @brief Send a speed_info message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_speed_info_send_struct(mavlink_channel_t chan, const mavlink_speed_info_t* speed_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_speed_info_send(chan, speed_info->time_x, speed_info->time_y, speed_info->speed_x, speed_info->speed_y, speed_info->valid);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_INFO, (const char *)speed_info, MAVLINK_MSG_ID_SPEED_INFO_MIN_LEN, MAVLINK_MSG_ID_SPEED_INFO_LEN, MAVLINK_MSG_ID_SPEED_INFO_CRC);
#endif
}

#if MAVLINK_MSG_ID_SPEED_INFO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_speed_info_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_x, uint32_t time_y, float speed_x, float speed_y, uint8_t valid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, time_x);
    _mav_put_uint32_t(buf, 4, time_y);
    _mav_put_float(buf, 8, speed_x);
    _mav_put_float(buf, 12, speed_y);
    _mav_put_uint8_t(buf, 16, valid);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_INFO, buf, MAVLINK_MSG_ID_SPEED_INFO_MIN_LEN, MAVLINK_MSG_ID_SPEED_INFO_LEN, MAVLINK_MSG_ID_SPEED_INFO_CRC);
#else
    mavlink_speed_info_t *packet = (mavlink_speed_info_t *)msgbuf;
    packet->time_x = time_x;
    packet->time_y = time_y;
    packet->speed_x = speed_x;
    packet->speed_y = speed_y;
    packet->valid = valid;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_INFO, (const char *)packet, MAVLINK_MSG_ID_SPEED_INFO_MIN_LEN, MAVLINK_MSG_ID_SPEED_INFO_LEN, MAVLINK_MSG_ID_SPEED_INFO_CRC);
#endif
}
#endif

#endif

// MESSAGE SPEED_INFO UNPACKING


/**
 * @brief Get field time_x from speed_info message
 *
 * @return  Time from boot of system for speed_x measure
 */
static inline uint32_t mavlink_msg_speed_info_get_time_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field time_y from speed_info message
 *
 * @return  Time from boot of system for speed_y measure
 */
static inline uint32_t mavlink_msg_speed_info_get_time_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field speed_x from speed_info message
 *
 * @return  Speed in x direction
 */
static inline float mavlink_msg_speed_info_get_speed_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field speed_y from speed_info message
 *
 * @return  Speed in y direction
 */
static inline float mavlink_msg_speed_info_get_speed_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field valid from speed_info message
 *
 * @return  0 if data are not valid, 1 if data are valid 
 */
static inline uint8_t mavlink_msg_speed_info_get_valid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Decode a speed_info message into a struct
 *
 * @param msg The message to decode
 * @param speed_info C-struct to decode the message contents into
 */
static inline void mavlink_msg_speed_info_decode(const mavlink_message_t* msg, mavlink_speed_info_t* speed_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    speed_info->time_x = mavlink_msg_speed_info_get_time_x(msg);
    speed_info->time_y = mavlink_msg_speed_info_get_time_y(msg);
    speed_info->speed_x = mavlink_msg_speed_info_get_speed_x(msg);
    speed_info->speed_y = mavlink_msg_speed_info_get_speed_y(msg);
    speed_info->valid = mavlink_msg_speed_info_get_valid(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SPEED_INFO_LEN? msg->len : MAVLINK_MSG_ID_SPEED_INFO_LEN;
        memset(speed_info, 0, MAVLINK_MSG_ID_SPEED_INFO_LEN);
    memcpy(speed_info, _MAV_PAYLOAD(msg), len);
#endif
}
