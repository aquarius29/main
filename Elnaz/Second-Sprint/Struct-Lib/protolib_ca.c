/*****************************************************************************
* Product: 
* Version: 
* Released: April 7 2011
* Updated: April 12 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

 
 #ifdef PC
   #include <stdio.h>
   #include "protolib_move.h" 
#endif
/***************************************************************************** 
    Definitions 
*****************************************************************************/ 


#include <stdio.h>
#include <string.h>


struct collision_avoid {
	int height; // from Collision Avoidance Movement to; DEFAULT is 0
	int distance ;
	int direction; // from Collision Avoidance Movement to; DEFAULT is 0
      
} collision_avoid;



 
 
//write speed from movement to collision avodance  
void write(struct collision_avoid ca);// proto API 
 
 
//read speed from movement to collision avodance 
struct collision_avoid read();// proto API 
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
 
void write(struct collision_avoid ca){ 
    collision_avoid = ca;
#ifdef PC
	printf("Collision Avoidance value set to: %d , %d , %d\n", ca.height , ca.direction, ca.distance);
#endif
} 
 
 
struct collision_avoid read(){ 
#ifdef PC
	printf("Collision Avoidance  set to: %d , %d ,%d\n", ca.height , ca.direction ,ca.distance);
#endif

    return collision_avoid; 
}


