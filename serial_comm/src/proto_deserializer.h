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
 *  @file   proto_deserializer.h
 *
 *  @brief  Module for de-serializing data received on the serial port
 *
 *  @author Joakim, Justin
 *  @date   2011-05-19
 *
 *  @history    2011-05-06 - Created this module - Joakim
 *              2011-05-19 - Added license text and more comments - Joakim
 *
 *  @details
 */


#ifndef PROTO_DESERIALIZER_H
#define PROTO_DESERIALIZER_H

#include <stdint.h>
#include "proto_msg_structs.h"
#include "proto_serial_define.h"

/*!
 *  Function reconstructs a serialized UI command message \n
 *
 *  Input: \n
 *  uint8_t *serialData - pointer to the array that will hold \n
 *      the serialized data\n
 *
 *  uint8_t *uiCommand - pointer to variable that will hold the \n
 *      reconstructed message\n
 *
 *  Returns: \n
 *  1 on success \n
 *
 *  @author Joakim
 */
uint8_t proto_reConstructMsgUICommand(uint8_t *serialData, 
                                        uint8_t *uiCommand);
                                        
/*!
 *  Function reconstructs a serialized navigation message \n
 *
 *  Input: \n
 *  uint8_t *serialData - pointer to the array that will hold \n
 *      the serialized data\n
 *
 *  struct navData *dataStruct - pointer to struct that will hold \n
 *      the reconstructed message \n
 *
 *  Returns: \n
 *  1 on success \n
 *
 *  @author Joakim
 */
uint8_t proto_reConstructMsgNav(uint8_t *serialData, 
                                    struct navData *dataStruct);
/*!
 *  Function reconstructs a serialized movement confirmation message \n
 *
 *  Input: \n
 *  uint8_t *serialData - pointer to the array that will hold \n
 *      the serialized data\n
 *
 *  uint8_t *target - pointer to variable that will hold the \n
 *      reconstructed message \n
 *
 *  Returns: \n
 *  1 on success \n
 *
 *  @author Joakim
 */
uint8_t proto_reConstructMovConfirmMsg(uint8_t *serialData, uint8_t *target);

#endif /* PROTO_DESERIALIZER_H */
