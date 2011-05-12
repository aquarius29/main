
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

#include <stdint.h>
#include <stdio.h>

#include "proto_serializer.h"
#include "proto_deserializer.h"

static uint8_t lowByte(uint16_t);
static uint8_t highByte(uint16_t);

/*
 *
 */
uint8_t proto_serializeMovConfirmMsg(uint8_t data, uint8_t *serializedData){
    serializedData[LEN_INDEX] = MOV_CONFIRM_MSG_LEN;
    serializedData[ID_INDEX] = MSG_ID_MOV_CONFIRM;
    serializedData[MOV_CONFIRM_VAL_INDEX] = data;
    serializedData[MOV_CONFIRM_NULL_INDEX] = '\0';
 
    return 1;
}

/*
 *
 */
uint8_t proto_serializeNavMsg(struct navData *data, uint8_t *serializedData){
    serializedData[LEN_INDEX] = NAV_MSG_LEN;
    serializedData[ID_INDEX] = MSG_ID_NAV;
    serializedData[NAV_TYPE_INDEX] = data->type;
    serializedData[NAV_ORDER_INDEX] = data->order;
    serializedData[NAV_HEIGHT_INDEX_LOWBYTE] = lowByte(data->height);
    serializedData[NAV_HEIGHT_INDEX_HIGHBYTE] = highByte(data->height);
    serializedData[NAV_DISTANCE_INDEX_LOWBYTE] = lowByte(data->distance);
    serializedData[NAV_DISTANCE_INDEX_HIGHBYTE] = highByte(data->distance);
    serializedData[NAV_YAW_INDEX_LOWBYTE] = lowByte(data->yaw);
    serializedData[NAV_YAW_INDEX_HIGHBYTE] = highByte(data->yaw);
    serializedData[NAV_NULL_INDEX] = '\0';

    return 1;
}

uint8_t lowByte(uint16_t word){
    return (uint8_t)(word &= 0x0F);   
}

uint8_t highByte(uint16_t word){
    return (uint8_t)(word >> 8);
}

