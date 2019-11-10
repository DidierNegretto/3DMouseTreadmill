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
#define MAVLINK_MESSAGE_CRCS {{0, 137, 5, 5, 0, 0, 0}, {1, 76, 12, 12, 0, 0, 0}, {2, 38, 8, 8, 0, 0, 0}, {3, 188, 1, 1, 0, 0, 0}, {4, 112, 12, 12, 0, 0, 0}, {5, 155, 1, 1, 0, 0, 0}, {6, 75, 13, 13, 0, 0, 0}, {7, 22, 5, 5, 0, 0, 0}}
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
   MOUSE_MODE_AUTO_LOAD=2, /* Predefined speed profile is loaded | */
   MOUSE_MODE_AUTO_RUN=3, /* Predefined speed profile is applied | */
   MOUSE_MODE_ENUM_END=4, /*  | */
} MOUSE_MODE;
#endif

/** @brief This enum defines the possible errors */
#ifndef HAVE_ENUM_MOUSE_ERROR
#define HAVE_ENUM_MOUSE_ERROR
typedef enum MOUSE_ERROR
{
   MOTOR_ERROR=0, /* The motor driver flaged an error, this might be due to many sources, see datasheet of motor driver. | */
   MOTOR_LOW_SPEED=1, /* The speed setpoint chosen is too low to be achieved. | */
   MOTOR_HIGH_SPEED=2, /* The speed setpoint chosen is too high to be achieved. | */
   MOUSE_ROUTINE_TOO_LONG=3, /* More than 255 points have been defined in the mouse routine. | */
   MOUSE_ERROR_ENUM_END=4, /*  | */
} MOUSE_ERROR;
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
#include "./mavlink_msg_motor_setpoint.h"
#include "./mavlink_msg_point_loaded.h"
#include "./mavlink_msg_point.h"
#include "./mavlink_msg_error.h"

// base include


#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#if MAVLINK_THIS_XML_IDX == MAVLINK_PRIMARY_XML_IDX
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_SPEED_INFO, MAVLINK_MESSAGE_INFO_SPEED_SETPOINT, MAVLINK_MESSAGE_INFO_MODE_SELECTION, MAVLINK_MESSAGE_INFO_MOTOR_SETPOINT, MAVLINK_MESSAGE_INFO_POINT_LOADED, MAVLINK_MESSAGE_INFO_POINT, MAVLINK_MESSAGE_INFO_ERROR}
# define MAVLINK_MESSAGE_NAMES {{ "ERROR", 7 }, { "HEARTBEAT", 0 }, { "MODE_SELECTION", 3 }, { "MOTOR_SETPOINT", 4 }, { "POINT", 6 }, { "POINT_LOADED", 5 }, { "SPEED_INFO", 1 }, { "SPEED_SETPOINT", 2 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_MOUSE_H
