<<<<<<< HEAD
#include <stdint.h>
#include "moto_msg_manipulation.h"
#include "../../proto_mega/src/proto_lib.h"

int move_run();
msg scanHexMsgSTDIN(void);
#ifdef ARDUINO_DBG
    uint8_t serReadUnsignedChar(void);
#endif

=======
#ifndef MOVE_STUB_H
#define MOVE_STUB_H
#include <stdint.h>
#include "moto_msg_manipulation.h"
#include "../../proto_mega/src/proto_lib.h"

int move_init();
int move_run();
msg scanHexMsgSTDIN(void);
uint8_t serReadUnsignedChar(void);
#endif
>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
