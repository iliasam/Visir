#pragma once
// MESSAGE MAV_SET_CURSOR PACKING

#define MAVLINK_MSG_ID_MAV_SET_CURSOR 104

MAVPACKED(
typedef struct __mavlink_mav_set_cursor_t {
 uint8_t cursor_type; /*< Cursor type*/
 int8_t X; /*< X*/
 int8_t Y; /*< Y*/
}) mavlink_mav_set_cursor_t;

#define MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN 3
#define MAVLINK_MSG_ID_MAV_SET_CURSOR_MIN_LEN 3
#define MAVLINK_MSG_ID_104_LEN 3
#define MAVLINK_MSG_ID_104_MIN_LEN 3

#define MAVLINK_MSG_ID_MAV_SET_CURSOR_CRC 81
#define MAVLINK_MSG_ID_104_CRC 81



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_SET_CURSOR { \
    104, \
    "MAV_SET_CURSOR", \
    3, \
    {  { "cursor_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_set_cursor_t, cursor_type) }, \
         { "X", NULL, MAVLINK_TYPE_INT8_T, 0, 1, offsetof(mavlink_mav_set_cursor_t, X) }, \
         { "Y", NULL, MAVLINK_TYPE_INT8_T, 0, 2, offsetof(mavlink_mav_set_cursor_t, Y) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_SET_CURSOR { \
    "MAV_SET_CURSOR", \
    3, \
    {  { "cursor_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_set_cursor_t, cursor_type) }, \
         { "X", NULL, MAVLINK_TYPE_INT8_T, 0, 1, offsetof(mavlink_mav_set_cursor_t, X) }, \
         { "Y", NULL, MAVLINK_TYPE_INT8_T, 0, 2, offsetof(mavlink_mav_set_cursor_t, Y) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_set_cursor message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param cursor_type Cursor type
 * @param X X
 * @param Y Y
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_set_cursor_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t cursor_type, int8_t X, int8_t Y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN];
    _mav_put_uint8_t(buf, 0, cursor_type);
    _mav_put_int8_t(buf, 1, X);
    _mav_put_int8_t(buf, 2, Y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN);
#else
    mavlink_mav_set_cursor_t packet;
    packet.cursor_type = cursor_type;
    packet.X = X;
    packet.Y = Y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SET_CURSOR;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_SET_CURSOR_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_CRC);
}

/**
 * @brief Pack a mav_set_cursor message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cursor_type Cursor type
 * @param X X
 * @param Y Y
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_set_cursor_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t cursor_type,int8_t X,int8_t Y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN];
    _mav_put_uint8_t(buf, 0, cursor_type);
    _mav_put_int8_t(buf, 1, X);
    _mav_put_int8_t(buf, 2, Y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN);
#else
    mavlink_mav_set_cursor_t packet;
    packet.cursor_type = cursor_type;
    packet.X = X;
    packet.Y = Y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SET_CURSOR;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_SET_CURSOR_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_CRC);
}

/**
 * @brief Encode a mav_set_cursor struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_set_cursor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_set_cursor_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_set_cursor_t* mav_set_cursor)
{
    return mavlink_msg_mav_set_cursor_pack(system_id, component_id, msg, mav_set_cursor->cursor_type, mav_set_cursor->X, mav_set_cursor->Y);
}

/**
 * @brief Encode a mav_set_cursor struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_set_cursor C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_set_cursor_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_set_cursor_t* mav_set_cursor)
{
    return mavlink_msg_mav_set_cursor_pack_chan(system_id, component_id, chan, msg, mav_set_cursor->cursor_type, mav_set_cursor->X, mav_set_cursor->Y);
}

/**
 * @brief Send a mav_set_cursor message
 * @param chan MAVLink channel to send the message
 *
 * @param cursor_type Cursor type
 * @param X X
 * @param Y Y
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_set_cursor_send(mavlink_channel_t chan, uint8_t cursor_type, int8_t X, int8_t Y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN];
    _mav_put_uint8_t(buf, 0, cursor_type);
    _mav_put_int8_t(buf, 1, X);
    _mav_put_int8_t(buf, 2, Y);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_CURSOR, buf, MAVLINK_MSG_ID_MAV_SET_CURSOR_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_CRC);
#else
    mavlink_mav_set_cursor_t packet;
    packet.cursor_type = cursor_type;
    packet.X = X;
    packet.Y = Y;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_CURSOR, (const char *)&packet, MAVLINK_MSG_ID_MAV_SET_CURSOR_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_CRC);
#endif
}

/**
 * @brief Send a mav_set_cursor message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_set_cursor_send_struct(mavlink_channel_t chan, const mavlink_mav_set_cursor_t* mav_set_cursor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_set_cursor_send(chan, mav_set_cursor->cursor_type, mav_set_cursor->X, mav_set_cursor->Y);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_CURSOR, (const char *)mav_set_cursor, MAVLINK_MSG_ID_MAV_SET_CURSOR_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_set_cursor_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t cursor_type, int8_t X, int8_t Y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, cursor_type);
    _mav_put_int8_t(buf, 1, X);
    _mav_put_int8_t(buf, 2, Y);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_CURSOR, buf, MAVLINK_MSG_ID_MAV_SET_CURSOR_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_CRC);
#else
    mavlink_mav_set_cursor_t *packet = (mavlink_mav_set_cursor_t *)msgbuf;
    packet->cursor_type = cursor_type;
    packet->X = X;
    packet->Y = Y;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_CURSOR, (const char *)packet, MAVLINK_MSG_ID_MAV_SET_CURSOR_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN, MAVLINK_MSG_ID_MAV_SET_CURSOR_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_SET_CURSOR UNPACKING


/**
 * @brief Get field cursor_type from mav_set_cursor message
 *
 * @return Cursor type
 */
static inline uint8_t mavlink_msg_mav_set_cursor_get_cursor_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field X from mav_set_cursor message
 *
 * @return X
 */
static inline int8_t mavlink_msg_mav_set_cursor_get_X(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  1);
}

/**
 * @brief Get field Y from mav_set_cursor message
 *
 * @return Y
 */
static inline int8_t mavlink_msg_mav_set_cursor_get_Y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  2);
}

/**
 * @brief Decode a mav_set_cursor message into a struct
 *
 * @param msg The message to decode
 * @param mav_set_cursor C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_set_cursor_decode(const mavlink_message_t* msg, mavlink_mav_set_cursor_t* mav_set_cursor)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_set_cursor->cursor_type = mavlink_msg_mav_set_cursor_get_cursor_type(msg);
    mav_set_cursor->X = mavlink_msg_mav_set_cursor_get_X(msg);
    mav_set_cursor->Y = mavlink_msg_mav_set_cursor_get_Y(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN? msg->len : MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN;
        memset(mav_set_cursor, 0, MAVLINK_MSG_ID_MAV_SET_CURSOR_LEN);
    memcpy(mav_set_cursor, _MAV_PAYLOAD(msg), len);
#endif
}
