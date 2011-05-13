
#ifndef PROTO_USART_ISR_MEGA_H
#define PROTO_USART_ISR_MEGA_H

#include <stdint.h>

/* CPU clock speed */
#define PROTO_FOSC 16000000UL

/* desired baud-rate */
#define PROTO_BAUD 9600

/*
 *  Value for baud-rate register calculated using the defined clock speed
 *  and desired baud-rate. Calculation is taken from atmels datasheet
 */
#define PROTO_UBRR_SETTING (uint16_t)((PROTO_FOSC/(PROTO_BAUD*16UL))-1)


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
uint8_t proto_usartInitMega(void);

/*!
 *  proto_isRxMsgComplete
 *
 *  Function checks if there is a complete message read from Rx
 *
 *  Returns: 1 if true, 0 if false
 *
 *  @author Joakim
 */
uint8_t proto_isRxMsgComplete(void);

/*!
 *  proto_getRxMsg
 *
 *  Function returns the current complete message received from Rx
 *
 *  Returns: a pointer to a buffer (uint8_t array) with the message
 *
 *  @author Joakim
 */
uint8_t *proto_getRxMsg(void);

/*!
 *
 *
 *
 */
uint8_t proto_usartTransmit(uint8_t *serialData);
 
 

#endif /* PROTO_USART_ISR_MEGA_H */