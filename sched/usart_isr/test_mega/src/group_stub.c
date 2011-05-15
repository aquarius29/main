
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

uint8_t sentFlag = FALSE;

void group_run(void){
    struct navData *navMsg = NULL;
    uint8_t data = 100;
    uint8_t data2 = 200;

    /* read data here */
    navMsg = proto_serialReadNavMsg();
    if (navMsg != NULL) {
        if (navMsg->type == 10) {
            digitalWrite(12, HIGH);
            // proto_serialSendMovConfirmMsg(data);
            if (sentFlag == FALSE) {
                proto_serialSendMovConfirmMsg(data2);
                sentFlag = TRUE;
            }
        }
        else if (navMsg->type == 50) {
            digitalWrite(13, HIGH);
            if (sentFlag == FALSE) {
                proto_serialSendMovConfirmMsg(data);
                sentFlag = TRUE;
            }
        }
    }

    // navMsg = proto_serialReadNavMsg();
    // if (navMsg != NULL) {
    //     if (navMsg->type == 50) {
    //         digitalWrite(13, HIGH);
    //     }
    //     // proto_serialSendMovConfirmMsg(data);
    // }
    
    // if (sentFlag == FALSE) {
    //     proto_serialSendMovConfirmMsg(data2);
    //     sentFlag = TRUE;
    // }
}



