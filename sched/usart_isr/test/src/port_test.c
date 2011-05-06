
#include "proto_serial_port.h"
#include "proto_serial_comm.h"
#include "port_test.h"

void port_test(void){
    int32_t portHandle;
    uint8_t data[] = {3, 1, 2, 3, '\0'};
    
    portHandle = proto_serialOpen();
    sleep(1);
    
    proto_serialSend(portHandle, data);
    
    sleep(2);
    proto_serialClose(portHandle);
}