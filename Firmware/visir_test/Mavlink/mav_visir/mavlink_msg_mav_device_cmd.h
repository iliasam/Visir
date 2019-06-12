#pragma once
// MESSAGE MAV_DEVICE_CMD PACKING

#define MAVLINK_MSG_ID_MAV_DEVICE_CMD 12

MAVPACKED(
typedef struct __mavlink_mav_device_cmd_t {
 uint32_t parameter; /*< Command parameter*/
 uint8_t tar_system_id; /*< Target system ID*/
 uint8_t tar_component_id; /*< Target component ID*/
 uint8_t cmd; /*< Needed command*/
}) mavlink_mav_device_cmd_t;

#define MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN 7
#define MAVLINK_MSG_ID_MAV_DEVICE_CMD_MIN_LEN 7
#define MAVLINK_MSG_ID_12_LEN 7
#define MAVLINK_MSG_ID_12_MIN_LEN 7

#define MAVLINK_MSG_ID_MAV_DEVICE_CMD_CRC 142
#define MAVLINK_MSG_ID_12_CRC 142



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_DEVICE_CMD { \
    12, \
    "MAV_DEVICE_CMD", \
    4, \
    {  { "tar_system_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_mav_device_cmd_t, tar_system_id) }, \
         { "tar_component_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_mav_device_cmd_t, tar_component_id) }, \
         { "cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_mav_device_cmd_t, cmd) }, \
         { "parameter", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_mav_device_cmd_t, parameter) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_DEVICE_CMD { \
    "MAV_DEVICE_CMD", \
    4, \
    {  { "tar_system_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_mav_device_cmd_t, tar_system_id) }, \
         { "tar_component_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_mav_device_cmd_t, tar_component_id) }, \
         { "cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_mav_device_cmd_t, cmd) }, \
         { "parameter", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_mav_device_cmd_t, parameter) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_device_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param tar_system_id Target system ID
 * @param tar_component_id Target component ID
 * @param cmd Needed command
 * @param parameter Command parameter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_device_cmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t tar_system_id, uint8_t tar_component_id, uint8_t cmd, uint32_t parameter)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN];
    _mav_put_uint32_t(buf, 0, parameter);
    _mav_put_uint8_t(buf, 4, tar_system_id);
    _mav_put_uint8_t(buf, 5, tar_component_id);
    _mav_put_uint8_t(buf, 6, cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN);
#else
    mavlink_mav_device_cmd_t packet;
    packet.parameter = parameter;
    packet.tar_system_id = tar_system_id;
    packet.tar_component_id = tar_component_id;
    packet.cmd = cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_DEVICE_CMD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_DEVICE_CMD_MIN_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_CRC);
}

