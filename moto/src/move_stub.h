#include <stdint.h>
#include "moto_msg_manipulation.h"
#include "../../proto_mega/src/proto_lib.h"

int move_run();
msg scanHexMsgSTDIN(void);
#ifdef ARDUINO_DBG
    uint8_t serReadUnsignedChar(void);
#endif

