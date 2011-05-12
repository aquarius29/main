
#ifndef PROTO_DESERIALIZER_H
#define PROTO_DESERIALIZER_H

#include <stdint.h>
#include "proto_msg_structs.h"

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

uint8_t proto_reConstructMsgNav(uint8_t *data, struct navData *);

#endif /* PROTO_DESERIALIZER_H */