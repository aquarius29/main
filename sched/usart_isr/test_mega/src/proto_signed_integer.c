/*!
 *  @file proto_serializer.c
 *
 *  @brief Module for serializing signed data to send over serial port
 *
 *  @author     Justin
 *  @date       2011-05-16
 *
 *  @history    2011-05-16 - Created this module - Justin
 *              2011-05-18 - Completed and merged pieces into the proper places.
 *                           This is now deprecated.
 *
 *  @details   will be integrated to the proto_serializer.c
 */


#include <stdint.h>
#include <stdio.h>
#include "proto_serialDefine.h"
#include "proto_msg_structs.h"
#define POSITIVE_OR_NEGATIVE_MASK 0x7FFF
#define HIGHBYTE 0
#define LOWBYTE 1
#define POSORNEG 2


uint8_t lowByte(uint16_t word);
uint8_t highByte(uint16_t word);
//uint16_t proto_deserialize_signed_int(uint8_t *data, uint8_t *serializedData);
void fillData(uint8_t *data, uint16_t intToShift);
//uint16_t proto_deserialize_signed_int(uint8_t *data);
uint16_t two_complement_shifting(uint8_t *data,int16_t intToShift);
int16_t proto_deserialize_signed_int(uint8_t *data);

static uint8_t data[2];
static uint8_t serializedData[NAV_MSG_LEN];



uint8_t main(){
  
  //uint8_t lByte; 
  //int8_t hByte;
  int16_t intToShift = -12003;
  


  printf("Before shift: %d\n", intToShift);
  
  //printf("inverse? = %d\n", intToShift);
  fillData(data,two_complement_shifting(data,intToShift));
  printf("Casted int: %d\n", proto_deserialize_signed_int(data));  
  //printf("Casted int: %d\n", );
  //proto_deserialize_signed_int(data, &dataStruct);

  return 1;

}


//Joakim's
uint8_t lowByte(uint16_t word){
    return (uint8_t)(word &= 0x00FF);   
}

//Joakim's
uint8_t highByte(uint16_t word){
    return (uint8_t)(word >> 8);
}

/* uint16_t proto_deserialize_signed_int(uint8_t *data, struct navData *dataStruct){ */
  
/*   dataStruct->height =  */
/*     (uint16_t)(data[NAV_HEIGHT_INDEX_HIGHBYTE] << 8) |  */
/*         (uint16_t)(data[NAV_HEIGHT_INDEX_LOWBYTE]); */
/*   completelyShiftedInt = dataStruct->height ^ POSITIVE_OR_NEGATIVE_MASK; */
/*   printf("completelyShiftedInt = %d\n", completelyShiftedInt); */
/*   return completelyShiftedInt; */
/* } */

/* int16_t proto_deserialize_signed_int(int8_t *data){ */
  
/*   int16_t shiftedInt =  */
/*     (int16_t)(data[0] << 8) |  */
/*         (int16_t)(data[1]); */
/*   printf("shiftedInt = %d\n", shiftedInt); */
/*   //int16_t completelyShiftedInt = shiftedInt ^ POSITIVE_OR_NEGATIVE_MASK; */
/*   //printf("completelyShiftedInt = %d\n", completelyShiftedInt); */
/*   return shiftedInt; */
/* } */

void fillData(uint8_t *data, uint16_t intToShift){
  data[HIGHBYTE] = (uint8_t)highByte(intToShift);
 printf("high = %d\n", data[HIGHBYTE]);
  data[LOWBYTE] = (uint8_t)lowByte(intToShift);
 printf("low = %d\n", data[LOWBYTE]);
}


uint16_t two_complement_shifting(uint8_t *data, int16_t intToShift){ 
  uint16_t maskTest = intToShift ^ POSITIVE_OR_NEGATIVE_MASK;
  maskTest >>= 15;
  printf("maskTest = %d\n", maskTest); 
  if(maskTest == 0){ 
    data[POSORNEG] = 0;
    return (uint16_t)intToShift; 
     } else { 
    //inverse and add 1
    data[POSORNEG] = 1;
    intToShift = ~intToShift+1;
    printf("inverse? = %d\n", intToShift); 
    return (uint16_t)intToShift;      
  } 
} 


int16_t proto_deserialize_signed_int(uint8_t *data){
  int16_t deserializedSignedInt;  
  uint16_t reconstructerInt =
    (uint16_t) (data[HIGHBYTE] << 8) |
    (uint16_t)(data[LOWBYTE]);
  printf("reconstructer: %d\n", reconstructerInt);
  if(data[POSORNEG] == 0){
    deserializedSignedInt =
      reconstructerInt;
  } else {
    deserializedSignedInt =
      (int16_t)(~reconstructerInt + 1);
    printf("am in here\n");
  }
  printf("reconstructer2: %d\n", reconstructerInt);
  return deserializedSignedInt;
}
