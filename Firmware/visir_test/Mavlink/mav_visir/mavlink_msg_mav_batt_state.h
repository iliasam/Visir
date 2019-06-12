#pragma once
// MESSAGE MAV_BATT_STATE PACKING

#define MAVLINK_MSG_ID_MAV_BATT_STATE 103

MAVPACKED(
typedef struct __mavlink_mav_batt_state_t {
 float voltage; /*< Voltage, V*/
 uint8_t state; /*< State*/
}) mavlink_mav_batt_state_t;

#define MAVLINK_MSG_ID_MAV_BATT_STATE_LEN 5
#define MAVLINK_MSG_ID_MAV_BATT_STATE_MIN_LEN 5
#define MAVLINK_MSG_ID_103_LEN 5
#define MAVLINK_MSG_ID_103_MIN_LEN 5

#define MAVLINK_MSG_ID_MAV_BATT_STATE_CRC 81
#define MAVLINK_MSG_ID_103_CRC 81



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_BATT_STATE { \
    103, \
    "MAV_BATT_STATE", \
    2, \
    {  { "state", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_mav_batt_state_t, state) }, \
         { "voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_batt_state_t, voltage) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_BATT_STATE { \
    "MAV_BATT_STATE", \
    2, \
    {  { "state", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_mav_batt_state_t, state) }, \
         { "voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_batt_state_t, voltage) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_batt_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param state State
 * @param voltage Voltage, V
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_batt_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t state, float voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_BATT_STATE_LEN];
    _mav_put_float(buf, 0, voltage);
    _mav_put_uint8_t(buf, 4, state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN);
#else
    mavlink_mav_batt_state_t packet;
    packet.voltage = voltage;
    packet.state = state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_BATT_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_BATT_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_CRC);
}

/**
 * @brief Pack a mav_batt_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param state State
 * @param voltage Voltage, V
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_batt_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t state,float voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_BATT_STATE_LEN];
    _mav_put_float(buf, 0, voltage);
    _mav_put_uint8_t(buf, 4, state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN);
#else
    mavlink_mav_batt_state_t packet;
    packet.voltage = voltage;
    packet.state = state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_BATT_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_BATT_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_CRC);
}

/**
 * @brief Encode a mav_batt_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_batt_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_batt_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_batt_state_t* mav_batt_state)
{
    return mavlink_msg_mav_batt_state_pack(system_id, component_id, msg, mav_batt_state->state, mav_batt_state->voltage);
}

/**
 * @brief Encode a mav_batt_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_batt_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_batt_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_batt_state_t* mav_batt_state)
{
    return mavlink_msg_mav_batt_state_pack_chan(system_id, component_id, chan, msg, mav_batt_state->state, mav_batt_state->voltage);
}

/**
 * @brief Send a mav_batt_state message
 * @param chan MAVLink channel to send the message
 *
 * @param state State
 * @param voltage Voltage, V
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_batt_state_send(mavlink_channel_t chan, uint8_t state, float voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_BATT_STATE_LEN];
    _mav_put_float(buf, 0, voltage);
    _mav_put_uint8_t(buf, 4, state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BATT_STATE, buf, MAVLINK_MSG_ID_MAV_BATT_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_CRC);
#else
    mavlink_mav_batt_state_t packet;
    packet.voltage = voltage;
    packet.state = state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BATT_STATE, (const char *)&packet, MAVLINK_MSG_ID_MAV_BATT_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_CRC);
#endif
}

/**
 * @brief Send a mav_batt_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_batt_state_send_struct(mavlink_channel_t chan, const mavlink_mav_batt_state_t* mav_batt_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_batt_state_send(chan, mav_batt_state->state, mav_batt_state->voltage);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BATT_STATE, (const char *)mav_batt_state, MAVLINK_MSG_ID_MAV_BATT_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_BATT_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_batt_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t state, float voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, voltage);
    _mav_put_uint8_t(buf, 4, state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BATT_STATE, buf, MAVLINK_MSG_ID_MAV_BATT_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_CRC);
#else
    mavlink_mav_batt_state_t *packet = (mavlink_mav_batt_state_t *)msgbuf;
    packet->voltage = voltage;
    packet->state = state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_BATT_STATE, (const char *)packet, MAVLINK_MSG_ID_MAV_BATT_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN, MAVLINK_MSG_ID_MAV_BATT_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_BATT_STATE UNPACKING


/**
 * @brief Get field state from mav_batt_state message
 *
 * @return State
 */
static inline uint8_t mavlink_msg_mav_batt_state_get_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field voltage from mav_batt_state message
 *
 * @return Voltage, V
 */
static inline float mavlink_msg_mav_batt_state_get_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a mav_batt_state message into a struct
 *
 * @param msg The message to decode
 * @param mav_batt_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_batt_state_decode(const mavlink_message_t* msg, mavlink_mav_batt_state_t* mav_batt_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_batt_state->voltage = mavlink_msg_mav_batt_state_get_voltage(msg);
    mav_batt_state->state = mavlink_msg_mav_batt_state_get_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_BATT_STATE_LEN? msg->len : MAVLINK_MSG_ID_MAV_BATT_STATE_LEN;
        memset(mav_batt_state, 0, MAVLINK_MSG_ID_MAV_BATT_STATE_LEN);
    memcpy(mav_batt_state, _MAV_PAYLOAD(msg), len);
#endif
}
