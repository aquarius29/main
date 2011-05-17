
/*!
 *  @file proto_srial_comm.h
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
 *                           the data first, this is now done automatically.
 *              2011-05-12 - Added the functions for reading navigations
 *                           message and sending movements confirmation
 *                           message. - Joakim
 *
 *  @details
 */
 

#ifndef PROTO_SERIAL_COMM_H
#define PROTO_SERIAL_COMM_H

#include <stdint.h>
#include "proto_msg_structs.h"

/*
 *  proto_serialSendNavMsg
 *
 *  Function to send navigation data message on serial port
 *  
 *  Takes a port handle to write to (serial port) and a navData struct
 *  containing the data to send. 
 *
 *  Author: Joakim
 */ 
uint8_t proto_serialSendNavMsg(int32_t portHandle, struct navData *data);

/*
 *  proto_serialSendMovConfirmMsg
 *
 *  Function to send movements confirmation message to navigation
 *
 *  Takes an unsigned byte as message
 *
 *  Author: Joakim
 */
uint8_t proto_serialSendMovConfirmMsg(uint8_t msg);

/*
 *  proto_serialReadNavMsg
 *
 *  Function to read navigations message to movement
 *
 *  Returns: a pointer to the structure that holds the message
 *
 *  Author: Joakim
 */
struct navData *proto_serialReadNavMsg(void);

uint8_t proto_readMovConfirmMsg(int32_t portHandle, uint8_t *targetStorage);


#endif /* PROTO_SERIAL_COMM_H */