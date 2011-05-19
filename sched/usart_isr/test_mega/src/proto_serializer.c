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
 *  @file   proto_serializer.c
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
 *           meta-data in the array that is used on the receiving end. \n
 *           This is why even single byte values needs to go through here \n
 */

#include <stdint.h>
#include <stdio.h>

#include "proto_serial_define.h"
#include "proto_msg_structs.h"
#include "proto_serializer.h"

static uint8_t lowByte(uint16_t);
static uint8_t highByte(uint16_t);

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
                                    uint8_t *serializedData){
    serializedData[LEN_INDEX] = UI_COMMAND_MSG_LEN;
    serializedData[ID_INDEX] = MSG_ID_UI_COMMAND;
    serializedData[UI_COMMAND_VAL_INDEX] = command;
    serializedData[UI_COMMAND_NULL_INDEX] = '\0';

    return 1;
}

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
uint8_t proto_serializeMovConfirmMsg(uint8_t data, uint8_t *serializedData){
    serializedData[LEN_INDEX] = MOV_CONFIRM_MSG_LEN;
    serializedData[ID_INDEX] = MSG_ID_MOV_CONFIRM;
    serializedData[MOV_CONFIRM_VAL_INDEX] = data;
    serializedData[MOV_CONFIRM_NULL_INDEX] = '\0';
 
    return 1;
}

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
uint8_t proto_serializeNavMsg(struct navData *data, uint8_t *serializedData){
    serializedData[LEN_INDEX] = NAV_MSG_LEN;
    serializedData[ID_INDEX] = MSG_ID_NAV;
    serializedData[NAV_TYPE_INDEX] = data->type;
    serializedData[NAV_ORDER_INDEX] = data->order;
    serializedData[NAV_HEIGHT_INDEX_LOWBYTE] = lowByte(data->height);
    serializedData[NAV_HEIGHT_INDEX_HIGHBYTE] = highByte(data->height);
    serializedData[NAV_DISTANCE_INDEX_LOWBYTE] = lowByte(data->distance);
    serializedData[NAV_DISTANCE_INDEX_HIGHBYTE] = highByte(data->distance);
    serializedData[NAV_YAW_INDEX_LOWBYTE] = lowByte(data->yaw);
    serializedData[NAV_YAW_INDEX_HIGHBYTE] = highByte(data->yaw);
    serializedData[NAV_NULL_INDEX] = '\0';

    return 1;
}

/*
 *  takes a 16 bit value and returns the low byte (right-most byte) \n
 *  @author Joakim
 */
static uint8_t lowByte(uint16_t word){
    return (uint8_t)(word &= 0x00FF);   
}

/*
 *  takes a 16 bit value and returns the high byte (left-most byte) \n
 *  @author Joakim
 */
static uint8_t highByte(uint16_t word){
    return (uint8_t)(word >> 8);
}

