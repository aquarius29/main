
#include "proto_serial_port.h"
#include "proto_serial_comm.h"
#include "proto_serializer.h"
#include "proto_msg_structs.h"
#include "port_test.h"

#include <stdio.h>

static struct navData navMsg;
    
void port_test(void){
    int32_t portHandle;
    uint8_t data1[NAV_MSG_LEN];

    portHandle = proto_serialOpen();
    sleep(1);
    
    navMsgFill1();
    proto_serializeNavMsg(&navMsg, data1);
        
    printf("sending data1\n");
    proto_serialSend(portHandle, data1);
    // sleep(1);
    
    navMsgFill2();
    proto_serializeNavMsg(&navMsg, data1);
        
    printf("sending data2\n");
    proto_serialSend(portHandle, data1);
    
    
    
    sleep(2);

    proto_serialClose(portHandle);
}

void navMsgFill1(void){
  navMsg.type = 10;
  navMsg.order = 2;
  navMsg.height = 1027;
  navMsg.distance = 1027;
  navMsg.yaw = 1027;
}

void navMsgFill2(void){
  navMsg.type = 55;
  navMsg.order = 2;
  navMsg.height = 1027;
  navMsg.distance = 1027;
  navMsg.yaw = 1027;
}

