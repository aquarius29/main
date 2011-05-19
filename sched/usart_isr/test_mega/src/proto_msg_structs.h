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
 *  @file   proto_msg_structs.h
 *
 *  @brief  Contains definitions of structs to be passed between modules.
 *
 *  @author Joakim, Justin
 *  @date   2011-05-19
 *
 *  @history    2011-05-06 - Created this module - Joakim \n
 *              2011-05-19 - Added license text and more comments - Joakim \n
 *
 *  @details Structs that are passed between groups over the serial port \n
 *           have to be de-constructed and then re-constructed. This header \n
 *           is used to make sure they share the same definition.
 */

#ifndef PROTO_MSG_STRUCTS_H
#define PROTO_MSG_STRUCTS_H

#include <stdint.h>

/* this is sent from navigation to movement */
struct navData {
    uint8_t type;
    uint8_t order;
    int16_t height;
    uint16_t distance;
    int16_t yaw;
};

#endif /* PROTO_MSG_STRUCTS_H */
