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

#include <stdio.h>
#include <string.h>


struct move {
        int speed;
        int direction;
      
} move_ca;

 
//write from movement to collision avodance  
void write(struct move mv);// proto API 
 
 
//read from movement to collision avodance 
struct move read();// proto API 
 

 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
 
void write(struct move mv){ 
    move_ca = mv;
#ifdef PC
	printf("Movement value set to: %d , %d\n", mv.speed , mv.direction);
#endif
} 
 
 
struct move read(){ 
#ifdef PC
	printf("Movement value set to: %d , %d\n", mv.speed , mv.direction);
#endif

    return move_ca; 
} 




