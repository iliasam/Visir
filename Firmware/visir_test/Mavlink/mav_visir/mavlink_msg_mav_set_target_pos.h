#pragma once
// MESSAGE MAV_SET_TARGET_POS PACKING

#define MAVLINK_MSG_ID_MAV_SET_TARGET_POS 108

MAVPACKED(
typedef struct __mavlink_mav_set_target_pos_t {
 float yaw; /*< Yaw, deg*/
 float pitch; /*< Pitch, deg*/
}) mavlink_mav_set_target_pos_t;

#define MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN 8
#define MAVLINK_MSG_ID_MAV_SET_TARGET_POS_MIN_LEN 8
#define MAVLINK_MSG_ID_108_LEN 8
#define MAVLINK_MSG_ID_108_MIN_LEN 8

#define MAVLINK_MSG_ID_MAV_SET_TARGET_POS_CRC 166
#define MAVLINK_MSG_ID_108_CRC 166



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_SET_TARGET_POS { \
    108, \
    "MAV_SET_TARGET_POS", \
    2, \
    {  { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_set_target_pos_t, yaw) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mav_set_target_pos_t, pitch) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_SET_TARGET_POS { \
    "MAV_SET_TARGET_POS", \
    2, \
    {  { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_set_target_pos_t, yaw) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mav_set_target_pos_t, pitch) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_set_target_pos message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param yaw Yaw, deg
 * @param pitch Pitch, deg
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_set_target_pos_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float yaw, float pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN];
    _mav_put_float(buf, 0, yaw);
    _mav_put_float(buf, 4, pitch);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN);
#else
    mavlink_mav_set_target_pos_t packet;
    packet.yaw = yaw;
    packet.pitch = pitch;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SET_TARGET_POS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_CRC);
}

/**
 * @brief Pack a mav_set_target_pos message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param yaw Yaw, deg
 * @param pitch Pitch, deg
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_set_target_pos_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float yaw,float pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN];
    _mav_put_float(buf, 0, yaw);
    _mav_put_float(buf, 4, pitch);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN);
#else
    mavlink_mav_set_target_pos_t packet;
    packet.yaw = yaw;
    packet.pitch = pitch;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SET_TARGET_POS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_CRC);
}

/**
 * @brief Encode a mav_set_target_pos struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_set_target_pos C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_set_target_pos_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_set_target_pos_t* mav_set_target_pos)
{
    return mavlink_msg_mav_set_target_pos_pack(system_id, component_id, msg, mav_set_target_pos->yaw, mav_set_target_pos->pitch);
}

/**
 * @brief Encode a mav_set_target_pos struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_set_target_pos C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_set_target_pos_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_set_target_pos_t* mav_set_target_pos)
{
    return mavlink_msg_mav_set_target_pos_pack_chan(system_id, component_id, chan, msg, mav_set_target_pos->yaw, mav_set_target_pos->pitch);
}

/**
 * @brief Send a mav_set_target_pos message
 * @param chan MAVLink channel to send the message
 *
 * @param yaw Yaw, deg
 * @param pitch Pitch, deg
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_set_target_pos_send(mavlink_channel_t chan, float yaw, float pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN];
    _mav_put_float(buf, 0, yaw);
    _mav_put_float(buf, 4, pitch);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_TARGET_POS, buf, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_CRC);
#else
    mavlink_mav_set_target_pos_t packet;
    packet.yaw = yaw;
    packet.pitch = pitch;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_TARGET_POS, (const char *)&packet, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_CRC);
#endif
}

/**
 * @brief Send a mav_set_target_pos message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_set_target_pos_send_struct(mavlink_channel_t chan, const mavlink_mav_set_target_pos_t* mav_set_target_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_set_target_pos_send(chan, mav_set_target_pos->yaw, mav_set_target_pos->pitch);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_TARGET_POS, (const char *)mav_set_target_pos, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_set_target_pos_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float yaw, float pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, yaw);
    _mav_put_float(buf, 4, pitch);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_TARGET_POS, buf, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_CRC);
#else
    mavlink_mav_set_target_pos_t *packet = (mavlink_mav_set_target_pos_t *)msgbuf;
    packet->yaw = yaw;
    packet->pitch = pitch;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_TARGET_POS, (const char *)packet, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_SET_TARGET_POS UNPACKING


/**
 * @brief Get field yaw from mav_set_target_pos message
 *
 * @return Yaw, deg
 */
static inline float mavlink_msg_mav_set_target_pos_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pitch from mav_set_target_pos message
 *
 * @return Pitch, deg
 */
static inline float mavlink_msg_mav_set_target_pos_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a mav_set_target_pos message into a struct
 *
 * @param msg The message to decode
 * @param mav_set_target_pos C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_set_target_pos_decode(const mavlink_message_t* msg, mavlink_mav_set_target_pos_t* mav_set_target_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_set_target_pos->yaw = mavlink_msg_mav_set_target_pos_get_yaw(msg);
    mav_set_target_pos->pitch = mavlink_msg_mav_set_target_pos_get_pitch(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN? msg->len : MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN;
        memset(mav_set_target_pos, 0, MAVLINK_MSG_ID_MAV_SET_TARGET_POS_LEN);
    memcpy(mav_set_target_pos, _MAV_PAYLOAD(msg), len);
#endif
}
