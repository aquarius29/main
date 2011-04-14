/*****************************************************************************
* Product: 
* Version: 
* Released: April 13 2011
* Updated: April 14 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

#include "protolib_move.h"
#include "protolib_move.c"


/* Set up and clean up test suite */

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void testCase1(void) {
 	int speed;
  	speed=read_speed();
  	CU_ASSERT(speed==300);

}

void testCase2(void) {
 	int direction;
  	direction=read_direction();
  	CU_ASSERT(direction==250);

}

