
/*!
 *  @file proto_srial_port.h
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

#ifndef PROTO_SERIAL_PORT_H
#define PROTO_SERIAL_PORT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define PROTO_SERIAL_PORT "/dev/tty.usbmodemfa141"

int32_t proto_serialOpen(void);
uint8_t proto_serialClose(int32_t);

#endif /* PROTO_SERIAL_PORT_H */