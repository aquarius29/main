
#include "proto_serial_port.h"
#include "proto_serial_comm.h"
#include "proto_serializer.h"
#include "proto_msg_structs.h"
#include "port_test.h"

#include <stdio.h>

static struct navData navMsg;

void port_test(void){
    int32_t portHandle;
    //uint8_t data1[] = {10, 1, 10, 2, 3, 4, 3, 4, 3, 4, '\0'};
    uint8_t data2[] = {3, 1, 2, 3, '\0'};
    uint8_t data1[NAV_MSG_LEN];
    navMsgFill();

    proto_serializeNavMsg(&navMsg, data1);
    
    
    portHandle = proto_serialOpen();
    sleep(1);
    
    printf("sending data1\n");
    proto_serialSend(portHandle, data1);
    // sleep(1);
    
    printf("sending data2\n");
    proto_serialSend(portHandle, data2);
    sleep(2);

    proto_serialClose(portHandle);
}

void navMsgFill(void){
  navMsg.type = 10;
  navMsg.order = 2;
  navMsg.height = 1027;
  navMsg.distance = 1027;
  navMsg.yaw = 1027;
}
