#pragma once
// MESSAGE INHA PACKING

#define MAVLINK_MSG_ID_INHA 53


typedef struct __mavlink_inha_t {
 uint64_t time_usec; /*<  Time (sec).*/
 float mode; /*<  AUTO or MANUAL.*/
 int16_t alt; /*<  altitude(m).*/
 uint8_t lat; /*<  latitude (deg).*/
 char lon[16]; /*<  longitude (deg).*/
 uint8_t seq; /*<  sequence of mission.*/
} mavlink_inha_t;

#define MAVLINK_MSG_ID_INHA_LEN 32
#define MAVLINK_MSG_ID_INHA_MIN_LEN 32
#define MAVLINK_MSG_ID_53_LEN 32
#define MAVLINK_MSG_ID_53_MIN_LEN 32

#define MAVLINK_MSG_ID_INHA_CRC 46
#define MAVLINK_MSG_ID_53_CRC 46

#define MAVLINK_MSG_INHA_FIELD_LON_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_INHA { \
    53, \
    "INHA", \
    6, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_inha_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_inha_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_CHAR, 16, 15, offsetof(mavlink_inha_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_INT16_T, 0, 12, offsetof(mavlink_inha_t, alt) }, \
         { "seq", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_inha_t, seq) }, \
         { "mode", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_inha_t, mode) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_INHA { \
    "INHA", \
    6, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_inha_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_inha_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_CHAR, 16, 15, offsetof(mavlink_inha_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_INT16_T, 0, 12, offsetof(mavlink_inha_t, alt) }, \
         { "seq", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_inha_t, seq) }, \
         { "mode", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_inha_t, mode) }, \
         } \
}
#endif

/**
 * @brief Pack a inha message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec  Time (sec).
 * @param lat  latitude (deg).
 * @param lon  longitude (deg).
 * @param alt  altitude(m).
 * @param seq  sequence of mission.
 * @param mode  AUTO or MANUAL.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inha_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint8_t lat, const char *lon, int16_t alt, uint8_t seq, float mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INHA_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, mode);
    _mav_put_int16_t(buf, 12, alt);
    _mav_put_uint8_t(buf, 14, lat);
    _mav_put_uint8_t(buf, 31, seq);
    _mav_put_char_array(buf, 15, lon, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_INHA_LEN);
#else
    mavlink_inha_t packet;
    packet.time_usec = time_usec;
    packet.mode = mode;
    packet.alt = alt;
    packet.lat = lat;
    packet.seq = seq;
    mav_array_memcpy(packet.lon, lon, sizeof(char)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_INHA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_INHA;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_INHA_MIN_LEN, MAVLINK_MSG_ID_INHA_LEN, MAVLINK_MSG_ID_INHA_CRC);
}

/**
 * @brief Pack a inha message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec  Time (sec).
 * @param lat  latitude (deg).
 * @param lon  longitude (deg).
 * @param alt  altitude(m).
 * @param seq  sequence of mission.
 * @param mode  AUTO or MANUAL.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inha_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint8_t lat,const char *lon,int16_t alt,uint8_t seq,float mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INHA_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, mode);
    _mav_put_int16_t(buf, 12, alt);
    _mav_put_uint8_t(buf, 14, lat);
    _mav_put_uint8_t(buf, 31, seq);
    _mav_put_char_array(buf, 15, lon, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_INHA_LEN);
#else
    mavlink_inha_t packet;
    packet.time_usec = time_usec;
    packet.mode = mode;
    packet.alt = alt;
    packet.lat = lat;
    packet.seq = seq;
    mav_array_memcpy(packet.lon, lon, sizeof(char)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_INHA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_INHA;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_INHA_MIN_LEN, MAVLINK_MSG_ID_INHA_LEN, MAVLINK_MSG_ID_INHA_CRC);
}

/**
 * @brief Encode a inha struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param inha C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inha_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_inha_t* inha)
{
    return mavlink_msg_inha_pack(system_id, component_id, msg, inha->time_usec, inha->lat, inha->lon, inha->alt, inha->seq, inha->mode);
}

/**
 * @brief Encode a inha struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param inha C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inha_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_inha_t* inha)
{
    return mavlink_msg_inha_pack_chan(system_id, component_id, chan, msg, inha->time_usec, inha->lat, inha->lon, inha->alt, inha->seq, inha->mode);
}

/**
 * @brief Send a inha message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec  Time (sec).
 * @param lat  latitude (deg).
 * @param lon  longitude (deg).
 * @param alt  altitude(m).
 * @param seq  sequence of mission.
 * @param mode  AUTO or MANUAL.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_inha_send(mavlink_channel_t chan, uint64_t time_usec, uint8_t lat, const char *lon, int16_t alt, uint8_t seq, float mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_INHA_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, mode);
    _mav_put_int16_t(buf, 12, alt);
    _mav_put_uint8_t(buf, 14, lat);
    _mav_put_uint8_t(buf, 31, seq);
    _mav_put_char_array(buf, 15, lon, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INHA, buf, MAVLINK_MSG_ID_INHA_MIN_LEN, MAVLINK_MSG_ID_INHA_LEN, MAVLINK_MSG_ID_INHA_CRC);
#else
    mavlink_inha_t packet;
    packet.time_usec = time_usec;
    packet.mode = mode;
    packet.alt = alt;
    packet.lat = lat;
    packet.seq = seq;
    mav_array_memcpy(packet.lon, lon, sizeof(char)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INHA, (const char *)&packet, MAVLINK_MSG_ID_INHA_MIN_LEN, MAVLINK_MSG_ID_INHA_LEN, MAVLINK_MSG_ID_INHA_CRC);
#endif
}

/**
 * @brief Send a inha message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_inha_send_struct(mavlink_channel_t chan, const mavlink_inha_t* inha)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_inha_send(chan, inha->time_usec, inha->lat, inha->lon, inha->alt, inha->seq, inha->mode);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INHA, (const char *)inha, MAVLINK_MSG_ID_INHA_MIN_LEN, MAVLINK_MSG_ID_INHA_LEN, MAVLINK_MSG_ID_INHA_CRC);
#endif
}

#if MAVLINK_MSG_ID_INHA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_inha_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint8_t lat, const char *lon, int16_t alt, uint8_t seq, float mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, mode);
    _mav_put_int16_t(buf, 12, alt);
    _mav_put_uint8_t(buf, 14, lat);
    _mav_put_uint8_t(buf, 31, seq);
    _mav_put_char_array(buf, 15, lon, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INHA, buf, MAVLINK_MSG_ID_INHA_MIN_LEN, MAVLINK_MSG_ID_INHA_LEN, MAVLINK_MSG_ID_INHA_CRC);
#else
    mavlink_inha_t *packet = (mavlink_inha_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->mode = mode;
    packet->alt = alt;
    packet->lat = lat;
    packet->seq = seq;
    mav_array_memcpy(packet->lon, lon, sizeof(char)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_INHA, (const char *)packet, MAVLINK_MSG_ID_INHA_MIN_LEN, MAVLINK_MSG_ID_INHA_LEN, MAVLINK_MSG_ID_INHA_CRC);
#endif
}
#endif

#endif

// MESSAGE INHA UNPACKING


/**
 * @brief Get field time_usec from inha message
 *
 * @return  Time (sec).
 */
