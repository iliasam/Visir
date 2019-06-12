//ILIASAM - 10.2018

#include "mavlink_handling.h"
#include "mavlink.h"
#include "bluetooth_comm.h"

// Defines ********************************************************************
#define MAVLINK_VISIR_ID        1
#define MAVLINK_IMU_ID          10


// Variables ******************************************************************


// Functions ******************************************************************
void mavlink_send_message(mavlink_message_t *msg);
void mavlink_parse_set_yaw_correction(mavlink_message_t* msg);


void mavlink_parse_byte(uint8_t value)
{
  mavlink_message_t msg;
  mavlink_status_t mavlink_status;
  
  if (mavlink_parse_char(0, value, &msg, &mavlink_status))
  {
    if (msg.msgid == MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION)
    {
      mavlink_parse_set_yaw_correction(&msg);
    }
  }
}

void mavlink_parse_set_yaw_correction(mavlink_message_t* msg)
{
  mavlink_mav_set_yaw_correction_t new_value;
  mavlink_msg_mav_set_yaw_correction_decode(msg, &new_value);
  
  bno080_set_yaw_correction(new_value.vector_type, new_value.value);
}

void mavlink_send_rotation_vector(euler_angles_t* angles)
{
  mavlink_mav_rotation_vector_euler_t euler_msg;
  
  euler_msg.roll = angles->roll;
  euler_msg.pitch = angles->pitch;
  euler_msg.yaw = angles->yaw;
  euler_msg.accur = angles->accur;
  euler_msg.state = angles->state;
  
  mavlink_message_t mav_msg;

  mavlink_msg_mav_rotation_vector_euler_encode(
            MAVLINK_VISIR_ID,
            MAVLINK_IMU_ID,
            &mav_msg,
            &euler_msg);
  
  mavlink_send_message(&mav_msg);
}

void mavlink_send_game_rotation_vector(euler_angles_t* angles)
{
  mavlink_mav_game_rotation_vector_euler_t euler_msg;
  
  euler_msg.roll = angles->roll;
  euler_msg.pitch = angles->pitch;
  euler_msg.yaw = angles->yaw;
  euler_msg.accur = angles->accur;
  euler_msg.state = angles->state;
  
  mavlink_message_t mav_msg;

  mavlink_msg_mav_game_rotation_vector_euler_encode(
            MAVLINK_VISIR_ID,
            MAVLINK_IMU_ID,
            &mav_msg,
            &euler_msg);
  
  mavlink_send_message(&mav_msg);
}

void mavlink_send_quaternion(quaternion_t* quaternion)
{
  mavlink_mav_quaternion_t quaternion_msg;
  
  quaternion_msg.x = quaternion->i;
  quaternion_msg.y = quaternion->j;
  quaternion_msg.z = quaternion->k;
  quaternion_msg.w = quaternion->real;
  
  mavlink_message_t mav_msg;

  mavlink_msg_mav_quaternion_encode(
            MAVLINK_VISIR_ID,
            MAVLINK_IMU_ID,
            &mav_msg,
            &quaternion_msg);
  
  mavlink_send_message(&mav_msg);
}

void mavlink_send_key_event(uint8_t key_code, uint8_t key_event)
{
  mavlink_mav_button_event_t key_msg;
  key_msg.button_code = key_code;
  key_msg.event_code = key_event;
  
  mavlink_message_t mav_msg;

  mavlink_msg_mav_button_event_encode(
            MAVLINK_VISIR_ID,
            MAVLINK_IMU_ID,
            &mav_msg,
            &key_msg);
  
  mavlink_send_message(&mav_msg);
}

void mavlink_send_battery_state(float voltage)
{
  mavlink_mav_batt_state_t battery_msg;
  battery_msg.voltage = voltage;
  battery_msg.state = 0;
  
  mavlink_message_t mav_msg;

  mavlink_msg_mav_batt_state_encode(
            MAVLINK_VISIR_ID,
            MAVLINK_IMU_ID,
            &mav_msg,
            &battery_msg);
  
  mavlink_send_message(&mav_msg);
}

// Отправить mavlink сообщение
void mavlink_send_message(mavlink_message_t *msg)
{
    if (msg == NULL)
        return;
            
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t size = mavlink_msg_to_send_buffer(buffer, msg);
    if (size > MAVLINK_MAX_PACKET_LEN)
        return;
    bluetooth_add_data_for_tx(buffer, size);
    //uart_handling_send_data(buffer, size);
}