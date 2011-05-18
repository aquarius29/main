
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

#include "proto_serial_define.h"
#include "proto_msg_structs.h"
#include "proto_serializer.h"

static uint8_t positive_or_negative;
static uint16_t convertingInt;
static uint8_t lowByte(uint16_t);
static uint8_t highByte(uint16_t);

/*
 *
 */
uint8_t proto_serializeUICommandMsg(uint8_t command, 
                                    uint8_t *serializedData){
    serializedData[LEN_INDEX] = UI_COMMAND_MSG_LEN;
    serializedData[ID_INDEX] = MSG_ID_UI_COMMAND;
    serializedData[UI_COMMAND_VAL_INDEX] = command;
    serializedData[UI_COMMAND_NULL_INDEX] = '\0';

    return 1;
}

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
    convertingInt = proto_two_complement_shifting(data->height);
    serializedData[NAV_HEIGHT_INDEX_LOWBYTE] = lowByte(convertingInt);
    serializedData[NAV_HEIGHT_INDEX_HIGHBYTE] = highByte(convertingInt);
    serializedData[NAV_HEIGHT_INDEX_POSORNEG] = positive_or_negative;
    serializedData[NAV_DISTANCE_INDEX_LOWBYTE] = lowByte(data->distance);
    serializedData[NAV_DISTANCE_INDEX_HIGHBYTE] = highByte(data->distance);
    convertingInt = proto_two_complement_shifting(data->yaw);
    serializedData[NAV_YAW_INDEX_LOWBYTE] = lowByte(convertingInt);
    serializedData[NAV_YAW_INDEX_HIGHBYTE] = highByte(convertingInt);
    serializedData[NAV_YAW_INDEX_POSORNEG] = positive_or_negative;
    serializedData[NAV_NULL_INDEX] = '\0';

    return 1;
}


// inverse negative and add 1 for unsigned transfer. 0 is positive. - Justin
uint16_t proto_two_complement_shifting(int16_t intToShift){ 
  uint16_t maskTest = intToShift ^ POSITIVE_OR_NEGATIVE_MASK;
  maskTest >>= 15;
  //printf("maskTest = %d\n", maskTest); 
  if(maskTest == 0){  
    positive_or_negative = 0;
    return (uint16_t)intToShift; 
     } else { 
    positive_or_negative = 1;
    intToShift = ~intToShift+1;
    //printf("inverse? = %d\n", intToShift); 
    return (uint16_t)intToShift;      
  } 
} 


uint8_t lowByte(uint16_t word){
    return (uint8_t)(word &= 0x00FF);   
}

uint8_t highByte(uint16_t word){
    return (uint8_t)(word >> 8);
}

