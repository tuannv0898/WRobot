#pragma once
// MESSAGE CMD_SET_GYRO_OFFSET PACKING

#define MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET 7

MAVPACKED(
typedef struct __mavlink_cmd_set_gyro_offset_t {
 int16_t gyro_offet_x; /*<  Gyro Offset X*/
 int16_t gyro_offet_y; /*<  Gyro Offset Y*/
 int16_t gyro_offet_z; /*<  Gyro Offset Z*/
}) mavlink_cmd_set_gyro_offset_t;

#define MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN 6
#define MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_MIN_LEN 6
#define MAVLINK_MSG_ID_7_LEN 6
#define MAVLINK_MSG_ID_7_MIN_LEN 6

#define MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_CRC 146
#define MAVLINK_MSG_ID_7_CRC 146



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CMD_SET_GYRO_OFFSET { \
    7, \
    "CMD_SET_GYRO_OFFSET", \
    3, \
    {  { "gyro_offet_x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_cmd_set_gyro_offset_t, gyro_offet_x) }, \
         { "gyro_offet_y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_cmd_set_gyro_offset_t, gyro_offet_y) }, \
         { "gyro_offet_z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_cmd_set_gyro_offset_t, gyro_offet_z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CMD_SET_GYRO_OFFSET { \
    "CMD_SET_GYRO_OFFSET", \
    3, \
    {  { "gyro_offet_x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_cmd_set_gyro_offset_t, gyro_offet_x) }, \
         { "gyro_offet_y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_cmd_set_gyro_offset_t, gyro_offet_y) }, \
         { "gyro_offet_z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_cmd_set_gyro_offset_t, gyro_offet_z) }, \
         } \
}
#endif

