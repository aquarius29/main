/*****************************************************************************
* Product: 
* Version: 
* Released: May 04 2011
* Updated: May 11 2011
*
* Copyright (C) 2011 by Navid ,Pooyan
* 
*
* update (C) 2011 by Elnaz Shahmehr
*
* <IT University of Goteborg>
*****************************************************************************/

#ifdef PC
   #include <stdio.h> 
   #include <stdint.h>
#endif

#include <stdlib.h>
#include "proto_lib.h"


uint8_t isca;

struct movCommand * navPtr;



struct movCommand * proto_read_move_to_nav(void){ 
  if (navPtr == NULL){
	createDefaultmove_to_nav();
}	
#ifdef PC
 storeForTint(READ, MOVEMENT, UNKNOWN, navPtr->type);
 storeForTint(READ, MOVEMENT, UNKNOWN, navPtr->order);
 storeForTint(READ, MOVEMENT, UNKNOWN, navPtr->height);
 storeForTint(READ, MOVEMENT, UNKNOWN, navPtr->distance);
 storeForTint(READ, MOVEMENT, UNKNOWN, navPtr->yaw);

	#ifdef DEBUG
	printf("movCommand value set to: %d , %d\n", navPtr.type , navPtr.order,navPtr.height,navPtr.distance,navPtr.yaw);
  #endif
#endif
  return (struct movCommand *) navPtr;
}



void proto_write_nav_to_move(uint8_t type,uint8_t order,int16_t height,uint16_t distance,int16_t yaw){ 
	if (navPtr == NULL)
	navPtr = (struct movCommand *) malloc(sizeof(struct movCommand));
        navPtr->type = type;
        navPtr->order = order;
        navPtr->height = height;
 	navPtr->distance = distance;
        navPtr->yaw = yaw;
   
#ifdef PC
 storeForTint(WRITE, NAV, UNKNOWN, navPtr->type);
 storeForTint(WRITE, NAV, UNKNOWN, navPtr->order);
 storeForTint(WRITE, NAV, UNKNOWN, navPtr->height);
 storeForTint(WRITE, NAV, UNKNOWN, navPtr->distance);
 storeForTint(WRITE, NAV, UNKNOWN, navPtr->yaw);


	#ifdef DEBUG
	printf("movCommand value set to: %d , %d\n",navPtr.type , navPtr.order,navPtr.height,navPtr.distance , navPtr.yaw);
  #endif
#endif
} 

void createDefaultmove_to_nav(){
	navPtr = (struct movCommand *) malloc(sizeof(struct movCommand));
	navPtr->type = 0;
	navPtr->order = 0;
	navPtr->height = 0;
	navPtr->distance = 0;
	navPtr->yaw = 0;	     
}


void proto_write_move_to_nav(uint8_t move_to_nav){
	isca=move_to_nav;
#ifdef PC
	 storeForTint(WRITE, MOTOR, UNKNOWN, move_to_nav);
#ifdef DEBUG
	printf("move to nav msg value set to: %c\n", move_to_nav);
#endif
#endif
}


uint8_t proto_read_nav_to_move(void){
	uint8_t temp=isca;
           isca=0;
#ifdef PC
 	storeForTint(READ, MOVEMENT, UNKNOWN, temp);
#ifdef DEBUG
	printf("move to nav msg value set to: %c\n", temp);
#endif
#endif
	return temp;
}
