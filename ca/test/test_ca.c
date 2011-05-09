/*
 * File:		test_ca_logic.c
 * Brief:	main file of the CUnit testing
 * Author:	Alina Butko
 * Date:		2011-05-09
 * Version:	0.1
 * History:	2011-05-09 create the file
 * Detail:
 */

#include "../src/ca_interface.h"
#include "../src/ca_filters.c"
#include "../src/ca_object_calculations.c"
#include "../src/ca_logic.c"
#include <stdio.h>

#define COMPARE_ARR(a,v1,v2,v3,v4) ( (a[0]==v1) && (a[1]==v2) && (a[2]==v3) && (a[3]==v4))
#define COMPARE_ARR2(a,v1,v2,v3,v4,v5) ( (a[0]==v1) && (a[1]==v2) && (a[2]==v3) && (a[3]==v4) && (a[4]==v5))


/* Set up and clean up test suite */

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void testCase1(void) {
  	CU_ASSERT_EQUAL(speed_filter(3),25);
  	CU_ASSERT_EQUAL(speed_filter(30),50);
  	CU_ASSERT_EQUAL(speed_filter(90),75);
  	CU_ASSERT_EQUAL(speed_filter(130),100);
  	CU_ASSERT_EQUAL(speed_filter(134515328),130);

}

void testCase2(void) {
   CU_ASSERT(COMPARE_ARR(distance_filter(25,10,11,10,10),1,1,1,1));
   CU_ASSERT(COMPARE_ARR(distance_filter(25,30,20,10,15),0,1,1,1));
	CU_ASSERT(COMPARE_ARR(distance_filter(25,10,60,20,15),1,0,1,1));
	CU_ASSERT(COMPARE_ARR(distance_filter(25,10,10,40,20),1,1,0,1));
	CU_ASSERT(COMPARE_ARR(distance_filter(25,20,21,20,50),1,1,1,0));
  	CU_ASSERT(COMPARE_ARR(distance_filter(25,30,40,60,50),0,0,0,0));
  	CU_ASSERT(COMPARE_ARR(distance_filter(25,30,51,40,10),0,0,0,1));
  	CU_ASSERT(COMPARE_ARR(distance_filter(25,30,41,10,10),0,0,1,1));
  	CU_ASSERT(COMPARE_ARR(distance_filter(25,10,11,40,50),1,1,0,0));
  	CU_ASSERT(COMPARE_ARR(distance_filter(25,10,51,40,30),1,0,0,0));
  	CU_ASSERT(COMPARE_ARR(distance_filter(25,30,11,40,10),0,1,0,1));
  	CU_ASSERT(COMPARE_ARR(distance_filter(25,20,51,15,60),1,0,1,0));
}

void testCase3(void) {
	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,10,11,10,10)), 0,0,0,0,1));
   CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,30,20,10,15)), 1,0,0,0,1));
	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,10,60,20,15)), 0,1,0,0,1));
	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,10,10,40,20)), 0,0,1,0,1));
	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,20,21,20,50)), 0,0,0,1,1));
  	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,30,40,60,50)), 1,1,1,1,1));
  	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,30,51,40,10)), 1,1,1,0,1));
  	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,30,41,10,10)), 1,1,0,0,1));
  	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,10,11,40,50)), 0,0,1,1,1));
  	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,10,51,40,30)), 0,1,1,1,1));
  	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,30,11,40,10)), 1,0,1,0,1));
  	CU_ASSERT(COMPARE_ARR2(ir_filter(distance_filter(25,20,51,15,60)), 0,1,0,1,1));
}

void testCase4(void) {
	CU_ASSERT(COMPARE_ARR2(currentDirection_filter(1,ir_filter(distance_filter(25,30,40,60,50))), 1,0,1,1,1));
	CU_ASSERT(COMPARE_ARR2(currentDirection_filter(2,ir_filter(distance_filter(25,30,40,60,50))), 0,1,1,1,1));
	CU_ASSERT(COMPARE_ARR2(currentDirection_filter(3,ir_filter(distance_filter(25,30,40,60,50))), 1,1,1,0,1));
	CU_ASSERT(COMPARE_ARR2(currentDirection_filter(4,ir_filter(distance_filter(25,30,40,60,50))), 1,1,0,1,1));
	CU_ASSERT(COMPARE_ARR2(currentDirection_filter(1,ir_filter(distance_filter(25,10,11,10,10))), 0,0,0,0,1));
}

/*void testCase5(void){
	CU_ASSERT(COMPARE_ARR2(moving_closer_filter(moving_closer((1,1,1,1)),currentDirection_filter(1,ir_filter(distance_filter(25,30,40,60,50))), 0,0,0,0,0));
}

void testCase6(void){
	CU_ASSERT(final_direction(moving_closer_filter(moving_closer(),currentDirection_filter(1,ir_filter(distance_filter(25,30,40,60,50))))), 
}
*/