/**
 * @brief Pack a mav_device_cmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tar_system_id Target system ID
 * @param tar_component_id Target component ID
 * @param cmd Needed command
 * @param parameter Command parameter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_device_cmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t tar_system_id,uint8_t tar_component_id,uint8_t cmd,uint32_t parameter)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN];
    _mav_put_uint32_t(buf, 0, parameter);
    _mav_put_uint8_t(buf, 4, tar_system_id);
    _mav_put_uint8_t(buf, 5, tar_component_id);
    _mav_put_uint8_t(buf, 6, cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN);
#else
    mavlink_mav_device_cmd_t packet;
    packet.parameter = parameter;
    packet.tar_system_id = tar_system_id;
    packet.tar_component_id = tar_component_id;
    packet.cmd = cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_DEVICE_CMD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_DEVICE_CMD_MIN_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_CRC);
}

/**
 * @brief Encode a mav_device_cmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_device_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_device_cmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_device_cmd_t* mav_device_cmd)
{
    return mavlink_msg_mav_device_cmd_pack(system_id, component_id, msg, mav_device_cmd->tar_system_id, mav_device_cmd->tar_component_id, mav_device_cmd->cmd, mav_device_cmd->parameter);
}

/**
 * @brief Encode a mav_device_cmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_device_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_device_cmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_device_cmd_t* mav_device_cmd)
{
    return mavlink_msg_mav_device_cmd_pack_chan(system_id, component_id, chan, msg, mav_device_cmd->tar_system_id, mav_device_cmd->tar_component_id, mav_device_cmd->cmd, mav_device_cmd->parameter);
}

/**
 * @brief Send a mav_device_cmd message
 * @param chan MAVLink channel to send the message
 *
 * @param tar_system_id Target system ID
 * @param tar_component_id Target component ID
 * @param cmd Needed command
 * @param parameter Command parameter
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_device_cmd_send(mavlink_channel_t chan, uint8_t tar_system_id, uint8_t tar_component_id, uint8_t cmd, uint32_t parameter)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN];
    _mav_put_uint32_t(buf, 0, parameter);
    _mav_put_uint8_t(buf, 4, tar_system_id);
    _mav_put_uint8_t(buf, 5, tar_component_id);
    _mav_put_uint8_t(buf, 6, cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DEVICE_CMD, buf, MAVLINK_MSG_ID_MAV_DEVICE_CMD_MIN_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_CRC);
#else
    mavlink_mav_device_cmd_t packet;
    packet.parameter = parameter;
    packet.tar_system_id = tar_system_id;
    packet.tar_component_id = tar_component_id;
    packet.cmd = cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DEVICE_CMD, (const char *)&packet, MAVLINK_MSG_ID_MAV_DEVICE_CMD_MIN_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_CRC);
#endif
}

/**
 * @brief Send a mav_device_cmd message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_device_cmd_send_struct(mavlink_channel_t chan, const mavlink_mav_device_cmd_t* mav_device_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_device_cmd_send(chan, mav_device_cmd->tar_system_id, mav_device_cmd->tar_component_id, mav_device_cmd->cmd, mav_device_cmd->parameter);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DEVICE_CMD, (const char *)mav_device_cmd, MAVLINK_MSG_ID_MAV_DEVICE_CMD_MIN_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_device_cmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t tar_system_id, uint8_t tar_component_id, uint8_t cmd, uint32_t parameter)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, parameter);
    _mav_put_uint8_t(buf, 4, tar_system_id);
    _mav_put_uint8_t(buf, 5, tar_component_id);
    _mav_put_uint8_t(buf, 6, cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DEVICE_CMD, buf, MAVLINK_MSG_ID_MAV_DEVICE_CMD_MIN_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_CRC);
#else
    mavlink_mav_device_cmd_t *packet = (mavlink_mav_device_cmd_t *)msgbuf;
    packet->parameter = parameter;
    packet->tar_system_id = tar_system_id;
    packet->tar_component_id = tar_component_id;
    packet->cmd = cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DEVICE_CMD, (const char *)packet, MAVLINK_MSG_ID_MAV_DEVICE_CMD_MIN_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN, MAVLINK_MSG_ID_MAV_DEVICE_CMD_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_DEVICE_CMD UNPACKING


/**
 * @brief Get field tar_system_id from mav_device_cmd message
 *
 * @return Target system ID
 */
static inline uint8_t mavlink_msg_mav_device_cmd_get_tar_system_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field tar_component_id from mav_device_cmd message
 *
 * @return Target component ID
 */
static inline uint8_t mavlink_msg_mav_device_cmd_get_tar_component_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field cmd from mav_device_cmd message
 *
 * @return Needed command
 */
static inline uint8_t mavlink_msg_mav_device_cmd_get_cmd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field parameter from mav_device_cmd message
 *
 * @return Command parameter
 */
static inline uint32_t mavlink_msg_mav_device_cmd_get_parameter(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a mav_device_cmd message into a struct
 *
 * @param msg The message to decode
 * @param mav_device_cmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_device_cmd_decode(const mavlink_message_t* msg, mavlink_mav_device_cmd_t* mav_device_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_device_cmd->parameter = mavlink_msg_mav_device_cmd_get_parameter(msg);
    mav_device_cmd->tar_system_id = mavlink_msg_mav_device_cmd_get_tar_system_id(msg);
    mav_device_cmd->tar_component_id = mavlink_msg_mav_device_cmd_get_tar_component_id(msg);
    mav_device_cmd->cmd = mavlink_msg_mav_device_cmd_get_cmd(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN? msg->len : MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN;
        memset(mav_device_cmd, 0, MAVLINK_MSG_ID_MAV_DEVICE_CMD_LEN);
    memcpy(mav_device_cmd, _MAV_PAYLOAD(msg), len);
#endif
}
