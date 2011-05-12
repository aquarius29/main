
#include "proto_serial_port.h"
#include "proto_serial_comm.h"
#include "proto_serializer.h"
#include "proto_msg_structs.h"
#include "port_test.h"

#include <stdio.h>

static struct navData navMsg;

void navMsgFill1(void);
void navMsgFill2(void);
    
void port_test(void){
    int32_t portHandle;

    portHandle = proto_serialOpen();
    
    navMsgFill1();
    printf("sending data1\n");
    proto_serialSendNavMsg(portHandle, &navMsg);
        
    navMsgFill2();
    printf("sending data2\n");
    proto_serialSendNavMsg(portHandle, &navMsg);
        
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
  navMsg.type = 50;
  navMsg.order = 2;
  navMsg.height = 1027;
  navMsg.distance = 1027;
  navMsg.yaw = 1027;
}

