
/*
 *  initial code for prototyping a way to receive serial data on the
 *  USART port
 *
 *  TODO: an rx-intetrrupt can occur before the last message is copied
 *  completely to a buffer, code is very unsafe in this regard
 *
 *  author: Joakim
 */

/* WProgram.h includes all needed AVR headers */
#include "WProgram.h"

/* CPU clock speed */
#define FOSC 16000000UL

/* desired baud-rate */
#define BAUD 9600

/*
 *  Value for baud-rate register calculated using the defined clock speed
 *  and desired baud-rate. Calculation is taken from atmels datasheet
 */
#define UBRR_SETTING (uint16_t)((FOSC/(BAUD*16UL))-1)

/* maximum length of message and size of buffer that holds the message */
#define MAX_MSG_LEN 40

#define TRUE 1
#define FALSE 0

static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target);

volatile static uint8_t dataBuffer[MAX_MSG_LEN];
static uint8_t completeMsg[MAX_MSG_LEN];

volatile static uint8_t msgLen = 0;
volatile static uint8_t bytesReceived = 0;
volatile static uint8_t isMsgComplete = FALSE;

uint8_t *proto_getRxMsg(void){
    if (isMsgComplete == TRUE) {
        digitalWrite(13, HIGH);

        /* copy buffer to a new array */
        copyBuf(dataBuffer, completeMsg);
        if (completeMsg[0] == 3) {
            digitalWrite(12, HIGH);
        }
        else {
            digitalWrite(12, LOW);
        }
            
        isMsgComplete = FALSE;
    }
    else {
        return NULL;
    }
}

/*
 *  Interrupt service routine for RX Receive Interrupt on USART0
 *
 *  @author Joakim
 */
ISR(USART0_RX_vect){
    uint8_t data;

    data = UDR0;
        
    if (bytesReceived > 0 && bytesReceived < MAX_MSG_LEN) {
        if (bytesReceived <= msgLen) {
            
            dataBuffer[bytesReceived] = data;
            bytesReceived++;

            if (bytesReceived == msgLen) {
                isMsgComplete = TRUE;
                bytesReceived = 0;
            }
        }
    }
    else if (bytesReceived == 0) {
        msgLen = data;
        dataBuffer[bytesReceived] = msgLen;
        bytesReceived++;
    }
    else if (bytesReceived >= MAX_MSG_LEN) {
        // too long message, light upp error-led
        digitalWrite(12, HIGH);
    }
}

/* Remove this function later */
void setupMega(void){
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
}

/*
 *  USART initialization function for USART port 0
 * 
 *  @author Joakim 
 */
uint8_t proto_usartInitMega(void){
    setupMega(); /* should not be called in prduction code */
    
    /* disable global interrupts */
    cli();
    
    /* clear registers before setting them up */
    UCSR0C = 0x00;
    UCSR0B = 0x00;
    UCSR0A = 0x00;
    
    /* set serial frame format to 8data bits, 1stop bit */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    
    /* set baud rate registers */
    UBRR0H = (uint8_t)(UBRR_SETTING >> 8);
    UBRR0L = (uint8_t)UBRR_SETTING;

    /* enable RX-complete interrupt, receiver and transmitter */
    UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);

    /* enable global interrupts */
    sei();

    return 1;
}

static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target){
    register uint8_t i;
    
    for (i = 0; i < msgLen; i++) {
        target[i] = source[i]; 
    }

    return 1;
}

// static uint8_t copyBuf(volatile uint8_t *source, uint8_t *target){
//     while (*source != '\0') {
//         *target++ = *source++;
//     }
//     
//     return 1;
// }

