/***************************************************************************
 * Copyright (C) 2011  Joakim Gross
 * 
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

/*!
 *  @file   port_test.c
 *
 *  @brief  Module represents a group on the panda (sort of). It uses the \n
 *          serial API to open a serial port and send and receive \n
 *          data on it. \n
 *
 *  @author Joakim
 *  @date   2011-05-17
 *
 *  @detail This module ha been used to represent something on the Panda/PC \n
 *          that sends and receives on the serial port. It's nothing more \n
 *          to it, just test the serial API from here, send and read... \n
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

    /* this opens the serial device defined in proto_serial_port.h */
    portHandle = proto_serialOpen();
    
    // proto_serialSendUICommandMsg(portHandle, 2);
    // proto_serialReadMovConfirmMsg(portHandle, &movConfirmMsg);
    // 
    // printf("received confiramtion message: %d\n", movConfirmMsg);


    while (x < ITERATIONS) {
        if (x == 0) { 
            navMsgFill1(x);
            printf("sending data1\n");
            proto_serialSendNavMsg(portHandle, &navMsg);
            
            /* put movement confirmation in local storage */
            proto_serialReadMovConfirmMsg(portHandle, &movConfirmMsg);
            printf("we received movement confirmation: %d\n", movConfirmMsg);
        }
        
        if (x == 1) {
            navMsgFill2();
            // navMsgFill1(x);
            printf("sending data2\n");
            proto_serialSendNavMsg(portHandle, &navMsg);
        
            /* put movement confirmation in local storage */
            proto_serialReadMovConfirmMsg(portHandle, &movConfirmMsg);
            printf("we received movement confirmation: %d\n", movConfirmMsg);
        }
        x++;
    }


    sleep(1);
    
    proto_serialClose(portHandle);
}

void navMsgFill1(uint8_t n){
  navMsg.type = 10;
  navMsg.order = 2;
  navMsg.height = -1027;
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

