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
 *  @file   proto_usart_isr_mega.h
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
 *           (in HardwareSerial.cpp for example). 
 *
 *           How the ISR code actually works when multiple other modules \n
 *           use the millis() function from the Arduino libs \n
 *           (to get timestamps) is not fully understood. The millis \n
 *           function and other functions dependent on it (delay stuff) \n
 *           disables interrupts on a global level (using cli() ). \n
 */

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
 *  proto_usartTransmit
 *
 *  Function sends the data passed as argument using the USART port
 *
 *  @author Joakim
 */
uint8_t proto_usartTransmit(uint8_t *serialData);

#endif /* PROTO_USART_ISR_MEGA_H */