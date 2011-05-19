/***************************************************************************
 * Copyright (C) 2011  Joakim Gross, Justin Wagner
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
 *  @file   proto_usart_isr_mega.c
 *
 *  @brief  Module handles the lowest level hardware interaction of the \n
 *          serial API \n
 *
 *  @author Joakim, Justin
 *  @date   2011-05-19
 *
 *  @history    2011-05-06 - Created this module - Joakim
 *              2011-05-10 - Lots of trial and error...
 *              2011-05-19 - Added license text and more comments - Joakim
 *
 *  @details Module is probably vulnerable to lots of things. \n
 *           Limited testing using the real behavious of both the \n
 *           systems intended to use this code has led to this. \n
 *           For example an Rx-interrupt can occur before the last \n
 *           message is copied to the buffer not used by the ISR. \n
 *           Also the performance is not tested while both systems \n
 *           working as intended. \n
 *
 *           This module does not work and probably won't link \n
 *           with the rest of the code IF that also uses the serial \n
 *           comm.-functionality that is supplied with WProgram.h \n
 *           (in HardwareSerial.cpp for example). \n
 *
 *           How the ISR code actually works when multiple other modules \n
 *           use the millis() function from the Arduino libs \n
 *           (to get timestamps) is not fully understood. The millis \n
 *           function and other functions dependent on it (delay stuff) \n
 *           disables interrupts on a global level (using cli() ). \n
 */

/* WProgram.h includes all needed AVR headers */
#include "WProgram.h"

#include "proto_usart_isr_mega.h"
#include "proto_serial_define.h"

/* static data */
static uint8_t completeBuffer[PROTO_MAX_MSG_LEN];
volatile static uint8_t dataBuffer[PROTO_MAX_MSG_LEN];

volatile static uint8_t msgLen = 0;
volatile static uint8_t bytesReceived = 0;
volatile static uint8_t isMsgComplete = FALSE;

/* static function prototypes */
static void USART_transmit(uint8_t data);
static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target);


/*!
 *  proto_usartInitMega
 *
 *  Function initializes the Mega-board by setting the registers
 *  for the relevant interrupts and USART ports
 *
 *  Returns: a 1 on success, a 0 on failure
 *
 *  @author Joakim
 */
uint8_t proto_usartInitMega(void){
    /* disable global interrupts */
    cli();
    
    /* clear registers before setting them up */
    UCSR0C = 0x00;
    UCSR0B = 0x00;
    UCSR0A = 0x00;
    
    /* set serial frame format to 8data bits, 1stop bit */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    
    /* set baud rate registers */
    UBRR0H = (uint8_t)(PROTO_UBRR_SETTING >> 8);
    UBRR0L = (uint8_t)PROTO_UBRR_SETTING;

    /* enable RX-complete interrupt, receiver and transmitter */
    UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);

    /* enable global interrupts */
    sei();

    return 1;
}

/*!
 *  proto_isRxMsgComplete
 *
 *  Function checks if there is a complete message read from Rx
 *
 *  Returns: 1 if true, 0 if false
 *
 *  @author Joakim
 */
uint8_t proto_isRxMsgComplete(void){
    return isMsgComplete;
}

/*!
 *  proto_getRxMsg
 *
 *  Function returns the current complete message received from Rx
 *
 *  Returns: a pointer to a buffer (uint8_t array) with the message
 *
 *  @author Joakim
 */
uint8_t *proto_getRxMsg(void){
    if (isMsgComplete == TRUE) {
        isMsgComplete = FALSE;
        return completeBuffer;
    }
    else {
        return NULL;
    }
}

/*!
 *  proto_usartTransmit
 *
 *  Function sends the data passed as argument using the USART port
 *
 *  @author Joakim
 */
uint8_t proto_usartTransmit(uint8_t *serialData){
    while (*serialData != '\0') {
        USART_transmit(*serialData);
        serialData++;
    }

    return 1;
}

/*!
 *  USART_tansmit taken from a code example in the datasheet for atmega2560
 */
static void USART_transmit(uint8_t data){
    /* wait for empty transmit buffer *** BLOCKING! */
    while (!(UCSR0A & (1 << UDRE0))){
        ;
    }
    /* put data in buffer, sends the data */
    UDR0 = data;
}

/*
 *  Copies the buffer that is used to gather the bytes received 
 *  on the Rx-interrupt into a buffer that isn't as vulnerable
 *
 *  Unsafe for out of bounds problems if msgLen is read wrongly
 *  by the ISR
 */
static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target){
    register uint8_t i;
    
    if (source != NULL && target != NULL) {
        for (i = 0; i < msgLen; i++) {
            target[i] = source[i]; 
        }
        return 1;
    }
    else {
        return 0;
    }
}

/*
 *  Interrupt service routine for RX Receive Interrupt on USART0
 *
 *  Does very little to check for badly formatted messages! Can not handle
 *  multiple messages if they are not sent in a proper way.
 *
 *  Should be possible to avoid three level deep if-nesting...
 *
 *  @author Joakim, Justin
 */
ISR(USART0_RX_vect){
    uint8_t data;

    data = UDR0;
        
    if (bytesReceived > 0 && bytesReceived < PROTO_MAX_MSG_LEN) {
        if (bytesReceived <= msgLen) {
            
            dataBuffer[bytesReceived] = data;
            bytesReceived++;

            if (bytesReceived == msgLen) {
                isMsgComplete = TRUE;
                copyBuf(dataBuffer, completeBuffer);                
                bytesReceived = 0;
            }
        }
    }
    else if (bytesReceived == 0) {
        msgLen = data;
        dataBuffer[bytesReceived] = msgLen;
        bytesReceived++;
    }
    else if (bytesReceived >= PROTO_MAX_MSG_LEN) {
        /* if we end up here, there is an error */  
    }
}
