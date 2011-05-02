/*
* unitmain.c
*
*  Created on: 7 apr 2011
*      Author: Shan Huang
*/

#include "CUnit/Basic.h"

#include "unit_tests.c"

int main() {
    CU_pSuite simSuite = NULL;

  /* Initialize the CUnit test registry */
    if(CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

  /* Add a suite to the registry */
    simSuite = CU_add_suite("Simulations", init_suite, clean_suite);

    if(	NULL == simSuite ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

  /* Add tests to suite */
    if(	NULL == CU_add_test(simSuite, "Single Destination", test_init_list)
        // || NULL == CU_add_test(simSuite, "Multiple Destinations", multiple_destinations)
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

  /* Run all tests using the CUnit Console interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}