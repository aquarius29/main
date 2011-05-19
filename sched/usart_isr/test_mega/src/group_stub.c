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
 *  @file   group_stub.c
 *
 *  @brief  Module representing a groups code that will be scheduled and \n
 *          then reads a message sent on the serial port \n
 *
 *  @author Joakim
 *  @date   2011-05-01
 */

#include <stdio.h>

#include "WProgram.h"

#include "proto_msg_structs.h"
#include "group_stub.h"
#include "proto_serial_comm.h"

#define TRUE 1
#define FALSE 0

/* UI commands for the test when we lit leds when clicking GUI */
#define UP 1
#define DOWN 2
#define BACK 3
#define FORWARD 4
#define LEFT 5
#define RIGHT 6
#define HOVER 7 
#define LAND 8

void group_run(void){
    struct navData *navMsg = NULL;
    uint8_t data = 100;
    uint8_t data2 = 200;
    uint8_t uiCommand = 0;


    /* trying to receive a UI action command message to movement code */
     // uiCommand = proto_serialReadUICommandMsg();
     
     // if (uiCommand != 0) {
     //     switch (uiCommand) {
     //         case UP :
     //             digitalWrite(13, HIGH);
     //             break;
     //         case DOWN :
     //             digitalWrite(12, HIGH);
     //             proto_serialSendMovConfirmMsg(data2);
     //             break;
     //         case BACK :
     //             digitalWrite(11, HIGH);
     //             break;
     //         case FORWARD :
     //             digitalWrite(10, HIGH);
     //             break;
     //         case LEFT :
     //             digitalWrite(9, HIGH);
     //             break;
     //         case RIGHT :
     //             digitalWrite(8, HIGH);
     //             break;
     //         case HOVER :
     //             digitalWrite(7, HIGH);
     //             proto_serialSendMovConfirmMsg(data);
     //             break;
     //         case LAND :
     //             digitalWrite(13, LOW);
     //             digitalWrite(12, LOW);
     //             digitalWrite(11, LOW);
     //             digitalWrite(10, LOW);
     //             digitalWrite(9, LOW);
     //             digitalWrite(8, LOW);
     //             digitalWrite(7, LOW);
     //             break;
     //     }
     // }
 
    /* below is an example of reading a struct message from navigation */
    navMsg = proto_serialReadNavMsg();
    if (navMsg != NULL) {
        digitalWrite(13, LOW);
        if (navMsg->height == -1027) {
            digitalWrite(12, HIGH);
            proto_serialSendMovConfirmMsg(data);
        }
        else if (navMsg->type == 50) {
            // digitalWrite(13, HIGH);
            proto_serialSendMovConfirmMsg(data2);
        }
    }
    else {
        digitalWrite(13, HIGH);
    }

}



