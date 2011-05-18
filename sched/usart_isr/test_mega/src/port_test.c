
/*
 *  Module represents a group on the panda (sort of). It uses the serial
 *  API to open a serial port and send and receive data on it.
 */
 
#include "proto_serial_port.h"
#include "proto_serial_comm.h"
#include "proto_serializer.h"
#include "proto_msg_structs.h"
#include "port_test.h"
#include "proto_serial_define.h"

#include <stdio.h>

static struct navData navMsg;

void navMsgFill1(uint8_t n);
void navMsgFill2(void);

#define ITERATIONS 2
    
void port_test(void){
    uint8_t x = 0;

    int32_t portHandle;
    uint8_t serialData[PROTO_MAX_MSG_LEN];
    uint8_t *p_serialData = NULL;
    uint8_t movConfirmMsg;
    
    p_serialData = serialData;

    portHandle = proto_serialOpen();
    
    proto_serialSendUICommandMsg(portHandle, 1);
    proto_serialReadMovConfirmMsg(portHandle, &movConfirmMsg);
    
    printf("received confiramtion message: %d\n", movConfirmMsg);


    // while (x < ITERATIONS) {
    // // while (1) {
    //     if (x == 0) { 
    //         navMsgFill1(x);
    //         printf("sending data1\n");
    //         proto_serialSendNavMsg(portHandle, &navMsg);
    //         
    //         // p_serialData = proto_serialReceiveFromMega(portHandle);
    //         // printf("we received %d\n", *p_serialData);
    //         
    //         /* put movement confirmation in local storage */
    //         proto_serialReadMovConfirmMsg(portHandle, &movConfirmMsg);
    //         printf("we received movement confirmation: %d\n", movConfirmMsg);
    //     }
    //     
    //     if (x == 1) {
    //         navMsgFill2();
    //         // navMsgFill1(x);
    //         printf("sending data2\n");
    //         proto_serialSendNavMsg(portHandle, &navMsg);
    //     
    //         // p_serialData = proto_serialReceiveFromMega(portHandle);
    //         // printf("we received %d\n", *p_serialData);
    // 
    //         /* put movement confirmation in local storage */
    //         proto_serialReadMovConfirmMsg(portHandle, &movConfirmMsg);
    //         printf("we received movement confirmation: %d\n", movConfirmMsg);
    //     }
    //     x++;
    // }


    sleep(1);
    
    proto_serialClose(portHandle);
}

void navMsgFill1(uint8_t n){
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

