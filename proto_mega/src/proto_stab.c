/*****************************************************************************
* Product: 
* Version: 
* Released: April 1 2011
* Updated: April 28 2011
*
* Copyright (C) 2011 Peter Mihail Anton, Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

#ifdef PC
   #include <stdio.h>
   #include "proto_tint.h"
#endif

char stab_ctrl = 0; // from STAB; DEFAULT is 0

void proto_write_stab_ctrl(char value){
	stab_ctrl = value;
#ifdef PC
storeForTint(WRITE, STAB, UNKNOWN, stab_ctrl);
	#ifdef DEBUG
	printf("Stab value set to: %c\n", stab_ctrl);
  #endif
#endif	
}
	
char proto_read_stab_ctrl(void){
#ifdef PC
 storeForTint(READ, STAB, UNKNOWN, stab_ctrl);
	#ifdef DEBUG
	printf("Stab value is: %c\n", stab_ctrl);
 #endif
#endif
	return stab_ctrl;	
}
