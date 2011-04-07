/*****************************************************************************
* Product: 
* Version: 
* Released: April 1 2011
* Updated:  April 1 2011
*
* Copyright (C) 2011 Peter Mihail Anton 
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/


#include "stab.h"
#include "motor.h"

int main (void){
  while (1){
    	stab();
		motor();
    }
  return 1;
}

