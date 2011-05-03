/*****************************************************************************
* Product: 
* Version: 
* Released: April 8 2011
* Updated: May 3 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

 
 #ifdef PC
   #include <stdio.h>
   #include "proto_stab_move.h"
#include "proto_tint.h"
#endif
/***************************************************************************** 
    Definitions 
*****************************************************************************/ 

#include <stdio.h>
#include <string.h>


struct stab stab_move;

 
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
 
void proto_stabWriteAttitude(struct stab sb){ 
    stab_move = sb;
#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, sb.roll);
 storeForTint(WRITE, STAB, UNKNOWN, sb.pitch);
 storeForTint(WRITE, STAB, UNKNOWN, sb.yaw);
	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n", sb.roll , sb.pitch,sb.yaw);
  #endif
#endif
} 
 
 
void proto_stabWriteAcc(struct stab sb){ 
    stab_move = sb;
#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, sb.acc_x);
 storeForTint(WRITE, STAB, UNKNOWN, sb.acc_y);
 storeForTint(WRITE, STAB, UNKNOWN, sb.acc_z);
	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n", sb.acc_x , sb.acc_y,sb.acc_z);
  #endif
#endif
} 


void proto_stabWriteHeading(struct stab sb){ 
    stab_move = sb;
#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, sb.heading);

	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n", sb.heading);
  #endif
#endif
} 


void proto_stabWritePressure(struct stab sb){ 
    stab_move = sb;
#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, sb.pressure);

	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n", sb.pressure);
  #endif
#endif
}

