#include "navigation_lib.h"
#include "navigation_lib.c"


/* Set up and clean up test suite */

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void testCase1(void) {
 	 unsigned char mov_ca_msg;
  	mov_ca_msg=read_nav_to_mov_ca();
  	CU_ASSERT(mov_ca_msg=0x14);

}

void testCase2(void) {
 	unsigned char connect_msg;
  	connect_msg=read_connect_to_nav();
  	CU_ASSERT(connect_msg=0x15)

}
 void testCase3(void) {
 	unsigned char current_loc;
  	current_loc=get_current_location();
  	CU_ASSERT(current_loc=0x17)

}
void testCase4(void) {
	unsigned char destination_msg;
  	destination_msg=read_destination_msg_();
  	CU_ASSERT(destination_msg=0x18);

}


