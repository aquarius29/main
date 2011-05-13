#include "CUnit/Basic.h"

#include "test_psched_initpool.c"

int main(void) {
  CU_pSuite pSuite1 = NULL;
  
  /* Initialize CUnit test registry */
  
  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add suite to the registry */
  pSuite1 = CU_add_suite("hi", init_suite, clean_suite);
  if(NULL == pSuite1) {
    CU_cleanup_registry();
    return CU_get_error();
  }


  /* add tests to suite */
  if(NULL == CU_add_test(pSuite1, "Test case 1", test_psched_initpool)
     || NULL == CU_add_test(pSuite1, "test case 2", test_psched_addproc)
     || NULL == CU_add_test(pSuite1, "test case 3", test_psched_run)
     ){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using console interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
