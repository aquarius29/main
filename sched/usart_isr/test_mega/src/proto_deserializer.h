
#ifndef PROTO_DESERIALIZER_H
#define PROTO_DESERIALIZER_H

#include <stdint.h>
#include "proto_msg_structs.h"

uint8_t proto_reConstructMsgUICommand(uint8_t *serialData, 
                                        uint8_t *uiCommand);
                                        
uint8_t proto_reConstructMsgNav(uint8_t *data, struct navData *dataStruct);

uint8_t proto_reConstructMovConfirmMsg(uint8_t *serialData, uint8_t *target);

#endif /* PROTO_DESERIALIZER_H */
