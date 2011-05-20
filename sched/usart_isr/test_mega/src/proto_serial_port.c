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
 *  @file proto_serial_port.c
 *  
 *  @brief Module for initalizing, opening and closing serial port \n
 *
 *  @author     Michal, Joakim
 *  @date       2011-05-19
 *
 *  @history    2011-05-06 - Created this module, a lot of code is from \n
 *                           Michals test module for serial port comm. \n
 *                           - Joakim \n
 *              2011-05-12 - Added a delay in code to let port initialize \n
 *                           properly. Previously this had to be done by \n
 *                           the module making the call to serialOpen \n
 *                           -Joakim \n
 *              2011-05-19 - Added license text and additional comments \n
 *                           - Joakim \n
 *
 *  @details The port settings are taken from Michals code he used while \n
 *           testing and researching this. \n
 */
 
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>

#include "proto_serial_port.h"
#include "proto_serial_define.h"

#define BAUD_RATE B9600
 
static int32_t portHandle;
static uint8_t isPortOpen = FALSE;

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
int32_t proto_serialOpen(void){
    struct termios options;

    portHandle = open(PROTO_SERIAL_PORT, (O_RDWR | O_NOCTTY | O_NDELAY));

    fcntl(portHandle, F_SETFL, 0);
    
    tcgetattr(portHandle, &options);
    cfsetispeed(&options, BAUD_RATE);
    cfsetospeed(&options, BAUD_RATE);
    options.c_cflag |= CLOCAL;
    options.c_cflag |= CREAD;
    options.c_cflag |= CS8;
 
    options.c_oflag &= ~OPOST;

    tcsetattr(portHandle, TCSANOW, &options);

    /* delay is to make sure the port has time to initialize */
    sleep(1);
        
    isPortOpen = TRUE;
        
    return portHandle;
}

/* 
 *  function for closing port, takes an integer as the port handle
 *  @author Joakim
 */
uint8_t proto_serialClose(int32_t portHandle){
    close(portHandle);
 
    return 1;
}
