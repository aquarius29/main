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

#include "protolib_ca.h"
#include "protolib_ca.c"


/* Set up and clean up test suite */

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void testCase1(void) {
 	int height;
  	height=read_height();
  	CU_ASSERT(height==15);

}

void testCase2(void) {
 	int direction;
  	direction=read_direction();
  	CU_ASSERT(direction==22);

}
 void testCase3(void) {
 	int distance;
  	distance=read_distance();
  	CU_ASSERT(distance==30);

}
