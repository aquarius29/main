
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

#include "WProgram.h"
 
#include <stdio.h> 

#include "proto_serial_comm.h"
#include "proto_serializer.h"
#include "proto_stub.h"

#define TRUE 1
#define FALSE 0

#ifdef PC

static uint8_t proto_serialSendToMega(int32_t portHandle, uint8_t *data);

#endif /* PC */

#ifdef ARDUINO

static uint8_t proto_serialSendToPanda(uint8_t *data);

#endif /* ARDUINO */


#ifdef PC

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
    proto_serialSendToMega(portHandle, serialData);
    
    return 1;
}

/*****************************************
 *  proto_serialReadMovMsg goes here
 ****************************************/

/*
 *  Function for sending serial data on serial port
 *  
 *  Takes a port handle to write to (serial port) and a byte array
 *  to send. This array has to be NULL-terminated. The NULL terminator
 *  should be added by the serializer when converting data into an array.
 *
 *  Author: Joakim
 */
static uint8_t proto_serialSendToMega(int32_t portHandle, uint8_t *data){
    while (*data != '\0') {
        write(portHandle, data, 1);
        data++;
    }    

    return 1;
}

#endif /* PC */

#ifdef ARDUINO

struct navData *proto_serialReadNavMsg(void){
    struct navData *navMsg = NULL;

    if (proto_isNewNavMsg() == TRUE) {
        navMsg = proto_readNavMsg();
        return navMsg;
    }
    else {
        return NULL;
    }
}

uint8_t proto_serialSendMovConfirmMsg(uint8_t msg){
    uint8_t serialData[NAV_MSG_LEN];
    
    proto_serializeMovConfirmMsg(msg, serialData);
    proto_serialSendToPanda(serialData);
 
    return 1;
}

static uint8_t proto_serialSendToPanda(uint8_t *data){
    
    
    return 1;
}

#endif /* ARDUINO */

