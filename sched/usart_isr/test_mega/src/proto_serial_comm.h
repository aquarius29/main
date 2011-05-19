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
 *  @file proto_serial_comm.h
 *  
 *  @brief Module for sending data on the serial port
 *
 *  @author     Joakim
 *  @date       2011-05-19
 *
 *  @history    2011-05-06 - Created this module - Joakim \n
 *              2011-05-12 - Added specific function for sending navigation \n
 *                           data which in turn uses the serialSend \n
 *                           function. Previous code versions made the user \n 
 *                           serialize the data first, this is now done \n
 *                           automatically. - Joakim \n
 *              2011-05-17 - Added more functions for receiving and sending \n
 *                           specific messages. Changed interface functions \n
 *                           to take a pointer to the data storage where \n
 *                           the message will be stored by the caller. \n
 *                           This is to reduce the need of having \n
 *                           proto-code responsible for keeping groups data \n
 *                           in scope and available. - Joakim \n
 *              2011-05-18 - Changed the sendUICommand back to take a \n
 *                           normal int as argument since it made it \n
 *                           easier. - Joakim \n
 *              2011-05-19 - Added license text and additional comments \n
 *                           - Joakim
 *
 *  @details    Module should be used by other modules to send and receive \n
 *              messages on the serial port by both the Panda/Pc and \n
 *              Arduino systems. For the Panda/Pc side the actual sending \n
 *              and receiving is done here. The same functionality for \n
 *              the Arduino side is more hardware related and is done \n
 *              in seperate modules that gets called from here. \n
 *              (proto_handler.c and proto_usart_isr_mega.c) \n
 */
 

#ifndef PROTO_SERIAL_COMM_H
#define PROTO_SERIAL_COMM_H

#include <stdint.h>
#include "proto_msg_structs.h"

#ifdef PC

/*!
 *  Function sends a UI command message to the mega-board \n
 *
 *  Input: \n
 *  uint32_t portHandle - the handle to the device to write to \n
 *  
 *  uint8_t command - the command that should be sent \n
 *
 *  Returns: \n
 *  1 on success \n
 *
 *  @author Joakim
 */
uint8_t proto_serialSendUICommandMsg(uint32_t portHandle, uint8_t command);

/*!
 *  Function sends a navigation message to the mega-board \n
 *
 *  Input: \n
 *  uint32_t portHandle - the handle to the device to write to \n
 *  
 *  struct navData *data - a pointer to the struct that holds the \n
 *      data to be sent \n
 *
 *  Returns: \n
 *  1 on success \n
 *
 *  @author Joakim
 */
uint8_t proto_serialSendNavMsg(int32_t portHandle, struct navData *data);

/*!
 *  Function reads and returns a movement confirmation message \n
 *
 *  Input: \n
 *  uint32_t portHandle - the handle to the device to write to \n
 *  
 *  uint8_t *targetStorage - a pointer to the data storage that will \n
 *      hold the message /n
 *
 *  Returns: \n
 *  1 on success \n
 *
 *  @author Joakim
 */
uint8_t proto_serialReadMovConfirmMsg(int32_t portHandle, 
                                        uint8_t *targetStorage);

#endif /* PC */

#ifdef ARDUINO

/*!
 *  Function reads and returns UI command message \n
 *
 *  Returns: \n
 *  the UI command if there is any, 0 if not
 *
 *  @author Joakim
 */
uint8_t proto_serialReadUICommandMsg(void);

/*!
 *  Function reads and returns a pointer to the navigation message \n
 *
 *  Returns: \n
 *  a pointer to the message if there is any, NULL otherwise
 *
 *  @author Joakim
 */
struct navData *proto_serialReadNavMsg(void);

/*!
 *  Function sends a movement confiramtion message to the Panda/PC \n
 *
 *  Input: \n
 *  uint8_t msg - the data to send \n
 *  
 *  Returns: \n
 *  1 on success \n
 *
 *  @author Joakim
 */
uint8_t proto_serialSendMovConfirmMsg(uint8_t msg);

#endif /* ARDUINO */

#endif /* PROTO_SERIAL_COMM_H */