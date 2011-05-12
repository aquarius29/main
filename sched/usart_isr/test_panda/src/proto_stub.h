
/*!
 *  @brief Stub code for a protocol interface
 *
 *  @author Joakim
 *
 *  @history    2011-05-10 - Started this module - Joakim
 */

#ifndef PROTO_STUB_H
#define PROTO_STUB_H
 
#include <stdint.h>
#include "proto_msg_structs.h" 
 
uint8_t proto_init(void);
uint8_t proto_run(void);
uint8_t proto_isNewNavMsg(void);
struct navData *proto_readNavMsg(void);

#endif /* PROTO_STUB_H */