#ifdef MASTER_TEST_SUITE

#include <stdio.h>
#include "CUnit/CUnit.h"
#include "cunit_master_test_suite.h"

#ifdef AUTOMATED
    #include "CUnit/Basic.h"
#endif

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

int main(int argc){
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

    /* msg_handler, holds tests from cunit_moto_msg_handler.c */
    
    CU_pSuite msg_handler = CU_add_suite("msg_handler",NULL,NULL);    
    check_add_ok("suite msg_handler");
    
    CU_add_test(msg_handler, "test_moto_examineID", test_moto_examineID);
    check_add_ok("test test_moto_examineID");
    
    CU_add_test(msg_handler, "test_moto_examineID_bad_msg",
        test_moto_examineID_bad_msg);
    check_add_ok("test test_moto_examineID_bad_msg");

    CU_add_test(msg_handler, "test_moto_controlMotors", test_moto_controlMotors);
    check_add_ok("test test_moto_controlMotors");

    CU_add_test(msg_handler, "test_moto_specialMotorCommand", test_moto_specialMotorCommand);
    check_add_ok("test test_moto_specialMotorCommand");

    /*examineID suite, holds tests from cunit_moto_msg_handler.c */    
    CU_pSuite examineID = CU_add_suite("examine_ID",NULL,NULL);
    check_add_ok("suite examine_ID");

    CU_add_test(examineID, "test_examineID_start", test_examineID_start);
    check_add_ok("test test_examineID_start");    
    
    CU_add_test(examineID, "test_examineID_stop", test_examineID_stop);
    check_add_ok("test test_examineID_stop");  
    
    CU_add_test(examineID, "examineID_controlMotors", examineID_controlMotors);
    check_add_ok("examineID_controlMotors");  
  
    CU_add_test(examineID, "examineID_specialCommands", examineID_specialCommands);
    check_add_ok("examineID_specialCommands");    

    /* Create a test suite for start_stop functions */
    /* holds tests from from cunit_moto_driver_functions.c */
    CU_pSuite start_stop = CU_add_suite("start_stop_motors",NULL,NULL);    
    check_add_ok("suite start_stop_motors");

    /* Add appropriate test functions to the start_stop suite */
    CU_add_test(start_stop, "test_moto_startMotors", test_moto_startMotors);
    check_add_ok("test test_moto_startMotors");
    
    CU_add_test(start_stop, "test_moto_stopMotors",
        test_moto_stopMotors);
    check_add_ok("test test_moto_stopMotors");
    
    /* Create a test suite for increase/decrease all-functions */
    /* holds tests from from cunit_moto_driver_functions.c */
    CU_pSuite increase_decrease_all = 
        CU_add_suite("increase_decrese_all",NULL,NULL);
    check_add_ok("suite increase_decrease_all");
    
    /* Add appropriate test functions to the increase_decrease_all suite */
    CU_add_test(increase_decrease_all, "test_moto_increaseAllNormal",
        test_moto_increaseAllNormal);
    check_add_ok("test test_moto_increaseAllNormal");
    
    CU_add_test(increase_decrease_all, "test_moto_decreaseAllNormal",
        test_moto_decreaseAllNormal);
    check_add_ok("test test_moto_decreaseAllNormal");
    
    CU_add_test(increase_decrease_all, "test_moto_increaseAllPanic",
        test_moto_increaseAllPanic);
    check_add_ok("test test_moto_increaseAllPanic");
    
    CU_add_test(increase_decrease_all, "test_moto_decreaseAllPanic",
        test_moto_decreaseAllPanic);
    check_add_ok("test test_moto_decreaseAllPanic");

    /* Create a test suite for special command functions */
    /* holds tests from from cunit_moto_driver_functions.c */
    CU_pSuite special_commands = CU_add_suite("special commands",NULL,NULL);    
    check_add_ok("suite special_commands");

    /* Add appropriate test functions to the special_command suite */
    CU_add_test(special_commands, "test_moto_specialCommands",
        test_moto_specialCommands);
    check_add_ok("Test test_moto_specialCommands");

    /* holds tests from from cunit_moto_interface.c */
    /* add interface suite */
    CU_pSuite interface = CU_add_suite("interface",NULL,NULL);    
    check_add_ok("suite msg_handler");

    /* add test_moto_init to suite */
    CU_add_test(interface, "test_moto_init", test_moto_init);
    check_add_ok("test test_moto_init");
    
/***************************************************************************/
#ifdef AUTOMATED
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    //CU_console_run_tests();
#else
    CU_console_run_tests();
#endif
    CU_cleanup_registry();
    return CU_get_error();
}
#endif