/**
 * @brief Pack a cmd_set_gyro_offset message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param gyro_offet_x  Gyro Offset X
 * @param gyro_offet_y  Gyro Offset Y
 * @param gyro_offet_z  Gyro Offset Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cmd_set_gyro_offset_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int16_t gyro_offet_x, int16_t gyro_offet_y, int16_t gyro_offet_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN];
    _mav_put_int16_t(buf, 0, gyro_offet_x);
    _mav_put_int16_t(buf, 2, gyro_offet_y);
    _mav_put_int16_t(buf, 4, gyro_offet_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN);
#else
    mavlink_cmd_set_gyro_offset_t packet;
    packet.gyro_offet_x = gyro_offet_x;
    packet.gyro_offet_y = gyro_offet_y;
    packet.gyro_offet_z = gyro_offet_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_CRC);
}

/**
 * @brief Pack a cmd_set_gyro_offset message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gyro_offet_x  Gyro Offset X
 * @param gyro_offet_y  Gyro Offset Y
 * @param gyro_offet_z  Gyro Offset Z
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cmd_set_gyro_offset_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int16_t gyro_offet_x,int16_t gyro_offet_y,int16_t gyro_offet_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN];
    _mav_put_int16_t(buf, 0, gyro_offet_x);
    _mav_put_int16_t(buf, 2, gyro_offet_y);
    _mav_put_int16_t(buf, 4, gyro_offet_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN);
#else
    mavlink_cmd_set_gyro_offset_t packet;
    packet.gyro_offet_x = gyro_offet_x;
    packet.gyro_offet_y = gyro_offet_y;
    packet.gyro_offet_z = gyro_offet_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_CRC);
}

/**
 * @brief Encode a cmd_set_gyro_offset struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param cmd_set_gyro_offset C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cmd_set_gyro_offset_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_cmd_set_gyro_offset_t* cmd_set_gyro_offset)
{
    return mavlink_msg_cmd_set_gyro_offset_pack(system_id, component_id, msg, cmd_set_gyro_offset->gyro_offet_x, cmd_set_gyro_offset->gyro_offet_y, cmd_set_gyro_offset->gyro_offet_z);
}

/**
 * @brief Encode a cmd_set_gyro_offset struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd_set_gyro_offset C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cmd_set_gyro_offset_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_cmd_set_gyro_offset_t* cmd_set_gyro_offset)
{
    return mavlink_msg_cmd_set_gyro_offset_pack_chan(system_id, component_id, chan, msg, cmd_set_gyro_offset->gyro_offet_x, cmd_set_gyro_offset->gyro_offet_y, cmd_set_gyro_offset->gyro_offet_z);
}

/**
 * @brief Send a cmd_set_gyro_offset message
 * @param chan MAVLink channel to send the message
 *
 * @param gyro_offet_x  Gyro Offset X
 * @param gyro_offet_y  Gyro Offset Y
 * @param gyro_offet_z  Gyro Offset Z
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_cmd_set_gyro_offset_send(mavlink_channel_t chan, int16_t gyro_offet_x, int16_t gyro_offet_y, int16_t gyro_offet_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN];
    _mav_put_int16_t(buf, 0, gyro_offet_x);
    _mav_put_int16_t(buf, 2, gyro_offet_y);
    _mav_put_int16_t(buf, 4, gyro_offet_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET, buf, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_CRC);
#else
    mavlink_cmd_set_gyro_offset_t packet;
    packet.gyro_offet_x = gyro_offet_x;
    packet.gyro_offet_y = gyro_offet_y;
    packet.gyro_offet_z = gyro_offet_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET, (const char *)&packet, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_CRC);
#endif
}

/**
 * @brief Send a cmd_set_gyro_offset message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_cmd_set_gyro_offset_send_struct(mavlink_channel_t chan, const mavlink_cmd_set_gyro_offset_t* cmd_set_gyro_offset)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_cmd_set_gyro_offset_send(chan, cmd_set_gyro_offset->gyro_offet_x, cmd_set_gyro_offset->gyro_offet_y, cmd_set_gyro_offset->gyro_offet_z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET, (const char *)cmd_set_gyro_offset, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_CRC);
#endif
}

#if MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_cmd_set_gyro_offset_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int16_t gyro_offet_x, int16_t gyro_offet_y, int16_t gyro_offet_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int16_t(buf, 0, gyro_offet_x);
    _mav_put_int16_t(buf, 2, gyro_offet_y);
    _mav_put_int16_t(buf, 4, gyro_offet_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET, buf, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_CRC);
#else
    mavlink_cmd_set_gyro_offset_t *packet = (mavlink_cmd_set_gyro_offset_t *)msgbuf;
    packet->gyro_offet_x = gyro_offet_x;
    packet->gyro_offet_y = gyro_offet_y;
    packet->gyro_offet_z = gyro_offet_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET, (const char *)packet, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_MIN_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_CRC);
#endif
}
#endif

#endif

// MESSAGE CMD_SET_GYRO_OFFSET UNPACKING


/**
 * @brief Get field gyro_offet_x from cmd_set_gyro_offset message
 *
 * @return  Gyro Offset X
 */
static inline int16_t mavlink_msg_cmd_set_gyro_offset_get_gyro_offet_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field gyro_offet_y from cmd_set_gyro_offset message
 *
 * @return  Gyro Offset Y
 */
static inline int16_t mavlink_msg_cmd_set_gyro_offset_get_gyro_offet_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field gyro_offet_z from cmd_set_gyro_offset message
 *
 * @return  Gyro Offset Z
 */
static inline int16_t mavlink_msg_cmd_set_gyro_offset_get_gyro_offet_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Decode a cmd_set_gyro_offset message into a struct
 *
 * @param msg The message to decode
 * @param cmd_set_gyro_offset C-struct to decode the message contents into
 */
static inline void mavlink_msg_cmd_set_gyro_offset_decode(const mavlink_message_t* msg, mavlink_cmd_set_gyro_offset_t* cmd_set_gyro_offset)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    cmd_set_gyro_offset->gyro_offet_x = mavlink_msg_cmd_set_gyro_offset_get_gyro_offet_x(msg);
    cmd_set_gyro_offset->gyro_offet_y = mavlink_msg_cmd_set_gyro_offset_get_gyro_offet_y(msg);
    cmd_set_gyro_offset->gyro_offet_z = mavlink_msg_cmd_set_gyro_offset_get_gyro_offet_z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN? msg->len : MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN;
        memset(cmd_set_gyro_offset, 0, MAVLINK_MSG_ID_CMD_SET_GYRO_OFFSET_LEN);
    memcpy(cmd_set_gyro_offset, _MAV_PAYLOAD(msg), len);
#endif
}