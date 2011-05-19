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
 *  @file   proto_serializer.h
 *
 *  @brief  Module for serializing data to send over serial port
 *
 *  @author Joakim, Justin
 *  @date   2011-05-19
 *
 *  @history    2011-05-06 - Created this module - Joakim \n
 *              2011-05-19 - Added license text and more comments - Joakim \n
 *
 *  @details Module de-constructs messages and puts them into an array \n
 *           of bytes (this is the "serialization"). It also adds some \n
 *           meta-data in the array that is used on the receiving end, \n
 *           as well as the crucial null terminator. \n
 *           This is why even single byte values needs to go through here \n
 */

#ifndef PROTO_SERIALIZER_H
#define PROTO_SERIALIZER_H

#include "proto_msg_structs.h"

/*!
 *  Function for serializing a movement confirmation message so it can \n
 *  be sent over the serial port \n
 *
 *  Input: \n
 *  uint8_t data - the confirmation value to be serialized\n
 *
 *  uint8_t *serializedData - a pointer to the buffer that will hold \n
 *      the serialized data \n
 *
 *  Return: \n
 *      1 on success
 *
 *  @author Joakim, Justin
 */
uint8_t proto_serializeMovConfirmMsg(uint8_t data, uint8_t *serializedData);

/*!
 *  Function for serializing a navigation message so it can be sent \n
 *  over the serial port \n
 *
 *  Input: \n
 *  struct navData *data - a pointer to the struct that will be 
 *      serialized \n
 *
 *  uint8_t *serializedData - a pointer to the buffer that will hold \n
 *      the serialized data \n
 *
 *  Return: \n
 *      1 on success
 *
 *  @author Joakim, Justin
 */
uint8_t proto_serializeNavMsg(struct navData *, uint8_t *);

/*!
 *  Function for serializing a UI command message so it can be sent \n
 *  over the serial port \n
 *
 *  Input: \n
 *  uint8_t command - the command from UI to be serialized \n
 *
 *  uint8_t *serializedData - a pointer to the buffer that will hold \n
 *      the serialized data \n
 *
 *  Return: \n
 *      1 on success
 *
 *  @author Joakim, Justin
 */
uint8_t proto_serializeUICommandMsg(uint8_t command, 
                                    uint8_t *serializedData);
                                    
#endif /* PROTO_SERIALIZER_H */
