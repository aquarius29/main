
/*!
 *  @file       proto_srial_comm.c
 *  
 *  @brief      Interface module for sending and receiving messages on the \n
 *              serial port. 
 *
 *  @author     Joakim
 *  @date       2011-05-17
 *
 *  @history    2011-05-06 - Created this module - Joakim \n
 *              2011-05-12 - Added specific function for sending navigation \n
 *                           data which in turn uses the serialSend \n
 *                           function. Previous code versions made the user \n 
 *                           serialize the data first, this is now done \n
 *                           automatically. - Joakim \n
 *              2011-05-17 - Added more functions for receiving and sending \n
 *                           specific messages. Changed interface functions \n
 *                           to take a pointer to the data storage where \n
 *                           the message will be stored by the caller. \n
 *                           This is to reduce the need of having \n
 *                           proto-code responsible for keeping groups data \n
 *                           in scope and available. - Joakim \n
 *
 *  @details    Module should be used as the interface to send and receive \n
 *              messages on the serial port by both the Panda/Pc and \n
 *              Arduino systems. For the Panda/Pc side the actual sending \n
 *              and receiving is done here. The same functionality for \n
 *              the Arduino side is more hardware related and is done \n
 *              in seperate modules that gets called from here. \n
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

static uint8_t dataBuffer[PROTO_MAX_MSG_LEN];

/* PC specific static function prototypes */
#ifdef PC

static uint8_t proto_serialSendToMega(int32_t portHandle, uint8_t *data);
static uint8_t *proto_serialReceiveFromMega(int32_t portHandle);

#endif /* PC */

/* Arduino specific static function prototypes */
#ifdef ARDUINO

static uint8_t proto_serialSendToPanda(uint8_t *data);

#endif /* ARDUINO */

/* PC specific function implementations ********************************** */
#ifdef PC

uint8_t proto_serialSendUICommandMsg(uint32_t portHandle, uint8_t command){
    uint8_t serialData[UI_COMMAND_MSG_LEN];
    
    proto_serializeUICommandMsg(command, serialData);
    proto_serialSendToMega(portHandle, serialData);
 
    return 1;
}

/*!
 *  Function to send navigation data message on serial port
 *  
 *  Takes a port handle to write to (serial port) and a navData struct
 *  containing the data to send.
 *
 *  @author Joakim
 */
uint8_t proto_serialSendNavMsg(int32_t portHandle, struct navData *data){
    uint8_t serialData[NAV_MSG_LEN];

    proto_serializeNavMsg(data, serialData);
    proto_serialSendToMega(portHandle, serialData);
    
    return 1;
}

uint8_t proto_serialReadMovConfirmMsg(int32_t portHandle, 
                                        uint8_t *targetStorage){
    uint8_t *serialData;
    
    serialData = proto_serialReceiveFromMega(portHandle);
    proto_reConstructMovConfirmMsg(serialData, targetStorage);
    
    return 1;
}

static uint8_t *proto_serialReceiveFromMega(int32_t portHandle){
    uint8_t byte;
    uint8_t i = 0;
    uint8_t done = FALSE;
    uint8_t msgLength = 0;
    
    do {
        read(portHandle, &dataBuffer[i], 1);
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

/*!
 *  Function for sending serial data on serial port
 *  
 *  Takes a port handle to write to (serial port) and a byte array
 *  to send. This array has to be NULL-terminated. The NULL terminator
 *  should be added by the serializer when converting data into an array.
 *
 *  @author Joakim
 */
static uint8_t proto_serialSendToMega(int32_t portHandle, uint8_t *data){
    while (*data != '\0') {
        write(portHandle, data, 1);
        data++;
    }    

    return 1;
}

#endif /* PC */

/* ARDUINO specific function implementations ***************************** */
#ifdef ARDUINO

uint8_t proto_serialReadUICommandMsg(void){
    uint8_t uiCommand = 0;
    
    if (proto_isNewUICommandMsg() == TRUE) {
        uiCommand = proto_readUICommandMsg();
        return uiCommand;
    }
    else {
        return 0;
    }
}

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
    proto_serialSendToPanda(serialData);
 
    return 1;
}

static uint8_t proto_serialSendToPanda(uint8_t *serialData){
    /* 
     * call the usart_isr_mega code here to send data over Tx 
     * This should be changed to instead notifying the proto_run code
     * that a message needs to be sent and then let that code send it
     * when proto is scheduled
    */
    proto_usartTransmit(serialData);
    
    return 1;
}

#endif /* ARDUINO */

