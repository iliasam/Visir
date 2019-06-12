#ifndef MAVLINK_HANDLING_H
#define MAVLINK_HANDLING_H

#include "config.h"
#include "bno080_sensor_parsing.h"
#include <stdint.h>

// Defines ********************************************************************

// Functions ******************************************************************
void mavlink_parse_byte(uint8_t value);
void mavlink_send_rotation_vector(euler_angles_t* angles);
void mavlink_send_game_rotation_vector(euler_angles_t* angles);
void mavlink_send_quaternion(quaternion_t* quaternion);
void mavlink_send_key_event(uint8_t key_code, uint8_t key_event);
void mavlink_send_battery_state(float voltage);

#endif
