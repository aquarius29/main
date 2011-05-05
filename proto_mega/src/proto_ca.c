/*****************************************************************************
* Product: 
* Version: 
* Released: April 7 2011
* Updated: May 05 2011
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
int raw = -1;//int raw = -1; Default Value


void proto_write_raw(int value){ 
    raw = value;
#ifdef PC
	storeForTint(WRITE, COLLISION, UNKNOWN, value);
	#ifdef DEBUG
	printf("collision avodance value set to: %c\n", value);
	#endif
#endif
 
} 
 
 
unsigned int proto_read_raw(void){ 
#ifdef PC
	storeForTint(READ, MOVEMENT, UNKNOWN, raw);
	#ifdef DEBUG
	printf("collision avodance value is: %c\n", raw);
	#endif
#endif
    return raw; 
}


