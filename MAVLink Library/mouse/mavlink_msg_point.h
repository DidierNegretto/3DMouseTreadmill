#pragma once
// MESSAGE POINT PACKING

#define MAVLINK_MSG_ID_POINT 6

MAVPACKED(
typedef struct __mavlink_point_t {
 uint32_t duration; /*<  Time during which the setpoint need to be kept*/
 float setpoint_x; /*<  Speed setpoint in x direction*/
 float setpoint_y; /*<  Speed setpoint in y direction*/
 uint16_t point_id; /*<  point ID*/
}) mavlink_point_t;

#define MAVLINK_MSG_ID_POINT_LEN 14
#define MAVLINK_MSG_ID_POINT_MIN_LEN 14
#define MAVLINK_MSG_ID_6_LEN 14
#define MAVLINK_MSG_ID_6_MIN_LEN 14

#define MAVLINK_MSG_ID_POINT_CRC 144
#define MAVLINK_MSG_ID_6_CRC 144



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_POINT { \
    6, \
    "POINT", \
    4, \
    {  { "duration", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_point_t, duration) }, \
         { "point_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_point_t, point_id) }, \
         { "setpoint_x", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_point_t, setpoint_x) }, \
         { "setpoint_y", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_point_t, setpoint_y) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_POINT { \
    "POINT", \
    4, \
    {  { "duration", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_point_t, duration) }, \
         { "point_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_point_t, point_id) }, \
         { "setpoint_x", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_point_t, setpoint_x) }, \
         { "setpoint_y", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_point_t, setpoint_y) }, \
         } \
}
#endif

