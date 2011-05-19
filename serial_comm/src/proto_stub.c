
#include <stdio.h>

#include "WProgram.h"
#include "proto_usart_isr_mega.h"
#include "proto_deserializer.h"
#include "proto_stub.h"
#include "proto_msg_structs.h"
#include "proto_serial_define.h"

static struct navData navMsg;
static uint8_t uiCommand;
static uint8_t isNewNavMsg = FALSE;
static uint8_t isNewUICommandMsg = FALSE;


static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target);
static uint8_t deSerializeMsg(uint8_t *serialMsg);


uint8_t proto_setupPort(void){
    proto_usartInitMega();
}

uint8_t proto_processMessages(void){
    uint8_t serialMsg[PROTO_MAX_MSG_LEN];
    
    /* check if there is an unread message */
    if (proto_isRxMsgComplete() == TRUE) {
        
        /* copy to local buffer */
        copyBuf(proto_getRxMsg(), serialMsg);
        
        /* de-serialize data and re-construct the received struct */
        deSerializeMsg(serialMsg);

        return 1;
    }
    /* there is no unread message */
    else {
        return 0;
    }
    
    // /* check if there are any messages that should be sent */
    // if () {
    //     
    // }
    // /* there are no messages to be sent */
    // else {
    //     
    // }
}

uint8_t proto_isNewUICommandMsg(void){
    return isNewUICommandMsg;
}

uint8_t proto_readUICommandMsg(void){
    isNewUICommandMsg = FALSE;
    return uiCommand;
}

uint8_t proto_isNewNavMsg(void){
    return isNewNavMsg;
}

struct navData *proto_readNavMsg(void){
    isNewNavMsg = FALSE;
    return &navMsg;
}

static uint8_t deSerializeMsg(uint8_t *serialMsg){
    uint8_t msgId;
    
    msgId = serialMsg[ID_INDEX];
    
    switch (msgId) {
        case MSG_ID_NAV :
            /* message is from Navigation */
            proto_reConstructMsgNav(serialMsg, &navMsg);
            isNewNavMsg = TRUE;
            
        case MSG_ID_UI_COMMAND :
            proto_reConstructMsgUICommand(serialMsg, &uiCommand);
            isNewUICommandMsg = TRUE;
        
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
