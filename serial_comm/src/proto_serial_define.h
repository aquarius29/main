
/*!
 *  @file proto_serialDefine.h
 *
 *  @brief Combining defines for the serialize/deserialize
 *  @author     Justin
 *  @date       2011-05-12
 *
 *  @history    2011-05-12 - Created this header - Justin
 *
 *  @details
 */
#ifndef PROTO_SERIALDEFINE_H
#define PROTO_SERIALDEFINE_H

#define TRUE 1
#define FALSE 0

/* size of buffers used and maximum message length */
#define PROTO_MAX_MSG_LEN 100

/* Length defines for messages passed */
#define DATA_BUFFER_LEN 100
#define NAV_MSG_LEN 10
#define MOV_CONFIRM_MSG_LEN 3


/* array index that holds message length */
#define LEN_INDEX 0

/* array index that holds message ID */
#define ID_INDEX 1

/* navigation message array indexes */
#define NAV_TYPE_INDEX 2
#define NAV_ORDER_INDEX 3
#define NAV_HEIGHT_INDEX_LOWBYTE 4
#define NAV_HEIGHT_INDEX_HIGHBYTE 5
#define NAV_DISTANCE_INDEX_LOWBYTE 6
#define NAV_DISTANCE_INDEX_HIGHBYTE 7
#define NAV_YAW_INDEX_LOWBYTE 8
#define NAV_YAW_INDEX_HIGHBYTE 9
#define NAV_NULL_INDEX 10

/* message ID for messages from navigation */
#define MSG_ID_NAV 1

/* movement confirm array indexes*/
#define MOV_CONFIRM_VAL_INDEX 2
#define MOV_CONFIRM_NULL_INDEX 3

/* message ID for movements confirmation message */
#define MSG_ID_MOV_CONFIRM 2

#endif /* PROTO_SERIALDEFINE_H */
