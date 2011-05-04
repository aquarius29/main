/*****************************************************************************
* Product: 
* Version: 
* Released: April 7 2011
* Updated: April 27 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/
#ifdef PC
   #include <stdio.h>
   #include "proto_lib.h" 
#endif
/***************************************************************************** 
    Definitions 
*****************************************************************************/ 
 
//unsigned int height = 0; // from Collision Avoidance Movement to; DEFAULT is 0

unsigned int direction_ca = 0; // from Collision Avoidance Movement to; DEFAULT is 0
 
//write direction from movement to collision avodance  
void proto_write_direction_ca(int value);// proto API 

 
//read direction from movement to collision avodance  
unsigned int proto_read_direction_ca(void);// proto API 
 
//write distance from movement to collision avodance  
//void proto_write_distance(int value);// proto API 

 
//read distance from movement to collision avodance  
//unsigned int proto_read_distance(void);// proto API 
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 

void proto_write_direction_ca(int value){ 
    direction_ca = value;
#ifdef PC
	storeForTint(WRITE, COLLISION, UNKNOWN, value);
	#ifdef DEBUG
	printf("collision avodance value set to: %c\n", direction_ca);
	#endif
#endif
 
} 
 
 
unsigned int proto_read_direction_ca(void){ 
#ifdef PC
	storeForTint(READ, MOVEMENT, UNKNOWN, direction_ca);
	#ifdef DEBUG
	printf("collision avodance value is: %c\n", direction_ca);
	#endif
#endif
    return direction_ca; 
}

/*
void proto_write_distance(int value){ 
    distance = value;
#ifdef PC
	printf("collision avodance value set to: %c\n", distance);
#endif
 
} 
 
unsigned int proto_read_distance(void){ 
#ifdef PC
	printf("collision avodance value is: %c\n", distance);
#endif
    return distance; 
}

*/
