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
   #include "proto_move.h" 
#endif
/***************************************************************************** 
    Definitions 
*****************************************************************************/ 
 
unsigned int height = 0; // from Collision Avoidance Movement to; DEFAULT is 0
unsigned int distance ;
unsigned int direction = 0; // from Collision Avoidance Movement to; DEFAULT is 0
 
 
//write height from movement to collision avodance  
void write_height(int value);// proto API 
 
 
//read height from movement to collision avodance 
unsigned int read_height(void);// proto API 
 

//write direction from movement to collision avodance  
void write_direction(int value);// proto API 

 
//read direction from movement to collision avodance  
unsigned int read_direction(void);// proto API 
 
//write distance from movement to collision avodance  
void write_distance(int value);// proto API 

 
//read distance from movement to collision avodance  
unsigned int read_distance(void);// proto API 
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
 
void write_height(int value){ 
    height = value;
#ifdef PC
	printf("collision avodance value set to: %c\n", height);
#endif
} 
 
 
unsigned int read_height(void){ 
#ifdef PC
	printf("collision avodance value is: %c\n", height);
#endif

    return height; 
} 


void write_direction(int value){ 
    direction = value;
#ifdef PC
	printf("collision avodance value set to: %c\n", direction);
#endif
 
} 
 
 
unsigned int read_direction(void){ 
#ifdef PC
	printf("collision avodance value is: %c\n", direction);
#endif
    return direction; 
}

void write_distance(int value){ 
    distance = value;
#ifdef PC
	printf("collision avodance value set to: %c\n", distance);
#endif
 
} 
 
 
unsigned int read_distance(void){ 
#ifdef PC
	printf("collision avodance value is: %c\n", distance);
#endif
    return distance; 
}



