
#ifndef PROTO_SERIALIZER_H
#define PROTO_SERIALIZER_H

#define DATA_BUFFER_LEN 40
#define NAV_MSG_LEN 10

#include "proto_msg_structs.h"

uint8_t proto_serializeNavMsg(struct navData *, uint8_t *);

#endif /* PROTO_SERIALIZER_H */
