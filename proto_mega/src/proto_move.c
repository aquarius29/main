/*****************************************************************************
* Product: 
* Version: 
* Released: April 8 2011
* Updated: April 27 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* <IT University of Goteborg>
*****************************************************************************/
#ifdef PC
   #include <stdio.h>
   #include "proto_move.h" 
   #include "proto_tint.h"
#endif
/***************************************************************************** 
    Definitions 
*****************************************************************************/ 
 
unsigned int speed = 0; // from Movement to Collision Avoidance; DEFAULT is 0
unsigned int direction; 
 
 
//write speed from movement to collision avodance  
void proto_write_speed(int value);// proto API 
 
 
//read speed from movement to collision avodance 
unsigned int proto_read_speed(void);// proto API 
 

//write direction from movement to collision avodance  
void proto_write_direction(int value);// proto API 
 
 
//read direction from movement to collision avodance  
unsigned int proto_read_direction(void);// proto API 
 
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
 
void proto_write_speed(int value){ 
    speed = value;
#ifdef PC
	storeForTint(WRITE, MOVEMENT, UNKNOWN, speed);
	#ifdef DEBUG
		printf("Movement value set to: %c\n", speed);
	#endif
#endif
} 
 
 
unsigned int proto_read_speed(void){ 
#ifdef PC
	storeForTint(READ, COLLISION, UNKNOWN, speed);
	#ifdef DEBUG
		printf("Movement value is: %c\n", speed);
	#endif
#endif

    return speed; 
} 


void proto_write_direction(int value){ 
    direction = value;
#ifdef PC
	printf("Movement value set to: %c\n", direction);
#endif
 
} 
 
 
unsigned int proto_read_direction(void){ 
#ifdef PC
	printf("Movement value is: %c\n", direction);
#endif
    return direction; 
}



