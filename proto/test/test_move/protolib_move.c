/*****************************************************************************
* Product: 
* Version: 
* Released: April 8 2011
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
 
unsigned int speed = 300; // from Movement to Collision Avoidance; DEFAULT is 0
unsigned int direction = 250; 
 
 
//write speed from movement to collision avodance  
void write_speed(int value);// proto API 
 
 
//read speed from movement to collision avodance 
unsigned int read_speed(void);// proto API 
 

//write direction from movement to collision avodance  
void write_direction(int value);// proto API 
 
 
//read direction from movement to collision avodance  
unsigned int read_direction(void);// proto API 
 
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
 
void write_speed(int value){ 
    speed = value;
#ifdef PC
	printf("Movement value set to: %c\n", speed);
#endif
} 
 
 
unsigned int read_speed(void){ 
#ifdef PC
	printf("Movement value is: %c\n", speed);
#endif

    return speed; 
} 


void write_direction(int value){ 
    direction = value;
#ifdef PC
	printf("Movement value set to: %c\n", direction);
#endif
 
} 
 
 
unsigned int read_direction(void){ 
#ifdef PC
	printf("Movement value is: %c\n", direction);
#endif
    return direction; 
}



