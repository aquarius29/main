/*****************************************************************************
* Product: 
* Version: 
* Released: April 8 2011
* Updated: April 28 2011
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
#include "proto_tint.h"
#endif
/***************************************************************************** 
    Definitions 
*****************************************************************************/ 

#include <stdio.h>
#include <string.h>


struct move move_ca;

 
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
 
void proto_write(struct move mv){ 
    move_ca = mv;
#ifdef PC
 storeForTint(WRITE, MOVEMENT, UNKNOWN, mv.speed);
 storeForTint(WRITE, MOVEMENT, UNKNOWN, mv.direction_move);
	#ifdef DEBUG
	printf("Movement value set to: %d , %d\n", mv.speed , mv.direction_move);
  #endif
#endif
} 
 
 
struct move proto_read(){ 
#ifdef PC
  storeForTint(READ, COLLISION, UNKNOWN, move_ca.speed);
  storeForTint(READ, COLLISION, UNKNOWN, move_ca.direction_move);
	#ifdef DEBUG
	printf("Movement value set to: %d , %d\n", move_ca.speed , move_ca.direction_move);
  #endif
#endif

    return move_ca; 
} 




