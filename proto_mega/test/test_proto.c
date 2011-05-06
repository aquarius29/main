/*****************************************************************************
* Product: 
* Version: 
* Released: April 13 2011
* Updated: may 06 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

#include "../src/proto_lib.h"
#include "../src/proto_move.c"
#include "CUnit/Basic.h"
#include "../src/proto_ca.c"

/* Set up and clean up test suite */

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void testCase1(void) {
 	int dir;
  	dir=proto_read_direction();
  	CU_ASSERT(dir==0);

}

void testCase2(void) {
 	int raw;
  	raw = proto_read_raw();
  	CU_ASSERT(raw== -1);

}



int main(void) {
  CU_pSuite pSuite1 = NULL;
  
  /* Initialize CUnit test registry */
  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add suite to the registry */
  pSuite1 = CU_add_suite("Suite 1", init_suite, clean_suite);
  if(NULL == pSuite1) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add tests to suite */
  if(NULL == CU_add_test(pSuite1, "Test case 1", testCase1)
     // || NULL == CU_add_test(pSuite1, ...[next test case]...)
     ) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if(NULL == CU_add_test(pSuite1, "Test case 2", testCase2)
     // || NULL == CU_add_test(pSuite1, ...[next test case]...)
     ) {
    CU_cleanup_registry();
    return CU_get_error();
  }


  /* Run all tests using console interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
