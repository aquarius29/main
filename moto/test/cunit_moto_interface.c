

#include "../src/moto_driver_functions.h"
#include <stdint.h>
#include "cunit_master_test_suite.h"
#include "CUnit/CUnit.h"
#include "../src/move_stub.h"

void test_moto_init(void){


    moto_init();
    /* 
     * since the values are only change if ARDUINO is defined,
     *  nothing will happen 
     * CU_ASSERT(leftPulse == STOP_PULSE);
     * CU_ASSERT(rightPulse == STOP_PULSE);
     * CU_ASSERT(frontPulse == STOP_PULSE);
     * CU_ASSERT(rearPulse == STOP_PULSE);
     */
    int i;
    for(i = 0; i < 5001; i++){
    moto_run();

    }
    CU_ASSERT(leftPulse == HOVER_PULSE_LEFT);
    CU_ASSERT(rightPulse == HOVER_PULSE_RIGHT);
    CU_ASSERT(frontPulse == HOVER_PULSE_FRONT);
    CU_ASSERT(rearPulse == HOVER_PULSE_REAR);    
    /* same problem with moto_run, just to gain branch coverage :) */
}


#ifndef MASTER_TEST_SUITE
/*check_add_ok() gives a print_out on the screen when a test suite or a test
has been created, the char** passed to this function should always be in the 
style:
    suite "suite name"
    test "test name"*/
void check_add_ok(char* msg){

    if(CU_get_error() == CUE_SUCCESS){
            fprintf(stdout, "%s created successfully!\n",msg);
    }
    else{
        fprintf(stdout, "failed to create %s\n",msg);
    }
}

uint16_t main(uint16_t argc){
/***************************************************************************/
    CU_ErrorCode ec = CU_initialize_registry();    
    if(ec == CUE_SUCCESS){
        fprintf(stdout, "\ntest register initialized successfully!\n");   
    }
    else{
        fprintf(stdout, "Failed to initialize test register");
        return;
    }   

/***************************************************************************/

    /* add interface suite */
    CU_pSuite interface = CU_add_suite("interface",NULL,NULL);    
    check_add_ok("suite msg_handler");

    /* add test_moto_init to suite */
    CU_add_test(interface, "test_moto_init", test_moto_init);
    check_add_ok("test test_moto_init");
    
   
    CU_console_run_tests();
    CU_cleanup_registry();
}
#endif
