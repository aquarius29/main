
#ifndef PROTO_SERIALIZER_H
#define PROTO_SERIALIZER_H

#define DATA_BUFFER_LEN 100
#define NAV_MSG_LEN 10
#define MOV_CONFIRM_MSG_LEN 3

#include "proto_msg_structs.h"

uint8_t proto_serializeMovConfirmMsg(uint8_t data, uint8_t *serializedData);
uint8_t proto_serializeNavMsg(struct navData *, uint8_t *);

#endif /* PROTO_SERIALIZER_H */
