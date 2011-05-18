
#include "serial_interface.h"
#include "proto_stub.h"

int16_t serial_init(void){
    proto_setupPort();
}

int16_t serial_run(void){
    proto_processMessages();
}
