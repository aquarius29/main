/*****************************************************************************
* Product: 
* Version: 
* Released: April 1 2011
* Updated: April 1 2011
*
* Copyright (C) 2011 Peter Mihail Anton, Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

#ifdef PC
   #include <stdio.h>
#endif

char stab_ctrl = 0; // from STAB; DEFAULT is 0

void proto_write_stab_ctrl(char value){
	stab_ctrl = value;
#ifdef PC
	printf("Stab value set to: %c\n", stab_ctrl);
#endif	
}
	
char proto_read_stab_ctrl(void){
#ifdef PC
	printf("Stab value is: %c\n", stab_ctrl);
#endif
	return stab_ctrl;	
}
