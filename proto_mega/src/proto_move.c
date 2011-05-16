<<<<<<< HEAD
/*!
* @file proto_move.c
* @brief Movement messages
* @author Elnaz Shahmehr
* @history 
*           - 2011-04-08
* 			- 2011-05-05 updated by Elnaz
* 			- 2011-05-12 updated by Mihail
*			- 2011-05-12 updated by Elnaz
*/

#ifdef PC
   #include <stdio.h>
#endif

#include <stdlib.h>
#include "proto_lib.h"

/*****************************************************************************/
int16_t dir = 0;//Deafult value 

void proto_write_direction(int16_t value){ 
    dir = value;
#ifdef PC
	storeForTint(PROTO_WRITE, PROTO_MOVEMENT, PROTO_UNKNOWN, dir);
	#ifdef DEBUG
	printf("Movement value set to: %c\n", dir);
    #endif
#endif
} 
 
uint16_t proto_read_direction(void){ 
#ifdef PC
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, dir);
	#ifdef DEBUG
	printf("Movement value is: %c\n", dir);
    #endif
#endif
    return dir; 
}
=======
/*****************************************************************************
* Product: 
* Version: 
* Released: April 8 2011
* Updated: may 05 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

 
 #ifdef PC
   #include <stdio.h>
#endif
   #include "proto_lib.h"

/*****************************************************************************/
int dir = 0;//Deafult value 

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



>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
