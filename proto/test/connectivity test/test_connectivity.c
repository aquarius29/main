#include "connectlib.h"
#include "connectlib.c"


/* Set up and clean up test suite */

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void testCase1(void) {
 	unsigned char navi_to_connectivity_msg;
  	navi_to_connectivity_msg=read_navi_to_connectivity();
  	CU_ASSERT(navi_to_connectivity_msg==0x12);
}
