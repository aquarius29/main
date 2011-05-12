
/*!
 *  @file proto_srial_port.c
 *  
 *  @brief Module for initalizing, opening and closing serial port
 *
 *  @author     Michal, Joakim
 *  @date       2011-05-06
 *
 *  @history    2011-05-06 - Created this module, a lot of code is from
 *                           Michals test module for serial port comm.
 *                           - Joakim
 *              2011-05-12 - Added a delay in code to let port initialize
 *                           properly. Previously this had to be done by
 *                           the module making the call to serialOpen -Joakim
 *
 *  @details
 */
 
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>

#include "proto_serial_port.h" 
 
/* 
 *  function for initializing and opening port
 */
int32_t proto_serialOpen(void){
    struct termios options;
    int32_t portHandle;
    
    portHandle = open(PROTO_SERIAL_PORT, (O_RDWR | O_NOCTTY | O_NDELAY));
    /* perform error-checking on open return value here */

    
    /* put in comments to explain the port and serial options chosen */
    tcgetattr(portHandle, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= CLOCAL;
    options.c_cflag |= CREAD;
    options.c_cflag |= CS8;
 
    options.c_oflag &= ~OPOST;

    tcsetattr(portHandle, TCSANOW, &options);

    /* delay is to make sure the port has time to initialize */
    sleep(1);

    return portHandle;
}

/* 
 *  function for closing port, takes an integer as the port handle
 */
uint8_t proto_serialClose(int32_t portHandle){
    close(portHandle);
 
    return 1;
}