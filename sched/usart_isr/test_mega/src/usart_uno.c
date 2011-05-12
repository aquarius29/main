
/*!
 *  @file usart_mega.c
 *
 *  @brief Module for reading and writing to the atmega2560 USART ports
 *
 *  @author Joakim, Justin
 *  @date 2011-05-02
 *  @history    2011-04-28 - Started with this module. - Joakim
 *              2011-05-02 - Added Doxygen comments. - Joakim
 *              2011-05-02 - Made a working version with asynchronous, 
 *                           non-interrupt, non-blocking (partly)
 *                           send/receive. - Justin, Joakim
 *
 *  @details    Handles low-level serial communication with the mega-board.
 *              This was written to see if the non-interrupt way would work,
 *              turns out it will be difficult in combination with the
 *              asynchronous nature of the system. This way of doing it
 *              will be put on ice for the time beeing.
 */



#ifdef ARDUINO

#include <stdint.h>

/* WProgram.h includes all AVR headers that are used */
#include "WProgram.h"

#endif /* ARDUINO */

#ifdef PC

#include <stdio.h>

#endif /* PC */

#include "usart_uno.h"

/* CPU clock freq. */
#define FOSC 16000000UL

/* desired baud-rate */
#define BAUD 9600

/* 
 *  Calculation of UBRR register (baud-rate register) value to be set.
 *  Calculation taken from atmels data sheet.
 */
#define UBRR_SETTING (uint16_t)((FOSC/(16UL*BAUD))-1)

#define BUFFER_MAX 3

static uint8_t dataBuffer[BUFFER_MAX] = {1,2,3};
static uint8_t dataBuffer2[BUFFER_MAX] = {4,5,6};

void setup(void);
void USART_init(uint16_t ubrr);
void USART_transmit(uint8_t data);
uint8_t USART_receive(void);
void run(void);
uint8_t serialSend(uint8_t *data, uint8_t len);


int usart_uno(void){
    #ifdef ARDUINO
        init();
    #endif /* ARDUINO */

    setup();
    
    uint8_t iterations = 1;
    uint8_t i = 0;
    while (i < iterations) {
        run();
        i++;
    }
    while (1) {
        ;
    }
    
    return 0;
}

void setup(void){
    delay(2000);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);

    USART_init(UBRR_SETTING);
}

/*!
 *  USART_init
 */
void USART_init(uint16_t ubrr){
    cli();
    
    /* clear registers before set-up */
    UCSR0B = 0x00;
    UCSR0A = 0x00;
 
    /* set frame format to 8 data bits, 1 stop bit */
    UCSR0C = (3 << UCSZ00); 

    /* set baud rate */
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;

    // /* clear USART1 I/O data register */
    /* NEVER EVER DO THIS AND THEN FORGET ABOUT IT!!! */
    // UDR1 = 0x00;
    
    /* enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    sei();
}

/*!
 *  USART_tansmit taken from a code example in the datasheet for atmega2560
 */
void USART_transmit(uint8_t data){
    /* wait for empty transmit buffer *** BLOCKING?! */
    while (!(UCSR0A & (1 << UDRE0))){
        ;
    }
    /* put data in buffer, sends the data */
    UDR0 = data;
}

/*!
 *  USART_receive taken from a code example in the datasheet for atmega2560
 */
uint8_t USART_receive(void){
    return 0;
}

void run(void){
    // uint8_t data = 0;
    uint8_t i;
    
    delay(1000);    
    digitalWrite(13, HIGH);

    uint8_t data1[] = {3,2,1};
    serialSend(data1, 3);
    
    delay(1000);
    digitalWrite(13, LOW);
    
}

uint8_t serialSend(uint8_t *data, uint8_t len){
    uint8_t i;
    
    for (i = 0; i < len; i++) {
        USART_transmit(*data);
        data++;
    }
}