/**
 * @brief Pack a point message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param duration  Time during which the setpoint need to be kept
 * @param point_id  point ID
 * @param setpoint_x  Speed setpoint in x direction
 * @param setpoint_y  Speed setpoint in y direction
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_point_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t duration, uint16_t point_id, float setpoint_x, float setpoint_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POINT_LEN];
    _mav_put_uint32_t(buf, 0, duration);
    _mav_put_float(buf, 4, setpoint_x);
    _mav_put_float(buf, 8, setpoint_y);
    _mav_put_uint16_t(buf, 12, point_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POINT_LEN);
#else
    mavlink_point_t packet;
    packet.duration = duration;
    packet.setpoint_x = setpoint_x;
    packet.setpoint_y = setpoint_y;
    packet.point_id = point_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_POINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_POINT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_POINT_MIN_LEN, MAVLINK_MSG_ID_POINT_LEN, MAVLINK_MSG_ID_POINT_CRC);
}

/**
 * @brief Pack a point message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param duration  Time during which the setpoint need to be kept
 * @param point_id  point ID
 * @param setpoint_x  Speed setpoint in x direction
 * @param setpoint_y  Speed setpoint in y direction
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_point_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t duration,uint16_t point_id,float setpoint_x,float setpoint_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POINT_LEN];
    _mav_put_uint32_t(buf, 0, duration);
    _mav_put_float(buf, 4, setpoint_x);
    _mav_put_float(buf, 8, setpoint_y);
    _mav_put_uint16_t(buf, 12, point_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POINT_LEN);
#else
    mavlink_point_t packet;
    packet.duration = duration;
    packet.setpoint_x = setpoint_x;
    packet.setpoint_y = setpoint_y;
    packet.point_id = point_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_POINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_POINT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_POINT_MIN_LEN, MAVLINK_MSG_ID_POINT_LEN, MAVLINK_MSG_ID_POINT_CRC);
}

/**
 * @brief Encode a point struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param point C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_point_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_point_t* point)
{
    return mavlink_msg_point_pack(system_id, component_id, msg, point->duration, point->point_id, point->setpoint_x, point->setpoint_y);
}

/**
 * @brief Encode a point struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param point C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_point_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_point_t* point)
{
    return mavlink_msg_point_pack_chan(system_id, component_id, chan, msg, point->duration, point->point_id, point->setpoint_x, point->setpoint_y);
}

/**
 * @brief Send a point message
 * @param chan MAVLink channel to send the message
 *
 * @param duration  Time during which the setpoint need to be kept
 * @param point_id  point ID
 * @param setpoint_x  Speed setpoint in x direction
 * @param setpoint_y  Speed setpoint in y direction
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_point_send(mavlink_channel_t chan, uint32_t duration, uint16_t point_id, float setpoint_x, float setpoint_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POINT_LEN];
    _mav_put_uint32_t(buf, 0, duration);
    _mav_put_float(buf, 4, setpoint_x);
    _mav_put_float(buf, 8, setpoint_y);
    _mav_put_uint16_t(buf, 12, point_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT, buf, MAVLINK_MSG_ID_POINT_MIN_LEN, MAVLINK_MSG_ID_POINT_LEN, MAVLINK_MSG_ID_POINT_CRC);
#else
    mavlink_point_t packet;
    packet.duration = duration;
    packet.setpoint_x = setpoint_x;
    packet.setpoint_y = setpoint_y;
    packet.point_id = point_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT, (const char *)&packet, MAVLINK_MSG_ID_POINT_MIN_LEN, MAVLINK_MSG_ID_POINT_LEN, MAVLINK_MSG_ID_POINT_CRC);
#endif
}

/**
 * @brief Send a point message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_point_send_struct(mavlink_channel_t chan, const mavlink_point_t* point)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_point_send(chan, point->duration, point->point_id, point->setpoint_x, point->setpoint_y);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT, (const char *)point, MAVLINK_MSG_ID_POINT_MIN_LEN, MAVLINK_MSG_ID_POINT_LEN, MAVLINK_MSG_ID_POINT_CRC);
#endif
}

#if MAVLINK_MSG_ID_POINT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_point_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t duration, uint16_t point_id, float setpoint_x, float setpoint_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, duration);
    _mav_put_float(buf, 4, setpoint_x);
    _mav_put_float(buf, 8, setpoint_y);
    _mav_put_uint16_t(buf, 12, point_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT, buf, MAVLINK_MSG_ID_POINT_MIN_LEN, MAVLINK_MSG_ID_POINT_LEN, MAVLINK_MSG_ID_POINT_CRC);
#else
    mavlink_point_t *packet = (mavlink_point_t *)msgbuf;
    packet->duration = duration;
    packet->setpoint_x = setpoint_x;
    packet->setpoint_y = setpoint_y;
    packet->point_id = point_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT, (const char *)packet, MAVLINK_MSG_ID_POINT_MIN_LEN, MAVLINK_MSG_ID_POINT_LEN, MAVLINK_MSG_ID_POINT_CRC);
#endif
}
#endif

#endif

// MESSAGE POINT UNPACKING


/**
 * @brief Get field duration from point message
 *
 * @return  Time during which the setpoint need to be kept
 */
static inline uint32_t mavlink_msg_point_get_duration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field point_id from point message
 *
 * @return  point ID
 */
static inline uint16_t mavlink_msg_point_get_point_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field setpoint_x from point message
 *
 * @return  Speed setpoint in x direction
 */
static inline float mavlink_msg_point_get_setpoint_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field setpoint_y from point message
 *
 * @return  Speed setpoint in y direction
 */
static inline float mavlink_msg_point_get_setpoint_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a point message into a struct
 *
 * @param msg The message to decode
 * @param point C-struct to decode the message contents into
 */
static inline void mavlink_msg_point_decode(const mavlink_message_t* msg, mavlink_point_t* point)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    point->duration = mavlink_msg_point_get_duration(msg);
    point->setpoint_x = mavlink_msg_point_get_setpoint_x(msg);
    point->setpoint_y = mavlink_msg_point_get_setpoint_y(msg);
    point->point_id = mavlink_msg_point_get_point_id(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_POINT_LEN? msg->len : MAVLINK_MSG_ID_POINT_LEN;
        memset(point, 0, MAVLINK_MSG_ID_POINT_LEN);
    memcpy(point, _MAV_PAYLOAD(msg), len);
#endif
}
