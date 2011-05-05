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
   #include "proto_lib.h"
#endif

/*****************************************************************************/
int dir = 0;

void proto_write_direction(int value){ 
    dir = value;
#ifdef PC
	storeForTint(WRITE, MOVEMENT, UNKNOWN, dir);
	#ifdef DEBUG
	printf("Movement value set to: %c\n", dir);
#endif
 #endif
} 
 
 
unsigned int proto_read_direction(void){ 
#ifdef PC
       storeForTint(READ, MOVEMENT, UNKNOWN, dir);
	#ifdef DEBUG
	printf("Movement value is: %c\n", dir);
#endif
#endif
    return dir; 
}



