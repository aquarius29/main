/***************************************************************************
 * Copyright (C) 2011  Joakim Gross, Michal Musialik
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
 *  @file proto_serial_port.h
 *  
 *  @brief Module for initalizing, opening and closing serial port \n
 *
 *  @author     Michal, Joakim
 *  @date       2011-05-19
 *
 *  @history    2011-05-06 - Created this module - Joakim \n
 *              2011-05-19 - Added license text and additional comments \n
 *                           - Joakim \n
 *
 *  @details
 */

#ifndef PROTO_SERIAL_PORT_H
#define PROTO_SERIAL_PORT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define PROTO_SERIAL_PORT "/dev/tty.usbmodemfa141"

/* 
 *  Function for initializing and opening port \n
 *
 *  NOTE: Only call this function when in an initialization sequence \n
 *  of the system. Calling it while in fliht will be a disaster \n
 *
 *  Returns: \n
 *  a handle of the device to use as a serial port \n
 *
 *  TODO: \n
 *  Maybe make this return the already open port if called again? \n
 *
 *  @author Michal, Joakim
 */
int32_t proto_serialOpen(void);

/* 
 *  function for closing port, takes an integer as the port handle
 *  @author Joakim
 */
uint8_t proto_serialClose(int32_t);

#endif /* PROTO_SERIAL_PORT_H */