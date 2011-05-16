<<<<<<< HEAD
/*!
* @file proto_ca.c
* @brief Collision avoidance messages
* @author Elnaz Shahmehr
* @history 
* 			- 2011-04-11 first release
*			- 2011-05-10 updated by Elnaz
* 			- 2011-05-12 updated by Mihail
*			- 2011-05-12 updated by Elnaz
*/

#ifdef PC
   #include <stdio.h> 
#endif

#include <stdlib.h>
#include "proto_lib.h"
   
/*************************************************************************** 
    Implementations 
****************************************************************************/
int16_t yaw = -1;//int16_t yaw = -1; Default Value for direction 

void proto_write_yaw(int16_t value){ 
    yaw = value;
#ifdef PC
	storeForTint(PROTO_WRITE, PROTO_COLLISION, PROTO_UNKNOWN, value);
	#ifdef DEBUG
		printf("collision avodance value set to: %c\n", value);
	#endif
#endif
} 
 
int16_t proto_read_yaw(void){ 
#ifdef PC
	storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, yaw);
	#ifdef DEBUG
		printf("collision avodance value is: %c\n", yaw);
	#endif
#endif
    return yaw; 
}


=======
/*****************************************************************************
* Product: 
* Version: 
* Released: April 7 2011
* Updated: May 10 2011
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
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
int yaw = -1;//int raw = -1; Default Value


void proto_write_raw(int value){ 
    yaw = value;
#ifdef PC
	storeForTint(WRITE, COLLISION, UNKNOWN, value);
	#ifdef DEBUG
	printf("collision avodance value set to: %c\n", value);
	#endif
#endif
 
} 
 
 
int proto_read_yaw(void){ 
#ifdef PC
	storeForTint(READ, MOVEMENT, UNKNOWN, yaw);
	#ifdef DEBUG
	printf("collision avodance value is: %c\n", yaw);
	#endif
#endif
    return yaw; 
}


>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
