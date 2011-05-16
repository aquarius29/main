<<<<<<< HEAD
/* 
 * Inpired by Magnus Bergqvist
 * Author(S) Huilin Shi
 * created 16 April 2011
 * updated 28 April 2011 
 * updated  2 May   2011
 * updated 12 May   2011
 */
=======
/*************************************************************************************
 * @file stab_cunit_test.c
 * @brief Test the funtions in the code of stablization group 
 * @author Huilin Shi
 * Inpired by Magnus Bergqvist(motor groups test code)
 * @date 16/04/2011
 * @history
 *    16/04/2011: Initial version // Huilin Shi
 *    28/04/2011: Added more test funtions // Huilin Shi
 *    02/05/2011: Added more test funtions // Huilin Shi
 *    12/05/2011: Added more test funitons + format // Huilin Shi
 *************************************************************************************/
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93

/* compile with something like this:  gcc stab_cunit_test.c -o test -lcunit */

#include <stdio.h>
#include "CUnit/CUnit.h"
#include "../src/stab_filter.c"
<<<<<<< HEAD
//#include "stab_filter.c"
=======
//#include "../src/stab_rg.c"
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93


/* 
 * something is strange with "stab_rg.c", can't use it even
 * though I include it, that's why I copyed the function instead.
 */

float convert_gyro_raw_to_deg_s(float a)
{
  return a / SSF;
}

/* Test convert_gyro_raw_to_deg_s funtion from "stab_rg.c"
 * test_convert_gyro_raw_to_deg_s() checks so that expected results are returned, 
 * with a fault tolerance by 0,0001
 */

void test_convert_gyro_raw_to_deg_s(void)
{
    CU_ASSERT_DOUBLE_EQUAL(convert_gyro_raw_to_deg_s(28.75), 2.0, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(convert_gyro_raw_to_deg_s(149.543), 10.402991304, 0.0001); 
    CU_ASSERT_DOUBLE_EQUAL(convert_gyro_raw_to_deg_s(6.123), 0.425947826, 0.0001); 
<<<<<<< HEAD
}

/* 
 *Test comp_filter function from "stab_filter.c"
 * test_comp_filter checks so that expected results are returned, 
 * with a fault tolerance by 0,0001
 *it takes 3 arguments, the first one is which function are using, the second is the
 return value (result) and the third one is about the decimals/how accurate it is
=======
    CU_ASSERT_DOUBLE_EQUAL(convert_gyro_raw_to_deg_s(960.125), 66.791304348, 0.0001); 
    CU_ASSERT_DOUBLE_EQUAL(convert_gyro_raw_to_deg_s(50.875), 3.539130435, 0.0001); 
}

/* 
 * Test comp_filter function from "stab_filter.c"
 * test_comp_filter checks so that expected results are returned, 
 * with a fault tolerance by 0,0001
 * it takes 3 arguments, the first one is which function are using, the second is the
 * return value (result) and the third one is about the decimals/how accurate it is
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
 */

void test_comp_filter(void)
{
    CU_ASSERT_DOUBLE_EQUAL(comp_filter(12.45, 0.45, 20.12), 19.99306, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(comp_filter(28.34, 0.005, 10.29), 10.651294, 0.0001);
<<<<<<< HEAD
=======
    CU_ASSERT_DOUBLE_EQUAL(comp_filter(5.34, 0.01, 3.46), 3.498188, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(comp_filter(50.78, 0.68, 30.91), 31.347384, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(comp_filter(1.28, 0.51, 15.36), 15.108388, 0.0001);
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
}

/*
 * Test init_filter funtion from "stab_filter.c"
 * first I take the global variables from stab_filter.c
 * give them the numbers 1, 2, 3 and after the init_filter
 * they are supposed to be 0, 0, 0 for each of them.
 */

void test_init_filter(void)
{
    int i;
    for(i = 0; i < 2; i++)
    {
        acc_vector[i] = i + 1;
        gyro_vector[i] = i + 1;
        filter_est[i] = i + 1;

        CU_ASSERT(acc_vector[i] == i + 1);
        CU_ASSERT(gyro_vector[i] == i + 1);
        CU_ASSERT(filter_est[i] == i +1);
    }
    init_filter();
    for(i = 0; i < 2; i++)
    {
        CU_ASSERT(acc_vector[i] == 0);
        CU_ASSERT(gyro_vector[i] == 0);
        CU_ASSERT(filter_est[i] == 0);
    }
}

/*check_add_ok() gives a print_out on the screen when a test suite or a test
has been created, the char** passed to this function should always be in the 
style:
    suite "suite name"
    test "test name"*/

void check_add_ok(char* msg)
{
    if(CU_get_error() == CUE_SUCCESS)
    {
            fprintf(stdout, "%s created successfully!\n",msg);
    }
    else
    {
        fprintf(stdout, "failed to create %s\n",msg);
        return;
    }
}


int main(int argc)
{

/***************************************************************************/
    CU_ErrorCode ec = CU_initialize_registry();    
    if(ec == CUE_SUCCESS)
    {
        fprintf(stdout, "\ntest register initialized successfully!\n");   
    }
    else
    {
        fprintf(stdout, "Failed to initialize test register");
        return;
    }   

/***************************************************************************/
/* add convert_gyro_raw_to_deg_s and test_comp_filter tests*/

    CU_pSuite stab_filter = CU_add_suite("stab_filter",NULL,NULL);    
    check_add_ok("suite stab_filter");

    CU_add_test(stab_filter, "convert_gyro", test_convert_gyro_raw_to_deg_s);
    check_add_ok("test stab_rg.c");

    CU_add_test(stab_filter, "init_filter", test_init_filter);
    check_add_ok("test stab_filter.c");

    CU_add_test(stab_filter, "comp_filter", test_comp_filter);
    check_add_ok("test stab_filter.c");


/***************************************************************************/

    CU_console_run_tests();
    CU_cleanup_registry();
}
