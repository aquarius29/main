
#ifndef PROTO_DESERIALIZER_H
#define PROTO_DESERIALIZER_H

#include <stdint.h>
#include "proto_msg_structs.h"


uint8_t proto_reConstructMsgNav(uint8_t *data, struct navData *);

#endif /* PROTO_DESERIALIZER_H */
