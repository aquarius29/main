
#include <stdio.h>

#include "WProgram.h"
#include "proto_usart_isr_mega.h"
#include "proto_deserializer.h"
#include "proto_stub.h"
#include "proto_msg_structs.h"
#include "proto_serial_define.h"

static struct navData navMsg;
static uint8_t isNewNavMsg = FALSE;

static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target);
static uint8_t deSerializeMsg(uint8_t *serialMsg);

uint8_t proto_init(void){
    proto_usartInitMega();
}

uint8_t proto_run(void){
    uint8_t serialMsg[PROTO_MAX_MSG_LEN];
    
    /* there is an unread message */
    if (proto_isRxMsgComplete()) {
        
        /* copy to local buffer */
        copyBuf(proto_getRxMsg(), serialMsg);
        
        /* 
         *  de-serialize data and re-construct the received struct
         */
        deSerializeMsg(serialMsg);
        isNewNavMsg = TRUE;
        // if (navMsg.type == 10) {
        //     digitalWrite(12, HIGH);
        // }

        return 1;
    }
    /* there is no unread message */
    else {
        return 0;
    }
}

uint8_t proto_isNewNavMsg(void){
    return isNewNavMsg;
}

struct navData *proto_readNavMsg(void){
    return &navMsg;
}

static uint8_t deSerializeMsg(uint8_t *serialMsg){
    uint8_t msgId;
    
    msgId = serialMsg[ID_INDEX];
    
    switch (msgId) {
        case MSG_ID_NAV :
            /* message is from Navigation */
            proto_reConstructMsgNav(serialMsg, &navMsg);
        default :
            /* we should never end up here */
            ;
    }
    
    return 1;
}
/*
 *  is this unsafe with regard to getting out of bounds? 
 */
static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target){
    register uint8_t i;
    uint8_t msgLen;
    
    if (source != NULL && target != NULL) {
        msgLen = source[0];        
        for (i = 0; i < msgLen; i++) {
            target[i] = source[i]; 
        }
        return 1;
    }
    else {
        return 0;
    }
}
