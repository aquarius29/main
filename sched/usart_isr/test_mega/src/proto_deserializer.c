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
 *  @file   proto_deserializer.c
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

#include "proto_serial_define.h"
#include "proto_deserializer.h"
#include "proto_msg_structs.h"

/*!
 *  Function reconstructs a serialized UI command message \n
 *
 *  Input:
 *  serialData - pointer to the array that will hold the serialized data\n
 *  uiCommand - pointer to variable that will hold the reconstructed message\n
 *
 *  Returns:
 *  1 on success
 *
 *  @author Joakim
 */
uint8_t proto_reConstructMsgUICommand(uint8_t *serialData, uint8_t *uiCommand){
  *uiCommand = serialData[UI_COMMAND_VAL_INDEX];
    
    return 1;
}

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
 *  @author Joakim, Justin
 */
uint8_t proto_reConstructMsgNav(uint8_t *data, struct navData *dataStruct){
    dataStruct->type = data[NAV_TYPE_INDEX];
    dataStruct->order = data[NAV_ORDER_INDEX];
    
    dataStruct->height = 
        (uint16_t)(data[NAV_HEIGHT_INDEX_HIGHBYTE] << 8) | 
        (uint16_t)(data[NAV_HEIGHT_INDEX_LOWBYTE]);
    
    dataStruct->distance = 
        (uint16_t)(data[NAV_DISTANCE_INDEX_HIGHBYTE] << 8) | 
        (uint16_t)(data[NAV_DISTANCE_INDEX_LOWBYTE]);
    
    dataStruct->yaw = 
        (uint16_t)(data[NAV_YAW_INDEX_HIGHBYTE] << 8) | 
        (uint16_t)(data[NAV_YAW_INDEX_LOWBYTE]);
                    
    return 1;
}

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
uint8_t proto_reConstructMovConfirmMsg(uint8_t *serialData, uint8_t *target){
    *target = serialData[MOV_CONFIRM_VAL_INDEX];
 
    return 1;
}

