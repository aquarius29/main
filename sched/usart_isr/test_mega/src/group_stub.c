
/*!
 *  Module representing a groups code that will be scheduled and then
 *  reads a message sent on the serial port
 */

#include <stdio.h>

#include "WProgram.h"

#include "proto_stub.h"
#include "proto_msg_structs.h"
#include "group_stub.h"

#define TRUE 1
#define FALSE 0

void group_run(void){
    struct navData *navMsg = NULL;
    /* read data here */
    if (proto_isNewNavMsg() == TRUE) {
        navMsg = proto_readNavMsg();
        
        if (navMsg->type == 10) {
            digitalWrite(12, HIGH);
        }
        else if (navMsg->type == 50) {
            digitalWrite(13, HIGH);
        }
    }
}