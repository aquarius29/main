#include "CUnit/Basic.h"

#include "test_nav_gps.c"


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
	if(NULL == CU_add_test(pSuite1, "Test case 1", test_od_pn1))
	{
     // || NULL == CU_add_test(pSuite1, ...[next test case]...))
      
    CU_cleanup_registry();
    return CU_get_error();
  }


	if(NULL == CU_add_test(pSuite1, "Test case 2", test_od_pn2))
	// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite1, "Test case 3", test_od_pn3))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite1, "Test case 4", test_od_pn4))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite1, "Test case 6", test_od_pn6))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite1, "Test case 7", test_od_pn7))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite1, "Test case 8", test_od_pn8))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
		
	if(NULL == CU_add_test(pSuite1, "Test case 9",test_od_dijk1))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite1, "Test case 10",test_od_dijk2))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite1, "Test case 11",test_od_dijk3))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite1, "Test case 12",test_od_dijk4))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite1, "Test case 13",test_od_dijk5))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite1, "Test case 14",test_od_dijk8))
		// || NULL == CU_add_test(pSuite1, ...[next test case]...))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}	
	
	/* Run all tests using console interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}