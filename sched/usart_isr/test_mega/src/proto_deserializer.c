
#include "proto_deserializer.h"
#include "proto_msg_structs.h"

uint8_t proto_reConstructMsgNav(uint8_t *data, struct navData *dataStruct){
    dataStruct->type = data[NAV_TYPE_INDEX];
    dataStruct->order = data[NAV_ORDER_INDEX];
    
    dataStruct->height = 
        (uint16_t)(data[NAV_HEIGHT_INDEX_HIGHBYTE] << 8) | 
        (uint16_t)(data[NAV_HEIGHT_INDEX_LOWBYTE]);
    
    dataStruct->distance = 
        (uint16_t)(data[NAV_DISTANCE_INDEX_HIGHBYTE] << 8) | 
        (uint16_t)(data[NAV_DISTANCE_INDEX_LOWBYTE]);
    
    dataStruct->yaw = 
        (uint16_t)(data[NAV_YAW_INDEX_HIGHBYTE] << 8) | 
        (uint16_t)(data[NAV_YAW_INDEX_LOWBYTE]);
                    
    return 1;
}

// uint8_t proto_reConstructMsgNav(uint8_t *data, void *dataStruct){
//     ((struct navData *)dataStruct)->type = data[NAV_TYPE_INDEX];
//     ((struct navData *)dataStruct)->order = data[NAV_ORDER_INDEX];
//     
//     ((struct navData *)dataStruct)->height = 
//         (uint16_t)(data[NAV_HEIGHT_INDEX_HIGHBYTE] << 8) | 
//         (uint16_t)(data[NAV_HEIGHT_INDEX_LOWBYTE]);
//     
//     ((struct navData *)dataStruct)->distance = 
//         (uint16_t)(data[NAV_DISTANCE_INDEX_HIGHBYTE] << 8) | 
//         (uint16_t)(data[NAV_DISTANCE_INDEX_LOWBYTE]);
//     
//     ((struct navData *)dataStruct)->yaw = 
//         (uint16_t)(data[NAV_YAW_INDEX_HIGHBYTE] << 8) | 
//         (uint16_t)(data[NAV_YAW_INDEX_LOWBYTE]);
//                     
//     return 1;
// }
