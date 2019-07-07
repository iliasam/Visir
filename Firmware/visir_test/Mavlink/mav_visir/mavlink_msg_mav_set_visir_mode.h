#pragma once
// MESSAGE MAV_SET_VISIR_MODE PACKING

#define MAVLINK_MSG_ID_MAV_SET_VISIR_MODE 107

MAVPACKED(
typedef struct __mavlink_mav_set_visir_mode_t {
 uint8_t mode_code; /*< New visir mode*/
}) mavlink_mav_set_visir_mode_t;

#define MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN 1
#define MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_MIN_LEN 1
#define MAVLINK_MSG_ID_107_LEN 1
#define MAVLINK_MSG_ID_107_MIN_LEN 1

#define MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_CRC 170
#define MAVLINK_MSG_ID_107_CRC 170



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_SET_VISIR_MODE { \
    107, \
    "MAV_SET_VISIR_MODE", \
    1, \
    {  { "mode_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_set_visir_mode_t, mode_code) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_SET_VISIR_MODE { \
    "MAV_SET_VISIR_MODE", \
    1, \
    {  { "mode_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_set_visir_mode_t, mode_code) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_set_visir_mode message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mode_code New visir mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_set_visir_mode_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t mode_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN];
    _mav_put_uint8_t(buf, 0, mode_code);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN);
#else
    mavlink_mav_set_visir_mode_t packet;
    packet.mode_code = mode_code;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SET_VISIR_MODE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_CRC);
}

/**
 * @brief Pack a mav_set_visir_mode message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mode_code New visir mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_set_visir_mode_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t mode_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN];
    _mav_put_uint8_t(buf, 0, mode_code);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN);
#else
    mavlink_mav_set_visir_mode_t packet;
    packet.mode_code = mode_code;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SET_VISIR_MODE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_CRC);
}

/**
 * @brief Encode a mav_set_visir_mode struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_set_visir_mode C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_set_visir_mode_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_set_visir_mode_t* mav_set_visir_mode)
{
    return mavlink_msg_mav_set_visir_mode_pack(system_id, component_id, msg, mav_set_visir_mode->mode_code);
}

/**
 * @brief Encode a mav_set_visir_mode struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_set_visir_mode C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_set_visir_mode_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_set_visir_mode_t* mav_set_visir_mode)
{
    return mavlink_msg_mav_set_visir_mode_pack_chan(system_id, component_id, chan, msg, mav_set_visir_mode->mode_code);
}

/**
 * @brief Send a mav_set_visir_mode message
 * @param chan MAVLink channel to send the message
 *
 * @param mode_code New visir mode
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_set_visir_mode_send(mavlink_channel_t chan, uint8_t mode_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN];
    _mav_put_uint8_t(buf, 0, mode_code);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE, buf, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_CRC);
#else
    mavlink_mav_set_visir_mode_t packet;
    packet.mode_code = mode_code;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE, (const char *)&packet, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_CRC);
#endif
}

/**
 * @brief Send a mav_set_visir_mode message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_set_visir_mode_send_struct(mavlink_channel_t chan, const mavlink_mav_set_visir_mode_t* mav_set_visir_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_set_visir_mode_send(chan, mav_set_visir_mode->mode_code);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE, (const char *)mav_set_visir_mode, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_set_visir_mode_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t mode_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, mode_code);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE, buf, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_CRC);
#else
    mavlink_mav_set_visir_mode_t *packet = (mavlink_mav_set_visir_mode_t *)msgbuf;
    packet->mode_code = mode_code;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE, (const char *)packet, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_MIN_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_SET_VISIR_MODE UNPACKING


/**
 * @brief Get field mode_code from mav_set_visir_mode message
 *
 * @return New visir mode
 */
static inline uint8_t mavlink_msg_mav_set_visir_mode_get_mode_code(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a mav_set_visir_mode message into a struct
 *
 * @param msg The message to decode
 * @param mav_set_visir_mode C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_set_visir_mode_decode(const mavlink_message_t* msg, mavlink_mav_set_visir_mode_t* mav_set_visir_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_set_visir_mode->mode_code = mavlink_msg_mav_set_visir_mode_get_mode_code(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN? msg->len : MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN;
        memset(mav_set_visir_mode, 0, MAVLINK_MSG_ID_MAV_SET_VISIR_MODE_LEN);
    memcpy(mav_set_visir_mode, _MAV_PAYLOAD(msg), len);
#endif
}
