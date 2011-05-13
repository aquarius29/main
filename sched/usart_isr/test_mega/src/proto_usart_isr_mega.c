
/*
 *  initial code for prototyping a way to receive serial data on the
 *  USART port
 *
 *  TODO: an rx-interrupt can occur before the last message is copied
 *  completely to a buffer, code is very unsafe in this regard
 *
 *  if there is a too long message sent the bytes after the real message
 *  are still read and treated as a new message. Need to flush the buffer?
 *
 *  author: Joakim
 */

/* WProgram.h includes all needed AVR headers */
#include "WProgram.h"

#include "proto_usart_isr_mega.h"

#define TRUE 1
#define FALSE 0

static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target);

static uint8_t completeBuffer[PROTO_MAX_MSG_LEN];
volatile static uint8_t dataBuffer[PROTO_MAX_MSG_LEN];
volatile static uint8_t msgLen = 0;
volatile static uint8_t bytesReceived = 0;
volatile static uint8_t isMsgComplete = FALSE;

static void USART_transmit(uint8_t data);



uint8_t proto_isRxMsgComplete(void){
    return isMsgComplete;
}

uint8_t *proto_getRxMsg(void){
    if (isMsgComplete == TRUE) {
        return completeBuffer;
    }
    else {
        return NULL;
    }
}

/*!
 *  USART_tansmit taken from a code example in the datasheet for atmega2560
 */
static void USART_transmit(uint8_t data){
    /* wait for empty transmit buffer *** BLOCKING?! */
    while (!(UCSR0A & (1 << UDRE0))){
        ;
    }
    /* put data in buffer, sends the data */
    UDR0 = data;
}

uint8_t proto_usartTransmit(uint8_t *serialData){
    while (*serialData != '\0') {
        USART_transmit(*serialData);
        serialData++;
    }

    return 1;
}

/*
 *  Interrupt service routine for RX Receive Interrupt on USART0
 *
 *  Does very little to check for badly formatted messages! Can not handle
 *  multiple messages if they are not sent in a proper way.
 *
 *  @author Joakim
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
                /* flush buffer here? */
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
        // too long message, light upp error-led
        digitalWrite(12, HIGH);
    }
}

/*
 *  USART initialization function for USART port 0
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

/*
 *  is this unsafe with regard to getting out of bounds? 
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
