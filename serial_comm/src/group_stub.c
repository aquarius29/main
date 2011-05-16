
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


void group_run(void){
    struct navData *navMsg = NULL;
    uint8_t data = 100;
    uint8_t data2 = 200;

    /* read data here */
    navMsg = proto_serialReadNavMsg();
    if (navMsg != NULL) {
        digitalWrite(13, LOW);
        if (navMsg->type == 10) {
            // digitalWrite(12, HIGH);
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



