
#include "serial_interface.h"
#include "proto_stub.h"

uint16_t serial_init(void){
    proto_setupPort();
}

uint16_t serial_run(void){
    proto_processMessages();
}
