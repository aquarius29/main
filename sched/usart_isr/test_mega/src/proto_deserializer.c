
/*!
 *  @file proto_deserializer.c
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

//static int16_t proto_deserialize_height(uint8_t *serialData);
//static int16_t proto_deserialize_yaw(uint8_t *serialData);

uint8_t proto_reConstructMsgUICommand(uint8_t *serialData, uint8_t *uiCommand){
  *uiCommand = serialData[UI_COMMAND_VAL_INDEX];
    
    return 1;
}

uint8_t proto_reConstructMsgNav(uint8_t *serialData, 
                                struct navData *dataStruct){
  dataStruct->type = serialData[NAV_TYPE_INDEX];
  dataStruct->order = serialData[NAV_ORDER_INDEX];
  
  dataStruct->height = 
    //(uint16_t)(serialData[NAV_HEIGHT_INDEX_HIGHBYTE] << 8) | 
    //(uint16_t)(serialData[NAV_HEIGHT_INDEX_LOWBYTE]);
    proto_deserialize_signed_int(serialData, HEIGHT);
  
  dataStruct->distance = 
    (uint16_t)(serialData[NAV_DISTANCE_INDEX_HIGHBYTE] << 8) | 
    (uint16_t)(serialData[NAV_DISTANCE_INDEX_LOWBYTE]);
  
  dataStruct->yaw = 
    //(uint16_t)(serialData[NAV_YAW_INDEX_HIGHBYTE] << 8) | 
    //(uint16_t)(serialData[NAV_YAW_INDEX_LOWBYTE]);
    proto_deserialize_signed_int(serialData, YAW);          
  
  return 1;
}

uint8_t proto_reConstructMovConfirmMsg(uint8_t *serialData, uint8_t *target){
    *target = serialData[MOV_CONFIRM_VAL_INDEX];
 
    return 1;
}
 
/* static int16_t proto_deserialize_height(uint8_t *serialData){ */
/*   int16_t deserializedSignedInt; */
/*   uint16_t reconstructerInt = */
/*     (uint16_t) (serialData[NAV_HEIGHT_INDEX_HIGHBYTE] << 8) | */
/*     (uint16_t)(serialData[NAV_HEIGHT_INDEX_LOWBYTE]); */
/*   //printf("reconstructer: %d\n", reconstructerInt); */
/*   if(serialData[NAV_HEIGHT_INDEX_POSORNEG] == 0){ */
/*     deserializedSignedInt = */
/*       reconstructerInt; */
/*   } else { */
/*     deserializedSignedInt = */
/*       (int16_t)(~reconstructerInt + 1); */
/*   } */
/*   //printf("reconstructer2: %d\n", reconstructerInt); */
/*   return deserializedSignedInt; */
/* } */

/* static int16_t proto_deserialize_yaw(uint8_t *serialData){  */
/*   int16_t deserializedSignedInt; */
/*   uint16_t reconstructerInt = */
/*       (uint16_t) (serialData[NAV_YAW_INDEX_HIGHBYTE] << 8) | */
/*       (uint16_t)(serialData[NAV_YAW_INDEX_LOWBYTE]); */
/*     //printf("reconstructer: %d\n", reconstructerInt); */
/*     if(serialData[NAV_YAW_INDEX_POSORNEG] == 0){ */
/*       deserializedSignedInt = */
/* 	reconstructerInt; */
/*     } else { */
/*       deserializedSignedInt = */
/* 	(int16_t)(~reconstructerInt + 1); */
/*     } */
/*     //printf("reconstructer2: %d\n", reconstructerInt); */
/*   } */
/*   return deserializedSignedInt; */
/* } */

int16_t proto_deserialize_signed_int(uint8_t *serialData, uint8_t type){
  int16_t deserializedSignedInt;
  uint16_t reconstructerInt;

  switch(type)
    {
    case HEIGHT :
      reconstructerInt =
	(uint16_t) (serialData[NAV_HEIGHT_INDEX_HIGHBYTE] << 8) |
	(uint16_t)(serialData[NAV_HEIGHT_INDEX_LOWBYTE]);
      //printf("reconstructer: %d\n", reconstructerInt);
      if(serialData[NAV_HEIGHT_INDEX_POSORNEG] == 0){
	deserializedSignedInt =
	  reconstructerInt;
      } else {
	deserializedSignedInt =
	  (int16_t)(~reconstructerInt + 1);
      }
      //printf("reconstructer2: %d\n", reconstructerInt);
      return deserializedSignedInt;
      break;
    
    case YAW :   
      reconstructerInt =
	(uint16_t) (serialData[NAV_YAW_INDEX_HIGHBYTE] << 8) |
	(uint16_t)(serialData[NAV_YAW_INDEX_LOWBYTE]);
      //printf("reconstructer: %d\n", reconstructerInt);
      if(serialData[NAV_YAW_INDEX_POSORNEG] == 0){
	deserializedSignedInt =
	  reconstructerInt;
      } else {
	deserializedSignedInt =
	  (int16_t)(~reconstructerInt + 1);
      }
      //printf("reconstructer2: %d\n", reconstructerInt);
      return deserializedSignedInt;
      break;
      
    default:
      return 0;
    }
}

