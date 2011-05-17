
#ifndef PROTO_SERIALIZER_H
#define PROTO_SERIALIZER_H

#include "proto_msg_structs.h"

uint8_t proto_serializeMovConfirmMsg(uint8_t data, uint8_t *serializedData);
uint8_t proto_serializeNavMsg(struct navData *, uint8_t *);
uint8_t proto_serializeUICommandMsg(uint8_t command, 
                                    uint8_t *serializedData);

#endif /* PROTO_SERIALIZER_H */
