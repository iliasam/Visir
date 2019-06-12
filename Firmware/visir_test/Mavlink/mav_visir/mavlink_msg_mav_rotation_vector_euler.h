#pragma once
// MESSAGE MAV_ROTATION_VECTOR_EULER PACKING

#define MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER 100

MAVPACKED(
typedef struct __mavlink_mav_rotation_vector_euler_t {
 float roll; /*< Roll, deg*/
 float pitch; /*< Pitch, deg*/
 float yaw; /*< Yaw, deg*/
 float accur; /*< Accuracy, deg*/
 uint8_t state; /*< State*/
}) mavlink_mav_rotation_vector_euler_t;

#define MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN 17
#define MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_MIN_LEN 17
#define MAVLINK_MSG_ID_100_LEN 17
#define MAVLINK_MSG_ID_100_MIN_LEN 17

#define MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_CRC 134
#define MAVLINK_MSG_ID_100_CRC 134



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_ROTATION_VECTOR_EULER { \
    100, \
    "MAV_ROTATION_VECTOR_EULER", \
    5, \
    {  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_rotation_vector_euler_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mav_rotation_vector_euler_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mav_rotation_vector_euler_t, yaw) }, \
         { "accur", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_mav_rotation_vector_euler_t, accur) }, \
         { "state", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_mav_rotation_vector_euler_t, state) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_ROTATION_VECTOR_EULER { \
    "MAV_ROTATION_VECTOR_EULER", \
    5, \
    {  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_rotation_vector_euler_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mav_rotation_vector_euler_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mav_rotation_vector_euler_t, yaw) }, \
         { "accur", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_mav_rotation_vector_euler_t, accur) }, \
         { "state", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_mav_rotation_vector_euler_t, state) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_rotation_vector_euler message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll Roll, deg
 * @param pitch Pitch, deg
 * @param yaw Yaw, deg
 * @param accur Accuracy, deg
 * @param state State
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_rotation_vector_euler_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float roll, float pitch, float yaw, float accur, uint8_t state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, yaw);
    _mav_put_float(buf, 12, accur);
    _mav_put_uint8_t(buf, 16, state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN);
#else
    mavlink_mav_rotation_vector_euler_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.accur = accur;
    packet.state = state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_MIN_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_CRC);
}

/**
 * @brief Pack a mav_rotation_vector_euler message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll Roll, deg
 * @param pitch Pitch, deg
 * @param yaw Yaw, deg
 * @param accur Accuracy, deg
 * @param state State
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_rotation_vector_euler_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float roll,float pitch,float yaw,float accur,uint8_t state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, yaw);
    _mav_put_float(buf, 12, accur);
    _mav_put_uint8_t(buf, 16, state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN);
#else
    mavlink_mav_rotation_vector_euler_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.accur = accur;
    packet.state = state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_MIN_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_CRC);
}

/**
 * @brief Encode a mav_rotation_vector_euler struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_rotation_vector_euler C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_rotation_vector_euler_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_rotation_vector_euler_t* mav_rotation_vector_euler)
{
    return mavlink_msg_mav_rotation_vector_euler_pack(system_id, component_id, msg, mav_rotation_vector_euler->roll, mav_rotation_vector_euler->pitch, mav_rotation_vector_euler->yaw, mav_rotation_vector_euler->accur, mav_rotation_vector_euler->state);
}

/**
 * @brief Encode a mav_rotation_vector_euler struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_rotation_vector_euler C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_rotation_vector_euler_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_rotation_vector_euler_t* mav_rotation_vector_euler)
{
    return mavlink_msg_mav_rotation_vector_euler_pack_chan(system_id, component_id, chan, msg, mav_rotation_vector_euler->roll, mav_rotation_vector_euler->pitch, mav_rotation_vector_euler->yaw, mav_rotation_vector_euler->accur, mav_rotation_vector_euler->state);
}

/**
 * @brief Send a mav_rotation_vector_euler message
 * @param chan MAVLink channel to send the message
 *
 * @param roll Roll, deg
 * @param pitch Pitch, deg
 * @param yaw Yaw, deg
 * @param accur Accuracy, deg
 * @param state State
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_rotation_vector_euler_send(mavlink_channel_t chan, float roll, float pitch, float yaw, float accur, uint8_t state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, yaw);
    _mav_put_float(buf, 12, accur);
    _mav_put_uint8_t(buf, 16, state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER, buf, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_MIN_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_CRC);
#else
    mavlink_mav_rotation_vector_euler_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.accur = accur;
    packet.state = state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER, (const char *)&packet, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_MIN_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_CRC);
#endif
}

/**
 * @brief Send a mav_rotation_vector_euler message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_rotation_vector_euler_send_struct(mavlink_channel_t chan, const mavlink_mav_rotation_vector_euler_t* mav_rotation_vector_euler)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_rotation_vector_euler_send(chan, mav_rotation_vector_euler->roll, mav_rotation_vector_euler->pitch, mav_rotation_vector_euler->yaw, mav_rotation_vector_euler->accur, mav_rotation_vector_euler->state);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER, (const char *)mav_rotation_vector_euler, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_MIN_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_rotation_vector_euler_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float roll, float pitch, float yaw, float accur, uint8_t state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, yaw);
    _mav_put_float(buf, 12, accur);
    _mav_put_uint8_t(buf, 16, state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER, buf, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_MIN_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_CRC);
#else
    mavlink_mav_rotation_vector_euler_t *packet = (mavlink_mav_rotation_vector_euler_t *)msgbuf;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->yaw = yaw;
    packet->accur = accur;
    packet->state = state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER, (const char *)packet, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_MIN_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_ROTATION_VECTOR_EULER UNPACKING


/**
 * @brief Get field roll from mav_rotation_vector_euler message
 *
 * @return Roll, deg
 */
static inline float mavlink_msg_mav_rotation_vector_euler_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pitch from mav_rotation_vector_euler message
 *
 * @return Pitch, deg
 */
static inline float mavlink_msg_mav_rotation_vector_euler_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field yaw from mav_rotation_vector_euler message
 *
 * @return Yaw, deg
 */
static inline float mavlink_msg_mav_rotation_vector_euler_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field accur from mav_rotation_vector_euler message
 *
 * @return Accuracy, deg
 */
static inline float mavlink_msg_mav_rotation_vector_euler_get_accur(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field state from mav_rotation_vector_euler message
 *
 * @return State
 */
static inline uint8_t mavlink_msg_mav_rotation_vector_euler_get_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Decode a mav_rotation_vector_euler message into a struct
 *
 * @param msg The message to decode
 * @param mav_rotation_vector_euler C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_rotation_vector_euler_decode(const mavlink_message_t* msg, mavlink_mav_rotation_vector_euler_t* mav_rotation_vector_euler)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_rotation_vector_euler->roll = mavlink_msg_mav_rotation_vector_euler_get_roll(msg);
    mav_rotation_vector_euler->pitch = mavlink_msg_mav_rotation_vector_euler_get_pitch(msg);
    mav_rotation_vector_euler->yaw = mavlink_msg_mav_rotation_vector_euler_get_yaw(msg);
    mav_rotation_vector_euler->accur = mavlink_msg_mav_rotation_vector_euler_get_accur(msg);
    mav_rotation_vector_euler->state = mavlink_msg_mav_rotation_vector_euler_get_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN? msg->len : MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN;
        memset(mav_rotation_vector_euler, 0, MAVLINK_MSG_ID_MAV_ROTATION_VECTOR_EULER_LEN);
    memcpy(mav_rotation_vector_euler, _MAV_PAYLOAD(msg), len);
#endif
}
