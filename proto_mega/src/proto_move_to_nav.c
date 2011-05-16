/*!
* @file proto_move_to_nav.c
* @brief Messages from Move to Nav
* @author Navid, Pooyan
* @history 
* 			- 2011-05-04 updated by Elnaz
* 			- 2011-05-12 updated by Mihail
*			- 2011-05-13 updated by Elnaz
*/

#ifdef PC
   #include <stdio.h> 
   #include <stdint.h>
#endif

#include <stdlib.h>
#include "proto_lib.h"


uint16_t isca;

struct movCommand * navPtr;

struct movCommand * proto_read_move_to_nav(void){ 
#ifdef PC
	storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, navPtr->type);
	storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, navPtr->order);
	storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, navPtr->height);
	storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, navPtr->distance);
	storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, navPtr->yaw);
	#ifdef DEBUG
		printf("movCommand value set to: %d , %d\n", navPtr->type,
		    navPtr->order, navPtr->height, navPtr->distance, navPtr->yaw);
	#endif
#endif
 	return (struct movCommand *) navPtr;
}



void proto_write_nav_to_move(uint16_t type, uint16_t order, int16_t height,
		uint16_t distance,int16_t yaw){ 
    navPtr->type = type;
    navPtr->order = order;
    navPtr->height = height;
 	navPtr->distance = distance;
    navPtr->yaw = yaw;
#ifdef PC
	storeForTint(PROTO_WRITE, PROTO_NAV, PROTO_UNKNOWN, navPtr->type);
	storeForTint(PROTO_WRITE, PROTO_NAV, PROTO_UNKNOWN, navPtr->order);
	storeForTint(PROTO_WRITE, PROTO_NAV, PROTO_UNKNOWN, navPtr->height);
	storeForTint(PROTO_WRITE, PROTO_NAV, PROTO_UNKNOWN, navPtr->distance);
	storeForTint(PROTO_WRITE, PROTO_NAV, PROTO_UNKNOWN, navPtr->yaw);
	#ifdef DEBUG
		printf("movCommand value set to: %d , %d\n", navPtr->type,
			navPtr->order, navPtr->height,navPtr->distance , navPtr->yaw);
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

void proto_write_move_to_nav(uint16_t move_to_nav){
	isca=move_to_nav;
#ifdef PC
	storeForTint(PROTO_WRITE, PROTO_MOTOR, PROTO_UNKNOWN, move_to_nav);
	#ifdef DEBUG
		printf("move to nav msg value set to: %c\n", move_to_nav);
	#endif
#endif
}


uint16_t proto_read_nav_to_move(void){
	uint16_t temp=isca;
    isca=0;
#ifdef PC
 	storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, temp);
	#ifdef DEBUG
		printf("move to nav msg value set to: %c\n", temp);
	#endif
#endif
	return temp;
}
