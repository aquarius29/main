
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

#define BAUD_RATE B9600
 
#define TRUE 1
#define FALSE 0
 
static int32_t portHandle;
static uint8_t isPortOpen = FALSE;

/* 
 *  function for getting the port if it's already open
 */
int32_t getSerialPort(void){
    if (isPortOpen == TRUE) {
        return portHandle;
    }
    else {
        return 0;
    }
}

/* 
 *  function for initializing and opening port
 *
 *  NOTE: Only call this function when in an initialization sequence
 *  of the system. Calling it while in fliht will be a disaster
 *
 *  Maybe make this return the already open port if called again?
 */
int32_t proto_serialOpen(void){
    struct termios options;

    portHandle = open(PROTO_SERIAL_PORT, (O_RDWR | O_NOCTTY | O_NDELAY));
    /* perform error-checking on open return value here */

    fcntl(portHandle, F_SETFL, 0);
    // fcntl(portHandle, F_SETFL, FNDELAY);
    
    /* put in comments to explain the port and serial options chosen */
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
 */
uint8_t proto_serialClose(int32_t portHandle){
    close(portHandle);
 
    return 1;
}
