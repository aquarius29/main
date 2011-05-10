
#include "proto_usart_isr_mega.h"

#define MSG_LEN 40

uint8_t proto_init(void){
    proto_usartInitMega();
}

uint8_t proto_run(void){
    uint8_t msgBuffer[MSG_LEN];
    
    if (proto_getRxMsg() != NULL) {
        /* there is an unread message */
    }
    else {
        /* there is no unread message */
    }
}