#ifndef MOVE_STUB_H
    #define MOVE_STUB_H
#include <stdint.h>
#include "moto_msg_manipulation.h"
#include "../../proto_mega/src/proto_lib.h"
extern unsigned int input;
int move_init();
int move_run();
msg scanHexMsgSTDIN(void);
uint8_t serReadUnsignedChar(void);
#endif
