
#ifndef PROTO_SERIALIZER_H
#define PROTO_SERIALIZER_H

#define DATA_BUFFER_LEN 40
#define STATUS_STRUCT_LEN 6
#define NAV_MSG_LEN 10


#include "proto_msg_structs.h"

/*struct status {
    uint8_t uInt8;
    int8_t int8;
    uint16_t uInt16;
    int16_t int16;
};  */  

uint8_t proto_serializeNavMsg(struct navData *, uint8_t *);

#endif /* PROTO_SERIALIZER_H */
