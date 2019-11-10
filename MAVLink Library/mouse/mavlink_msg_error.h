#pragma once
// MESSAGE ERROR PACKING

#define MAVLINK_MSG_ID_ERROR 7

MAVPACKED(
typedef struct __mavlink_error_t {
 uint8_t error; /*<  error ID*/
}) mavlink_error_t;

#define MAVLINK_MSG_ID_ERROR_LEN 1
#define MAVLINK_MSG_ID_ERROR_MIN_LEN 1
#define MAVLINK_MSG_ID_7_LEN 1
#define MAVLINK_MSG_ID_7_MIN_LEN 1

#define MAVLINK_MSG_ID_ERROR_CRC 124
#define MAVLINK_MSG_ID_7_CRC 124



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ERROR { \
    7, \
    "ERROR", \
    1, \
    {  { "error", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_error_t, error) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ERROR { \
    "ERROR", \
    1, \
    {  { "error", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_error_t, error) }, \
         } \
}
#endif

/**
 * @brief Pack a error message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param error  error ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_error_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ERROR_LEN];
    _mav_put_uint8_t(buf, 0, error);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ERROR_LEN);
#else
    mavlink_error_t packet;
    packet.error = error;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ERROR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ERROR;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ERROR_MIN_LEN, MAVLINK_MSG_ID_ERROR_LEN, MAVLINK_MSG_ID_ERROR_CRC);
}

/**
 * @brief Pack a error message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param error  error ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_error_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ERROR_LEN];
    _mav_put_uint8_t(buf, 0, error);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ERROR_LEN);
#else
    mavlink_error_t packet;
    packet.error = error;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ERROR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ERROR;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ERROR_MIN_LEN, MAVLINK_MSG_ID_ERROR_LEN, MAVLINK_MSG_ID_ERROR_CRC);
}

/**
 * @brief Encode a error struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param error C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_error_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_error_t* error)
{
    return mavlink_msg_error_pack(system_id, component_id, msg, error->error);
}

/**
 * @brief Encode a error struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param error C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_error_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_error_t* error)
{
    return mavlink_msg_error_pack_chan(system_id, component_id, chan, msg, error->error);
}

/**
 * @brief Send a error message
 * @param chan MAVLink channel to send the message
 *
 * @param error  error ID
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_error_send(mavlink_channel_t chan, uint8_t error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ERROR_LEN];
    _mav_put_uint8_t(buf, 0, error);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ERROR, buf, MAVLINK_MSG_ID_ERROR_MIN_LEN, MAVLINK_MSG_ID_ERROR_LEN, MAVLINK_MSG_ID_ERROR_CRC);
#else
    mavlink_error_t packet;
    packet.error = error;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ERROR, (const char *)&packet, MAVLINK_MSG_ID_ERROR_MIN_LEN, MAVLINK_MSG_ID_ERROR_LEN, MAVLINK_MSG_ID_ERROR_CRC);
#endif
}

/**
 * @brief Send a error message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_error_send_struct(mavlink_channel_t chan, const mavlink_error_t* error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_error_send(chan, error->error);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ERROR, (const char *)error, MAVLINK_MSG_ID_ERROR_MIN_LEN, MAVLINK_MSG_ID_ERROR_LEN, MAVLINK_MSG_ID_ERROR_CRC);
#endif
}

#if MAVLINK_MSG_ID_ERROR_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_error_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, error);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ERROR, buf, MAVLINK_MSG_ID_ERROR_MIN_LEN, MAVLINK_MSG_ID_ERROR_LEN, MAVLINK_MSG_ID_ERROR_CRC);
#else
    mavlink_error_t *packet = (mavlink_error_t *)msgbuf;
    packet->error = error;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ERROR, (const char *)packet, MAVLINK_MSG_ID_ERROR_MIN_LEN, MAVLINK_MSG_ID_ERROR_LEN, MAVLINK_MSG_ID_ERROR_CRC);
#endif
}
#endif

#endif

// MESSAGE ERROR UNPACKING


/**
 * @brief Get field error from error message
 *
 * @return  error ID
 */
static inline uint8_t mavlink_msg_error_get_error(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a error message into a struct
 *
 * @param msg The message to decode
 * @param error C-struct to decode the message contents into
 */
static inline void mavlink_msg_error_decode(const mavlink_message_t* msg, mavlink_error_t* error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    error->error = mavlink_msg_error_get_error(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ERROR_LEN? msg->len : MAVLINK_MSG_ID_ERROR_LEN;
        memset(error, 0, MAVLINK_MSG_ID_ERROR_LEN);
    memcpy(error, _MAV_PAYLOAD(msg), len);
#endif
}
