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
 *  @file proto_serial_define.h
 *
 *  @brief      Combining defines for the serialize/deserialize modules
 *  @author     Justin, Joakim
 *  @date       2011-05-18
 *
 *  @history    2011-05-12 - Created this header - Justin \n
 *              2011-05-18 - Adding more definitions for UI command \n
 *                           messages. - Joakim \n
 *              2011-05-19 - Added license text and additonal comments \n
 *                           - Joakim \n
 *
 *  @details
 */
#ifndef PROTO_SERIALDEFINE_H
#define PROTO_SERIALDEFINE_H

#define TRUE 1
#define FALSE 0

/* size of buffers used and maximum message length */
#define PROTO_MAX_MSG_LEN 100

/* Length defines for messages passed */
#define DATA_BUFFER_LEN PROTO_MAX_MSG_LEN
#define NAV_MSG_LEN 10
#define MOV_CONFIRM_MSG_LEN 3
#define UI_COMMAND_MSG_LEN 3

/* array index that holds message length */
#define LEN_INDEX 0

/* array index that holds message ID */
#define ID_INDEX 1

/* navigation message array indexes */
#define NAV_TYPE_INDEX 2
#define NAV_ORDER_INDEX 3
#define NAV_HEIGHT_INDEX_LOWBYTE 4
#define NAV_HEIGHT_INDEX_HIGHBYTE 5
#define NAV_DISTANCE_INDEX_LOWBYTE 6
#define NAV_DISTANCE_INDEX_HIGHBYTE 7
#define NAV_YAW_INDEX_LOWBYTE 8
#define NAV_YAW_INDEX_HIGHBYTE 9
#define NAV_NULL_INDEX 10

/* message ID for messages from navigation */
#define MSG_ID_NAV 1

/* movement confirm array indexes*/
#define MOV_CONFIRM_VAL_INDEX 2
#define MOV_CONFIRM_NULL_INDEX 3

/* message ID for movements confirmation message */
#define MSG_ID_MOV_CONFIRM 2

/* UI action command message array indexes */
#define UI_COMMAND_VAL_INDEX 2
#define UI_COMMAND_NULL_INDEX 3

/* message ID for UI commands */
#define MSG_ID_UI_COMMAND 3

#endif /* PROTO_SERIALDEFINE_H */
