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
 *  @file   proto_handler.h
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
 *
 *  @details    
 */

#ifndef PROTO_HANDLER_H
#define PROTO_HANDLER_H
 
#include <stdint.h>
#include "proto_msg_structs.h" 
 
/*!
 *  Function calls the USART setup function in the proto_usart_isr_mega \n
 *  module. (This is to gather all lowest level hardware interaction to \n
 *  that module)
 *
 *  Returns:
 *  1 on success
 *
 *  @author Joakim
 */
uint8_t proto_setupUSART(void);

/*!
 *  Function checks if there is any new complete message received on the
 *  serial port.
 *
 *  Returns:
 *  1 if there was any message, 0 if not
 *
 *  @author Joakim
 */
uint8_t proto_processMessages(void);

/*!
 *  Function returns TRUE if there is a new navigation message, \n
 *  FALSE if not \n
 *
 *  @author Joakim
 */
uint8_t proto_isNewNavMsg(void);

/*!
 *  Function returns a pointer to the currently stored navigation \n
 *  message \n
 * 
 *  @author Joakim
 */
struct navData *proto_readNavMsg(void);

/*!
 *  Function returns TRUE if there is a new UI command message, \n
 *  FALSE if not \n
 *
 *  @author Joakim
 */
uint8_t proto_isNewUICommandMsg(void);

/*!
 *  Function returns the currently stored UI command \n
 * 
 *  @author Joakim
 */
uint8_t proto_readUICommandMsg(void);

#endif /* PROTO_HANDLER_H */