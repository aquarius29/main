/*****************************************************************************
* Product: 
* Version: 
* Released: April 1 2011
* Updated: April 1 2011
*
* Copyright (C) 2011 Peter Mihail Anton 
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/


#include <stdio.h>
#include "protolib.h"

int stab(void){
	write_motor_ctrl((char)10);
	return 1;
}

