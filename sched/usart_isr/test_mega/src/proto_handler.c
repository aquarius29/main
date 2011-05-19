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
 *  @file   proto_handler.c
 *
 *  @brief  Module checks if there are any messages received on USART0, \n
 *          copies them to local buffer, de-serialize them and \n
 *          keeps them available to other modules \n
 *
 *  @author Joakim
 *  @date   2011-05-19
 *
 *  @history    2011-05-06 - Created this module - Joakim \n
 *              2011-05-19 - Added license text and more comments. \n
 *                           Also fixed a bug in the switch statement \n
 *                           in deSerializeMsg  - Joakim \n
 *
 *  @details There is some functionality missing at the moment. There \n
 *           should be logic in proto_processMessages to check if there \n
 *           are any messages from other groups to be sent on the serial \n
 *           port. Also, these messages should be stored here until \n
 *           they can be sent. \n
 */

#include <stdio.h>

#include "proto_handler.h"
#include "proto_usart_isr_mega.h"
#include "proto_deserializer.h"
#include "proto_msg_structs.h"
#include "proto_serial_define.h"

/* static data */
static struct navData navMsg;   /* stores latest navigation message */
static uint8_t uiCommand;       /* stores latest UI command */

static uint8_t isNewNavMsg = FALSE;
static uint8_t isNewUICommandMsg = FALSE;

/* static prototypes */
static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target);
static uint8_t deSerializeMsg(uint8_t *serialMsg);

/*!
 *  Function calls the USART setup function in the proto_usart_isr_mega \n
 *  module. (This is to gather all lowest level hardware interaction to \n
 *  that module)
 *
 *  Returns: \n
 *  1 on success
 *
 *  @author Joakim
 */
uint8_t proto_setupUSART(void){
    proto_usartInitMega();
}

/*!
 *  Function checks if there is any new complete message received on the \n
 *  serial port. \n
 *
 *  Returns: \n
 *  1 if there was any message, 0 if not
 *
 *  @author Joakim
 */
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
    
    /* 
     *  check if there are any messages that should be sent here!
     *  this is still to be implemented, at the moment other modules
     *  call proto_usart_isr_mega directly
     */
}

/*!
 *  Function returns TRUE if there is a new UI command message, \n
 *  FALSE if not \n
 *
 *  @author Joakim
 */
uint8_t proto_isNewUICommandMsg(void){
    return isNewUICommandMsg;
}

/*!
 *  Function returns the currently stored UI command \n
 * 
 *  @author Joakim
 */
uint8_t proto_readUICommandMsg(void){
    isNewUICommandMsg = FALSE;  /* message is read, mark it as old */
    return uiCommand;
}

/*!
 *  Function returns TRUE if there is a new navigation message, \n
 *  FALSE if not \n
 *
 *  @author Joakim
 */
uint8_t proto_isNewNavMsg(void){
    return isNewNavMsg;
}

/*!
 *  Function returns a pointer to the currently stored navigation \n
 *  message \n
 * 
 *  @author Joakim
 */
struct navData *proto_readNavMsg(void){
    isNewNavMsg = FALSE;    /* message is read, mark it as old */
    return &navMsg;
}

/*
 *  Function checks what type of message and re-constructs it \n
 *
 *  @author Joakim
 */
static uint8_t deSerializeMsg(uint8_t *serialMsg){
    uint8_t msgId;
    
    msgId = serialMsg[ID_INDEX];
    
    switch (msgId) {
        case MSG_ID_NAV :
            proto_reConstructMsgNav(serialMsg, &navMsg);
            isNewNavMsg = TRUE;
            break;
            
        case MSG_ID_UI_COMMAND :
            proto_reConstructMsgUICommand(serialMsg, &uiCommand);
            isNewUICommandMsg = TRUE;
            break;
        
        default :
            /* we should never end up here */
            break;
    }
    
    return 1;
}

/*
 *  @author Joakim
 *
 *  this is unsafe for getting out of bounds if the byte read as length
 *  is not correct
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