static inline uint64_t mavlink_msg_inha_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field lat from inha message
 *
 * @return  latitude (deg).
 */
static inline uint8_t mavlink_msg_inha_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field lon from inha message
 *
 * @return  longitude (deg).
 */
static inline uint16_t mavlink_msg_inha_get_lon(const mavlink_message_t* msg, char *lon)
{
    return _MAV_RETURN_char_array(msg, lon, 16,  15);
}

/**
 * @brief Get field alt from inha message
 *
 * @return  altitude(m).
 */
static inline int16_t mavlink_msg_inha_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  12);
}

/**
 * @brief Get field seq from inha message
 *
 * @return  sequence of mission.
 */
static inline uint8_t mavlink_msg_inha_get_seq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  31);
}

/**
 * @brief Get field mode from inha message
 *
 * @return  AUTO or MANUAL.
 */
static inline float mavlink_msg_inha_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a inha message into a struct
 *
 * @param msg The message to decode
 * @param inha C-struct to decode the message contents into
 */
static inline void mavlink_msg_inha_decode(const mavlink_message_t* msg, mavlink_inha_t* inha)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    inha->time_usec = mavlink_msg_inha_get_time_usec(msg);
    inha->mode = mavlink_msg_inha_get_mode(msg);
    inha->alt = mavlink_msg_inha_get_alt(msg);
    inha->lat = mavlink_msg_inha_get_lat(msg);
    mavlink_msg_inha_get_lon(msg, inha->lon);
    inha->seq = mavlink_msg_inha_get_seq(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_INHA_LEN? msg->len : MAVLINK_MSG_ID_INHA_LEN;
        memset(inha, 0, MAVLINK_MSG_ID_INHA_LEN);
    memcpy(inha, _MAV_PAYLOAD(msg), len);
#endif
}
