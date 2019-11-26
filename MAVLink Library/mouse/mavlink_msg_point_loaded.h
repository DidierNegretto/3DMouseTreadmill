#pragma once
// MESSAGE POINT_LOADED PACKING

#define MAVLINK_MSG_ID_POINT_LOADED 5

MAVPACKED(
typedef struct __mavlink_point_loaded_t {
 uint16_t point_id; /*<  Last ID of point loaded*/
}) mavlink_point_loaded_t;

#define MAVLINK_MSG_ID_POINT_LOADED_LEN 2
#define MAVLINK_MSG_ID_POINT_LOADED_MIN_LEN 2
#define MAVLINK_MSG_ID_5_LEN 2
#define MAVLINK_MSG_ID_5_MIN_LEN 2

#define MAVLINK_MSG_ID_POINT_LOADED_CRC 167
#define MAVLINK_MSG_ID_5_CRC 167



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_POINT_LOADED { \
    5, \
    "POINT_LOADED", \
    1, \
    {  { "point_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_point_loaded_t, point_id) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_POINT_LOADED { \
    "POINT_LOADED", \
    1, \
    {  { "point_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_point_loaded_t, point_id) }, \
         } \
}
#endif

/**
 * @brief Pack a point_loaded message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param point_id  Last ID of point loaded
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_point_loaded_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t point_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POINT_LOADED_LEN];
    _mav_put_uint16_t(buf, 0, point_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POINT_LOADED_LEN);
#else
    mavlink_point_loaded_t packet;
    packet.point_id = point_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_POINT_LOADED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_POINT_LOADED;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_POINT_LOADED_MIN_LEN, MAVLINK_MSG_ID_POINT_LOADED_LEN, MAVLINK_MSG_ID_POINT_LOADED_CRC);
}

/**
 * @brief Pack a point_loaded message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param point_id  Last ID of point loaded
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_point_loaded_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t point_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POINT_LOADED_LEN];
    _mav_put_uint16_t(buf, 0, point_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POINT_LOADED_LEN);
#else
    mavlink_point_loaded_t packet;
    packet.point_id = point_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_POINT_LOADED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_POINT_LOADED;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_POINT_LOADED_MIN_LEN, MAVLINK_MSG_ID_POINT_LOADED_LEN, MAVLINK_MSG_ID_POINT_LOADED_CRC);
}

/**
 * @brief Encode a point_loaded struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param point_loaded C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_point_loaded_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_point_loaded_t* point_loaded)
{
    return mavlink_msg_point_loaded_pack(system_id, component_id, msg, point_loaded->point_id);
}

/**
 * @brief Encode a point_loaded struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param point_loaded C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_point_loaded_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_point_loaded_t* point_loaded)
{
    return mavlink_msg_point_loaded_pack_chan(system_id, component_id, chan, msg, point_loaded->point_id);
}

/**
 * @brief Send a point_loaded message
 * @param chan MAVLink channel to send the message
 *
 * @param point_id  Last ID of point loaded
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_point_loaded_send(mavlink_channel_t chan, uint16_t point_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POINT_LOADED_LEN];
    _mav_put_uint16_t(buf, 0, point_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT_LOADED, buf, MAVLINK_MSG_ID_POINT_LOADED_MIN_LEN, MAVLINK_MSG_ID_POINT_LOADED_LEN, MAVLINK_MSG_ID_POINT_LOADED_CRC);
#else
    mavlink_point_loaded_t packet;
    packet.point_id = point_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT_LOADED, (const char *)&packet, MAVLINK_MSG_ID_POINT_LOADED_MIN_LEN, MAVLINK_MSG_ID_POINT_LOADED_LEN, MAVLINK_MSG_ID_POINT_LOADED_CRC);
#endif
}

/**
 * @brief Send a point_loaded message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_point_loaded_send_struct(mavlink_channel_t chan, const mavlink_point_loaded_t* point_loaded)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_point_loaded_send(chan, point_loaded->point_id);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT_LOADED, (const char *)point_loaded, MAVLINK_MSG_ID_POINT_LOADED_MIN_LEN, MAVLINK_MSG_ID_POINT_LOADED_LEN, MAVLINK_MSG_ID_POINT_LOADED_CRC);
#endif
}

#if MAVLINK_MSG_ID_POINT_LOADED_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_point_loaded_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t point_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, point_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT_LOADED, buf, MAVLINK_MSG_ID_POINT_LOADED_MIN_LEN, MAVLINK_MSG_ID_POINT_LOADED_LEN, MAVLINK_MSG_ID_POINT_LOADED_CRC);
#else
    mavlink_point_loaded_t *packet = (mavlink_point_loaded_t *)msgbuf;
    packet->point_id = point_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POINT_LOADED, (const char *)packet, MAVLINK_MSG_ID_POINT_LOADED_MIN_LEN, MAVLINK_MSG_ID_POINT_LOADED_LEN, MAVLINK_MSG_ID_POINT_LOADED_CRC);
#endif
}
#endif

#endif

// MESSAGE POINT_LOADED UNPACKING


/**
 * @brief Get field point_id from point_loaded message
 *
 * @return  Last ID of point loaded
 */
static inline uint16_t mavlink_msg_point_loaded_get_point_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a point_loaded message into a struct
 *
 * @param msg The message to decode
 * @param point_loaded C-struct to decode the message contents into
 */
static inline void mavlink_msg_point_loaded_decode(const mavlink_message_t* msg, mavlink_point_loaded_t* point_loaded)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    point_loaded->point_id = mavlink_msg_point_loaded_get_point_id(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_POINT_LOADED_LEN? msg->len : MAVLINK_MSG_ID_POINT_LOADED_LEN;
        memset(point_loaded, 0, MAVLINK_MSG_ID_POINT_LOADED_LEN);
    memcpy(point_loaded, _MAV_PAYLOAD(msg), len);
#endif
}
