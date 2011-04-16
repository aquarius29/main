#include "CUnit/Basic.h"
#include "test_scheduler_h.c"

int main(void) 
{
    CU_pSuite pSuite1 = 0;
  
    /* Initialize CUnit test registry */
    if(CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add suite to the registry */
    pSuite1 = CU_add_suite("Suite 1", init_suite, clean_suite);
    if(0 == pSuite1) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add tests to suite */
    if(0 == CU_add_test(pSuite1, "Test case 1", testSched1))
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
