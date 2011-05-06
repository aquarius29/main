
/*!
 *  @file proto_serializer.c
 *
 *  @brief Module for serializing data to send over serial port
 *
 *  @author     Joakim
 *  @date       2011-05-06
 *
 *  @history    2011-05-06 - Created this module - Joakim
 *
 *  @details
 */

#include <stdint.h>
#include <stdio.h>

#include "proto_serializer.h"

static uint8_t lowByte(uint16_t);
static uint8_t highByte(uint16_t);

/*
 *  signed data types has to be handled properly!
 *
 */
uint8_t proto_serializeData(struct status *data, uint8_t *serializedData){
    uint8_t i;

    serializedData[0] = data->uInt8;
    serializedData[1] = data->int8;
    serializedData[2] = lowByte(data->uInt8);
    serializedData[3] = highByte(data->uInt8);
    
    printf("data->uInt8 = %d\n", data->uInt8);
    
    printf("data->uInt16 = %d\n", data->uInt16);
    printf("low byte of data->uInt16 = %d\n", lowByte(data->uInt16));
    printf("high byte of data->uInt16 = %d\n", highByte(data->uInt16));
    
    uint16_t word;
    uint8_t lByte = lowByte(data->uInt16);
    uint8_t hByte = highByte(data->uInt16);
    word = (uint16_t)(hByte << 8) | (uint16_t)(lByte);
    
    printf("Both put together = %d\n\n", word);



    printf("data->int16 = %d\n", data->int16);
    printf("low byte of data->int16 = %d\n", lowByte(data->int16));
    printf("high byte of data->int16 = %d\n", highByte(data->int16));
    
    lByte = lowByte(data->int16);
    hByte = highByte(data->int16);
    word = (uint16_t)(hByte << 8) | (uint16_t)(lByte);
    
    printf("Both put together = %d\n", word);
    
}

uint8_t lowByte(uint16_t word){
    return (uint8_t)(word &= 0x0F);   
}

uint8_t highByte(uint16_t word){
    return (uint8_t)(word >> 8);
}

