
#ifndef PROTO_DESERIALIZER_H
#define PROTO_DESERIALIZER_H

#include <stdint.h>
#include "proto_msg_structs.h"
#include "proto_serial_define.h"

uint8_t proto_reConstructMsgUICommand(uint8_t *serialData, 
                                        uint8_t *uiCommand);
                                        
uint8_t proto_reConstructMsgNav(uint8_t *serialData, struct navData *dataStruct);

uint8_t proto_reConstructMovConfirmMsg(uint8_t *serialData, uint8_t *target);

int16_t proto_deserialize_signed_int(uint8_t *serialData, uint8_t type);

#endif /* PROTO_DESERIALIZER_H */
