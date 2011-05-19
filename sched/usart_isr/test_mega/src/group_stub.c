
/*!
 *  Module representing a groups code that will be scheduled and then
 *  reads a message sent on the serial port
 */

#include <stdio.h>

#include "WProgram.h"

#include "proto_msg_structs.h"
#include "group_stub.h"
#include "proto_serial_comm.h"

#define TRUE 1
#define FALSE 0

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

    uiCommand = proto_serialReadUICommandMsg();
    
    if (uiCommand == 7) {
        digitalWrite(10, HIGH);
        proto_serialSendMovConfirmMsg(data);
    }

    // /* trying to receive a UI action command message to movement code */
    //  uiCommand = proto_serialReadUICommandMsg();
    //  
    //  if (uiCommand != 0) {
    //      if (uiCommand == 7) {
    //          digitalWrite(12, HIGH);
    //          proto_serialSendMovConfirmMsg(data2);
    //      }
    //      switch (uiCommand) {
    //          case UP :
    //              digitalWrite(13, HIGH);
    //          case DOWN :
    //              digitalWrite(12, HIGH);
    //          case BACK :
    //              digitalWrite(11, HIGH);
    //          case FORWARD :
    //              digitalWrite(10, HIGH);
    //          case LEFT :
    //              digitalWrite(9, HIGH);
    //          case RIGHT :
    //              digitalWrite(8, HIGH);
    //          case HOVER :
    //              digitalWrite(7, HIGH);
    //              proto_serialSendMovConfirmMsg(data);
    //          case LAND :
    //              digitalWrite(13, LOW);
    //              digitalWrite(12, LOW);
    //              digitalWrite(11, LOW);
    //              digitalWrite(10, LOW);
    //              digitalWrite(9, LOW);
    //              digitalWrite(8, LOW);
    //              digitalWrite(7, LOW);
    //      }
    //  }
 
    // /* read data here */
    // navMsg = proto_serialReadNavMsg();
    // if (navMsg != NULL) {
    //     digitalWrite(13, LOW);
    //     if (navMsg->type == 10) {
    //         digitalWrite(12, HIGH);
    //         proto_serialSendMovConfirmMsg(data);
    //     }
    //     else if (navMsg->type == 50) {
    //         // digitalWrite(13, HIGH);
    //         proto_serialSendMovConfirmMsg(data2);
    //     }
    // }
    // else {
    //     digitalWrite(13, HIGH);
    // }

}



