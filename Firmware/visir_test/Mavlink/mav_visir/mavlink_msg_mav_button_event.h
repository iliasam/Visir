#pragma once
// MESSAGE MAV_BUTTON_EVENT PACKING

#define MAVLINK_MSG_ID_MAV_BUTTON_EVENT 106

MAVPACKED(
typedef struct __mavlink_mav_button_event_t {
 uint8_t button_code; /*< Code of the button*/
 uint8_t event_code; /*< Button event type*/
}) mavlink_mav_button_event_t;

#define MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN 2
#define MAVLINK_MSG_ID_MAV_BUTTON_EVENT_MIN_LEN 2
#define MAVLINK_MSG_ID_106_LEN 2
#define MAVLINK_MSG_ID_106_MIN_LEN 2

#define MAVLINK_MSG_ID_MAV_BUTTON_EVENT_CRC 78
#define MAVLINK_MSG_ID_106_CRC 78



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_BUTTON_EVENT { \
    106, \
    "MAV_BUTTON_EVENT", \
    2, \
    {  { "button_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_button_event_t, button_code) }, \
         { "event_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_mav_button_event_t, event_code) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_BUTTON_EVENT { \
    "MAV_BUTTON_EVENT", \
    2, \
    {  { "button_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_button_event_t, button_code) }, \
         { "event_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_mav_button_event_t, event_code) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_button_event message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param button_code Code of the button
 * @param event_code Button event type
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_button_event_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t button_code, uint8_t event_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN];
    _mav_put_uint8_t(buf, 0, button_code);
    _mav_put_uint8_t(buf, 1, event_code);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN);
#else
    mavlink_mav_button_event_t packet;
    packet.button_code = button_code;
    packet.event_code = event_code;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_BUTTON_EVENT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_MIN_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_CRC);
}

/**
 * @brief Pack a mav_button_event message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param button_code Code of the button
 * @param event_code Button event type
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_button_event_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t button_code,uint8_t event_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN];
    _mav_put_uint8_t(buf, 0, button_code);
    _mav_put_uint8_t(buf, 1, event_code);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN);
#else
    mavlink_mav_button_event_t packet;
    packet.button_code = button_code;
    packet.event_code = event_code;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_BUTTON_EVENT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_MIN_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_CRC);
}

/**
 * @brief Encode a mav_button_event struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_button_event C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_button_event_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_button_event_t* mav_button_event)
{
    return mavlink_msg_mav_button_event_pack(system_id, component_id, msg, mav_button_event->button_code, mav_button_event->event_code);
}

/**
 * @brief Encode a mav_button_event struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_button_event C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_button_event_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_button_event_t* mav_button_event)
{
    return mavlink_msg_mav_button_event_pack_chan(system_id, component_id, chan, msg, mav_button_event->button_code, mav_button_event->event_code);
}

/**
 * @brief Send a mav_button_event message
 * @param chan MAVLink channel to send the message
 *
 * @param button_code Code of the button
 * @param event_code Button event type
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_button_event_send(mavlink_channel_t chan, uint8_t button_code, uint8_t event_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN];
    _mav_put_uint8_t(buf, 0, button_code);
    _mav_put_uint8_t(buf, 1, event_code);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BUTTON_EVENT, buf, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_MIN_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_CRC);
#else
    mavlink_mav_button_event_t packet;
    packet.button_code = button_code;
    packet.event_code = event_code;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BUTTON_EVENT, (const char *)&packet, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_MIN_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_CRC);
#endif
}

/**
 * @brief Send a mav_button_event message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_button_event_send_struct(mavlink_channel_t chan, const mavlink_mav_button_event_t* mav_button_event)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_button_event_send(chan, mav_button_event->button_code, mav_button_event->event_code);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BUTTON_EVENT, (const char *)mav_button_event, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_MIN_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_button_event_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t button_code, uint8_t event_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, button_code);
    _mav_put_uint8_t(buf, 1, event_code);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BUTTON_EVENT, buf, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_MIN_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_CRC);
#else
    mavlink_mav_button_event_t *packet = (mavlink_mav_button_event_t *)msgbuf;
    packet->button_code = button_code;
    packet->event_code = event_code;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BUTTON_EVENT, (const char *)packet, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_MIN_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_BUTTON_EVENT UNPACKING


/**
 * @brief Get field button_code from mav_button_event message
 *
 * @return Code of the button
 */
static inline uint8_t mavlink_msg_mav_button_event_get_button_code(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field event_code from mav_button_event message
 *
 * @return Button event type
 */
static inline uint8_t mavlink_msg_mav_button_event_get_event_code(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a mav_button_event message into a struct
 *
 * @param msg The message to decode
 * @param mav_button_event C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_button_event_decode(const mavlink_message_t* msg, mavlink_mav_button_event_t* mav_button_event)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_button_event->button_code = mavlink_msg_mav_button_event_get_button_code(msg);
    mav_button_event->event_code = mavlink_msg_mav_button_event_get_event_code(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN? msg->len : MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN;
        memset(mav_button_event, 0, MAVLINK_MSG_ID_MAV_BUTTON_EVENT_LEN);
    memcpy(mav_button_event, _MAV_PAYLOAD(msg), len);
#endif
}
