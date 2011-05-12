
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

#endif /* PROTO_SERIAL_COMM_H */