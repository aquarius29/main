
/*!
 *  @file proto_serializer.c
 *
 *  @brief Module for serializing data to send over serial port
 *
 *  @author     Joakim, Justin
 *  @date       2011-05-06
 *
 *  @history    2011-05-06 - Created this module - Joakim
 *
 *  @details
 */

#include "proto_serial_define.h"
#include "proto_deserializer.h"
#include "proto_msg_structs.h"

uint8_t proto_reConstructMsgNav(uint8_t *serialData, struct navData *dataStruct){
    dataStruct->type = serialData[NAV_TYPE_INDEX];
    dataStruct->order = serialData[NAV_ORDER_INDEX];
    
    dataStruct->height = 
        (uint16_t)(serialData[NAV_HEIGHT_INDEX_HIGHBYTE] << 8) | 
        (uint16_t)(serialData[NAV_HEIGHT_INDEX_LOWBYTE]);
    
    dataStruct->distance = 
        (uint16_t)(serialData[NAV_DISTANCE_INDEX_HIGHBYTE] << 8) | 
        (uint16_t)(serialData[NAV_DISTANCE_INDEX_LOWBYTE]);
    
    dataStruct->yaw = 
        (uint16_t)(serialData[NAV_YAW_INDEX_HIGHBYTE] << 8) | 
        (uint16_t)(serialData[NAV_YAW_INDEX_LOWBYTE]);
                    
    return 1;
}

uint8_t proto_reConstructMovConfirmMsg(uint8_t *serialData, uint8_t *target){
    *target = serialData[MOV_CONFIRM_VAL_INDEX];
 
    return 1;
} 