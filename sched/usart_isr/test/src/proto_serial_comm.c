
/*!
 *  @file proto_srial_comm.c
 *  
 *  @brief Module for initalizing, opening and closing serial port
 *
 *  @author     Joakim
 *  @date       2011-05-06
 *
 *  @history    2011-05-06 - Created this module - Joakim
 *
 *  @details
 */
 
#include "proto_serial_port.h"
#include "proto_serial_comm.h"

/*
 *  Function for sending serial data on serial port
 *  
 *  Takes a file descriptor to write to (serial port) and a byte array
 *  to send. This array has to be NULL-terminated
 *
 *  Author: Joakim
 */
uint8_t proto_serialSend(int portHandle, uint8_t *data){
    while (*data != '\0') {
        printf("*data is: %d\n", *data);
        write(portHandle, data, 1);
        data++;
    }    

    return 1;
}