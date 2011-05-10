
#include <stdio.h>

#include "WProgram.h"
#include "proto_usart_isr_mega.h"
#include "proto_stub.h"

static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target);


uint8_t proto_init(void){
    proto_usartInitMega();
}

uint8_t proto_run(void){
    uint8_t msgBuffer[PROTO_MAX_MSG_LEN];
    
    /* there is an unread message */
    if (proto_isRxMsgComplete()) {
        
        /* copy to local buffer */
        copyBuf(proto_getRxMsg(), msgBuffer);
        
        /* de-serialize data and re-construct the sent struct */
        
        return 1;
    }
    /* there is no unread message */
    else {
        return 0;
    }
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
