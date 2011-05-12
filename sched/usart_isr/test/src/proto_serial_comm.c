
/*!
 *  @file proto_srial_comm.c
 *  
 *  @brief Module for sending data on the serial port
 *
 *  @author     Joakim
 *  @date       2011-05-06
 *
 *  @history    2011-05-06 - Created this module - Joakim
 *              2011-05-12 - Added specific function for sending navigation
 *                           data which in turn uses the serialSend function.
 *                           Previous code versions made the user serialize
 *                           the data first, this is now done 
 *                           automatically. - Joakim
 *
 *  @details
 */
 
#include <stdio.h> 

#include "proto_serial_comm.h"
#include "proto_serializer.h"

static uint8_t proto_serialSend(int32_t portHandle, uint8_t *data);

/*
 *  Function to send navigation data message on serial port
 *  
 *  Takes a port handle to write to (serial port) and a navData struct
 *  containing the data to send.
 *
 *  Author: Joakim
 */
uint8_t proto_serialSendNavMsg(int32_t portHandle, struct navData *data){
    uint8_t serialData[NAV_MSG_LEN];

    proto_serializeNavMsg(data, serialData);
    proto_serialSend(portHandle, serialData);
    
    return 1;
}

/*
 *  Function for sending serial data on serial port
 *  
 *  Takes a port handle to write to (serial port) and a byte array
 *  to send. This array has to be NULL-terminated. The NULL terminator
 *  should be added by the serializer when converting data into an array.
 *
 *  Author: Joakim
 */
static uint8_t proto_serialSend(int32_t portHandle, uint8_t *data){
    while (*data != '\0') {
        write(portHandle, data, 1);
        data++;
    }    

    return 1;
}

