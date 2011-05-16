
#ifndef PROTO_MSG_STRUCTS_H
#define PROTO_MSG_STRUCTS_H

#include <stdint.h>

/* this is sent from navigation to movement */
struct navData {
    uint8_t type;
    uint8_t order;
    uint16_t height;
    uint16_t distance;
    uint16_t yaw;
};

#endif /* PROTO_MSG_STRUCTS_H */