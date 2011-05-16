
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

#ifdef ARDUINO

#include "WProgram.h"

#endif /* ARDUINO */
 
#include <stdio.h> 

#include "proto_serial_comm.h"
#include "proto_serializer.h"
#include "proto_stub.h"
#include "proto_serial_define.h"
#include "proto_usart_isr_mega.h"

#define TRUE 1
#define FALSE 0

static uint8_t dataBuffer[PROTO_MAX_MSG_LEN];


#ifdef PC

static uint8_t proto_serialSendToMega(int32_t portHandle, uint8_t *data);

#endif /* PC */

#ifdef ARDUINO

static uint8_t proto_serialSendToPanda(uint8_t *data);

#endif /* ARDUINO */


#ifdef PC

uint8_t *proto_readMovConfirmMsg(int32_t portHandle){
    /* return the specific confirm message from movement */
    uint8_t *serialData;
    
    serialData = proto_serialReceiveFromMega(portHandle);
    
    return serialData;
    
    //returnMsg = a port read function
    //proto_serialReceiveFromMega(portHandle, serialData);
    
    //return returnMsg;
}

uint8_t *proto_serialReceiveFromMega(int32_t portHandle){
    uint8_t byte;
    uint8_t i = 0;
    uint8_t done = FALSE;
    uint8_t msgLength = 0;
    
    do {
        // if (read(portHandle, dataBuffer, sizeof(dataBuffer)) == 0) {
        //     done = TRUE;
        //     printf("return value of read was zero\n");
        // }
        // else {    
        //     printf("databuffer[%d] = %d\n", i, dataBuffer[i]);
        //     msgLength = dataBuffer[0];
        //     printf("message length: %d\n", msgLength);
        // 
        //     i++;
        // 
        //     if (i >= msgLength || i == sizeof(dataBuffer)) {
        //         done = TRUE;
        //     }
        // }
        read(portHandle, &dataBuffer[i], 1);
        printf("i is %d, dataBuffer[%d] is %d\n", i, i, dataBuffer[i]);
        if (i == 0) {
            msgLength = dataBuffer[0];
        }
        i++;
        if (i >= msgLength) {
            done = TRUE;
        }
    } while (done != TRUE);
    
    return dataBuffer;
}

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
    uint8_t serialData[MOV_CONFIRM_MSG_LEN];
    
    proto_serializeMovConfirmMsg(msg, serialData);
    
    // if (serialData[2] == 101) {
    //     digitalWrite(12, HIGH);
    // }
    
    proto_serialSendToPanda(serialData);
 
    return 1;
}

static uint8_t proto_serialSendToPanda(uint8_t *data){
    // if (data[0] == 3) {
    //     digitalWrite(12, HIGH);
    // }
    
    /* call the usart_isr_mega code here to send data over Tx 
     * This should be changed to instead notifying the proto_run code
     * that a message needs to be sent and then let that code send it
     * when proto is scheduled
    */
    proto_usartTransmit(data);
    
    return 1;
}

#endif /* ARDUINO */

