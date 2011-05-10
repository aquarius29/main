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
   #include "proto_lib.h" 
#endif
 
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


