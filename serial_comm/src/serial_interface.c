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
 *  @file   serial_interface.c
 *
 *  @brief  Interface module for the serial code that needs to be scheduled \n
 *
 *  @author Joakim
 *  @date   2011-05-19
 *
 *  @history    2011-05-06 - Created this module - Joakim \n
 *              2011-05-19 - Added license text and more comments. \n
 */

#include "serial_interface.h"
#include "proto_handler.h"

int16_t serial_init(void){
    #ifdef ARDUINO
    proto_setupUSART();
    #endif /* ARDUINO */
    
    return 0;
}

int16_t serial_run(void){
    #ifdef ARDUINO
    proto_processMessages();
    #endif /* ARDUINO */
    
    return 0;
}
