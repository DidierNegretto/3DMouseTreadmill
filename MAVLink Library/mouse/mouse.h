/** @file
 *  @brief MAVLink comm protocol generated from mouse.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_MOUSE_H
#define MAVLINK_MOUSE_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_MOUSE.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 137, 5, 5, 0, 0, 0}, {1, 202, 16, 16, 0, 0, 0}, {2, 129, 12, 12, 0, 0, 0}, {3, 188, 1, 1, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_MOUSE

// ENUM DEFINITIONS


/** @brief This enum defines the mode to be used */
#ifndef HAVE_ENUM_MOUSE_MODE
#define HAVE_ENUM_MOUSE_MODE
typedef enum MOUSE_MODE
{
   MOUSE_MODE_STOP=0, /* All motion of mouse treadmill is stopped | */
   MOUSE_MODE_SPEED=1, /* Constanst speed is applied. Speed selected by PC message SPEED_SETPOINT. | */
   MOUSE_MODE_AUTO=2, /* Predefined speed profile is applied | */
   MOUSE_MODE_ENUM_END=3, /*  | */
} MOUSE_MODE;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_heartbeat.h"
#include "./mavlink_msg_speed_info.h"
#include "./mavlink_msg_speed_setpoint.h"
#include "./mavlink_msg_mode_selection.h"

// base include


#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#if MAVLINK_THIS_XML_IDX == MAVLINK_PRIMARY_XML_IDX
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_SPEED_INFO, MAVLINK_MESSAGE_INFO_SPEED_SETPOINT, MAVLINK_MESSAGE_INFO_MODE_SELECTION}
# define MAVLINK_MESSAGE_NAMES {{ "HEARTBEAT", 0 }, { "MODE_SELECTION", 3 }, { "SPEED_INFO", 1 }, { "SPEED_SETPOINT", 2 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_MOUSE_H
