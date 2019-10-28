#pragma once
// MESSAGE MODE_SELECTION PACKING

#define MAVLINK_MSG_ID_MODE_SELECTION 3

MAVPACKED(
typedef struct __mavlink_mode_selection_t {
 uint8_t mode; /*<  Actual operating mode*/
}) mavlink_mode_selection_t;

#define MAVLINK_MSG_ID_MODE_SELECTION_LEN 1
#define MAVLINK_MSG_ID_MODE_SELECTION_MIN_LEN 1
#define MAVLINK_MSG_ID_3_LEN 1
#define MAVLINK_MSG_ID_3_MIN_LEN 1

#define MAVLINK_MSG_ID_MODE_SELECTION_CRC 188
#define MAVLINK_MSG_ID_3_CRC 188



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MODE_SELECTION { \
    3, \
    "MODE_SELECTION", \
    1, \
    {  { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mode_selection_t, mode) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MODE_SELECTION { \
    "MODE_SELECTION", \
    1, \
    {  { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mode_selection_t, mode) }, \
         } \
}
#endif

/**
 * @brief Pack a mode_selection message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mode  Actual operating mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mode_selection_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MODE_SELECTION_LEN];
    _mav_put_uint8_t(buf, 0, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MODE_SELECTION_LEN);
#else
    mavlink_mode_selection_t packet;
    packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MODE_SELECTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MODE_SELECTION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MODE_SELECTION_MIN_LEN, MAVLINK_MSG_ID_MODE_SELECTION_LEN, MAVLINK_MSG_ID_MODE_SELECTION_CRC);
}

/**
 * @brief Pack a mode_selection message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mode  Actual operating mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mode_selection_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MODE_SELECTION_LEN];
    _mav_put_uint8_t(buf, 0, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MODE_SELECTION_LEN);
#else
    mavlink_mode_selection_t packet;
    packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MODE_SELECTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MODE_SELECTION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MODE_SELECTION_MIN_LEN, MAVLINK_MSG_ID_MODE_SELECTION_LEN, MAVLINK_MSG_ID_MODE_SELECTION_CRC);
}

/**
 * @brief Encode a mode_selection struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mode_selection C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mode_selection_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mode_selection_t* mode_selection)
{
    return mavlink_msg_mode_selection_pack(system_id, component_id, msg, mode_selection->mode);
}

/**
 * @brief Encode a mode_selection struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mode_selection C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mode_selection_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mode_selection_t* mode_selection)
{
    return mavlink_msg_mode_selection_pack_chan(system_id, component_id, chan, msg, mode_selection->mode);
}

/**
 * @brief Send a mode_selection message
 * @param chan MAVLink channel to send the message
 *
 * @param mode  Actual operating mode
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mode_selection_send(mavlink_channel_t chan, uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MODE_SELECTION_LEN];
    _mav_put_uint8_t(buf, 0, mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MODE_SELECTION, buf, MAVLINK_MSG_ID_MODE_SELECTION_MIN_LEN, MAVLINK_MSG_ID_MODE_SELECTION_LEN, MAVLINK_MSG_ID_MODE_SELECTION_CRC);
#else
    mavlink_mode_selection_t packet;
    packet.mode = mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MODE_SELECTION, (const char *)&packet, MAVLINK_MSG_ID_MODE_SELECTION_MIN_LEN, MAVLINK_MSG_ID_MODE_SELECTION_LEN, MAVLINK_MSG_ID_MODE_SELECTION_CRC);
#endif
}

/**
 * @brief Send a mode_selection message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mode_selection_send_struct(mavlink_channel_t chan, const mavlink_mode_selection_t* mode_selection)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mode_selection_send(chan, mode_selection->mode);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MODE_SELECTION, (const char *)mode_selection, MAVLINK_MSG_ID_MODE_SELECTION_MIN_LEN, MAVLINK_MSG_ID_MODE_SELECTION_LEN, MAVLINK_MSG_ID_MODE_SELECTION_CRC);
#endif
}

#if MAVLINK_MSG_ID_MODE_SELECTION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mode_selection_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MODE_SELECTION, buf, MAVLINK_MSG_ID_MODE_SELECTION_MIN_LEN, MAVLINK_MSG_ID_MODE_SELECTION_LEN, MAVLINK_MSG_ID_MODE_SELECTION_CRC);
#else
    mavlink_mode_selection_t *packet = (mavlink_mode_selection_t *)msgbuf;
    packet->mode = mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MODE_SELECTION, (const char *)packet, MAVLINK_MSG_ID_MODE_SELECTION_MIN_LEN, MAVLINK_MSG_ID_MODE_SELECTION_LEN, MAVLINK_MSG_ID_MODE_SELECTION_CRC);
#endif
}
#endif

#endif

// MESSAGE MODE_SELECTION UNPACKING


/**
 * @brief Get field mode from mode_selection message
 *
 * @return  Actual operating mode
 */
static inline uint8_t mavlink_msg_mode_selection_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a mode_selection message into a struct
 *
 * @param msg The message to decode
 * @param mode_selection C-struct to decode the message contents into
 */
static inline void mavlink_msg_mode_selection_decode(const mavlink_message_t* msg, mavlink_mode_selection_t* mode_selection)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mode_selection->mode = mavlink_msg_mode_selection_get_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MODE_SELECTION_LEN? msg->len : MAVLINK_MSG_ID_MODE_SELECTION_LEN;
        memset(mode_selection, 0, MAVLINK_MSG_ID_MODE_SELECTION_LEN);
    memcpy(mode_selection, _MAV_PAYLOAD(msg), len);
#endif
}
