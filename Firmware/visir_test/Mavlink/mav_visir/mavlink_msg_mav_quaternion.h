#pragma once
// MESSAGE MAV_QUATERNION PACKING

#define MAVLINK_MSG_ID_MAV_QUATERNION 102

MAVPACKED(
typedef struct __mavlink_mav_quaternion_t {
 float x; /*< X*/
 float y; /*< Y*/
 float z; /*< Z*/
 float w; /*< W*/
}) mavlink_mav_quaternion_t;

#define MAVLINK_MSG_ID_MAV_QUATERNION_LEN 16
#define MAVLINK_MSG_ID_MAV_QUATERNION_MIN_LEN 16
#define MAVLINK_MSG_ID_102_LEN 16
#define MAVLINK_MSG_ID_102_MIN_LEN 16

#define MAVLINK_MSG_ID_MAV_QUATERNION_CRC 140
#define MAVLINK_MSG_ID_102_CRC 140



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_QUATERNION { \
    102, \
    "MAV_QUATERNION", \
    4, \
    {  { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_quaternion_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mav_quaternion_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mav_quaternion_t, z) }, \
         { "w", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_mav_quaternion_t, w) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_QUATERNION { \
    "MAV_QUATERNION", \
    4, \
    {  { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_quaternion_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mav_quaternion_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mav_quaternion_t, z) }, \
         { "w", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_mav_quaternion_t, w) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_quaternion message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x X
 * @param y Y
 * @param z Z
 * @param w W
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_quaternion_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float x, float y, float z, float w)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_QUATERNION_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_float(buf, 12, w);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_QUATERNION_LEN);
#else
    mavlink_mav_quaternion_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.w = w;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_QUATERNION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_QUATERNION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_QUATERNION_MIN_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_CRC);
}

/**
 * @brief Pack a mav_quaternion message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param x X
 * @param y Y
 * @param z Z
 * @param w W
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_quaternion_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float x,float y,float z,float w)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_QUATERNION_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_float(buf, 12, w);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_QUATERNION_LEN);
#else
    mavlink_mav_quaternion_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.w = w;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_QUATERNION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_QUATERNION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_QUATERNION_MIN_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_CRC);
}

/**
 * @brief Encode a mav_quaternion struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_quaternion C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_quaternion_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_quaternion_t* mav_quaternion)
{
    return mavlink_msg_mav_quaternion_pack(system_id, component_id, msg, mav_quaternion->x, mav_quaternion->y, mav_quaternion->z, mav_quaternion->w);
}

/**
 * @brief Encode a mav_quaternion struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_quaternion C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_quaternion_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_quaternion_t* mav_quaternion)
{
    return mavlink_msg_mav_quaternion_pack_chan(system_id, component_id, chan, msg, mav_quaternion->x, mav_quaternion->y, mav_quaternion->z, mav_quaternion->w);
}

/**
 * @brief Send a mav_quaternion message
 * @param chan MAVLink channel to send the message
 *
 * @param x X
 * @param y Y
 * @param z Z
 * @param w W
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_quaternion_send(mavlink_channel_t chan, float x, float y, float z, float w)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_QUATERNION_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_float(buf, 12, w);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_QUATERNION, buf, MAVLINK_MSG_ID_MAV_QUATERNION_MIN_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_CRC);
#else
    mavlink_mav_quaternion_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.w = w;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_QUATERNION, (const char *)&packet, MAVLINK_MSG_ID_MAV_QUATERNION_MIN_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_CRC);
#endif
}

/**
 * @brief Send a mav_quaternion message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_quaternion_send_struct(mavlink_channel_t chan, const mavlink_mav_quaternion_t* mav_quaternion)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_quaternion_send(chan, mav_quaternion->x, mav_quaternion->y, mav_quaternion->z, mav_quaternion->w);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_QUATERNION, (const char *)mav_quaternion, MAVLINK_MSG_ID_MAV_QUATERNION_MIN_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_QUATERNION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_quaternion_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float x, float y, float z, float w)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_float(buf, 12, w);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_QUATERNION, buf, MAVLINK_MSG_ID_MAV_QUATERNION_MIN_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_CRC);
#else
    mavlink_mav_quaternion_t *packet = (mavlink_mav_quaternion_t *)msgbuf;
    packet->x = x;
    packet->y = y;
    packet->z = z;
    packet->w = w;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_QUATERNION, (const char *)packet, MAVLINK_MSG_ID_MAV_QUATERNION_MIN_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_LEN, MAVLINK_MSG_ID_MAV_QUATERNION_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_QUATERNION UNPACKING


/**
 * @brief Get field x from mav_quaternion message
 *
 * @return X
 */
static inline float mavlink_msg_mav_quaternion_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field y from mav_quaternion message
 *
 * @return Y
 */
static inline float mavlink_msg_mav_quaternion_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field z from mav_quaternion message
 *
 * @return Z
 */
static inline float mavlink_msg_mav_quaternion_get_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field w from mav_quaternion message
 *
 * @return W
 */
static inline float mavlink_msg_mav_quaternion_get_w(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a mav_quaternion message into a struct
 *
 * @param msg The message to decode
 * @param mav_quaternion C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_quaternion_decode(const mavlink_message_t* msg, mavlink_mav_quaternion_t* mav_quaternion)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_quaternion->x = mavlink_msg_mav_quaternion_get_x(msg);
    mav_quaternion->y = mavlink_msg_mav_quaternion_get_y(msg);
    mav_quaternion->z = mavlink_msg_mav_quaternion_get_z(msg);
    mav_quaternion->w = mavlink_msg_mav_quaternion_get_w(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_QUATERNION_LEN? msg->len : MAVLINK_MSG_ID_MAV_QUATERNION_LEN;
        memset(mav_quaternion, 0, MAVLINK_MSG_ID_MAV_QUATERNION_LEN);
    memcpy(mav_quaternion, _MAV_PAYLOAD(msg), len);
#endif
}
