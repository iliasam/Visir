#pragma once
// MESSAGE MAV_SET_YAW_CORRECTION PACKING

#define MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION 105

MAVPACKED(
typedef struct __mavlink_mav_set_yaw_correction_t {
 float value; /*< Correction value, deg*/
 uint8_t vector_type; /*< Type of the vector*/
}) mavlink_mav_set_yaw_correction_t;

#define MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN 5
#define MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_MIN_LEN 5
#define MAVLINK_MSG_ID_105_LEN 5
#define MAVLINK_MSG_ID_105_MIN_LEN 5

#define MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_CRC 161
#define MAVLINK_MSG_ID_105_CRC 161



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_SET_YAW_CORRECTION { \
    105, \
    "MAV_SET_YAW_CORRECTION", \
    2, \
    {  { "vector_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_mav_set_yaw_correction_t, vector_type) }, \
         { "value", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_set_yaw_correction_t, value) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_SET_YAW_CORRECTION { \
    "MAV_SET_YAW_CORRECTION", \
    2, \
    {  { "vector_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_mav_set_yaw_correction_t, vector_type) }, \
         { "value", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_set_yaw_correction_t, value) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_set_yaw_correction message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param vector_type Type of the vector
 * @param value Correction value, deg
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_set_yaw_correction_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t vector_type, float value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN];
    _mav_put_float(buf, 0, value);
    _mav_put_uint8_t(buf, 4, vector_type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN);
#else
    mavlink_mav_set_yaw_correction_t packet;
    packet.value = value;
    packet.vector_type = vector_type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_CRC);
}

/**
 * @brief Pack a mav_set_yaw_correction message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param vector_type Type of the vector
 * @param value Correction value, deg
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_set_yaw_correction_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t vector_type,float value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN];
    _mav_put_float(buf, 0, value);
    _mav_put_uint8_t(buf, 4, vector_type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN);
#else
    mavlink_mav_set_yaw_correction_t packet;
    packet.value = value;
    packet.vector_type = vector_type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_CRC);
}

/**
 * @brief Encode a mav_set_yaw_correction struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_set_yaw_correction C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_set_yaw_correction_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_set_yaw_correction_t* mav_set_yaw_correction)
{
    return mavlink_msg_mav_set_yaw_correction_pack(system_id, component_id, msg, mav_set_yaw_correction->vector_type, mav_set_yaw_correction->value);
}

/**
 * @brief Encode a mav_set_yaw_correction struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_set_yaw_correction C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_set_yaw_correction_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_set_yaw_correction_t* mav_set_yaw_correction)
{
    return mavlink_msg_mav_set_yaw_correction_pack_chan(system_id, component_id, chan, msg, mav_set_yaw_correction->vector_type, mav_set_yaw_correction->value);
}

/**
 * @brief Send a mav_set_yaw_correction message
 * @param chan MAVLink channel to send the message
 *
 * @param vector_type Type of the vector
 * @param value Correction value, deg
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_set_yaw_correction_send(mavlink_channel_t chan, uint8_t vector_type, float value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN];
    _mav_put_float(buf, 0, value);
    _mav_put_uint8_t(buf, 4, vector_type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION, buf, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_CRC);
#else
    mavlink_mav_set_yaw_correction_t packet;
    packet.value = value;
    packet.vector_type = vector_type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION, (const char *)&packet, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_CRC);
#endif
}

/**
 * @brief Send a mav_set_yaw_correction message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_set_yaw_correction_send_struct(mavlink_channel_t chan, const mavlink_mav_set_yaw_correction_t* mav_set_yaw_correction)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_set_yaw_correction_send(chan, mav_set_yaw_correction->vector_type, mav_set_yaw_correction->value);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION, (const char *)mav_set_yaw_correction, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_set_yaw_correction_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t vector_type, float value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, value);
    _mav_put_uint8_t(buf, 4, vector_type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION, buf, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_CRC);
#else
    mavlink_mav_set_yaw_correction_t *packet = (mavlink_mav_set_yaw_correction_t *)msgbuf;
    packet->value = value;
    packet->vector_type = vector_type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION, (const char *)packet, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_SET_YAW_CORRECTION UNPACKING


/**
 * @brief Get field vector_type from mav_set_yaw_correction message
 *
 * @return Type of the vector
 */
static inline uint8_t mavlink_msg_mav_set_yaw_correction_get_vector_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field value from mav_set_yaw_correction message
 *
 * @return Correction value, deg
 */
static inline float mavlink_msg_mav_set_yaw_correction_get_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a mav_set_yaw_correction message into a struct
 *
 * @param msg The message to decode
 * @param mav_set_yaw_correction C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_set_yaw_correction_decode(const mavlink_message_t* msg, mavlink_mav_set_yaw_correction_t* mav_set_yaw_correction)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_set_yaw_correction->value = mavlink_msg_mav_set_yaw_correction_get_value(msg);
    mav_set_yaw_correction->vector_type = mavlink_msg_mav_set_yaw_correction_get_vector_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN? msg->len : MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN;
        memset(mav_set_yaw_correction, 0, MAVLINK_MSG_ID_MAV_SET_YAW_CORRECTION_LEN);
    memcpy(mav_set_yaw_correction, _MAV_PAYLOAD(msg), len);
#endif
}
