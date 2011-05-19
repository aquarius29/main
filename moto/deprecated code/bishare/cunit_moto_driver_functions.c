/*Created by Magnus Bergqvist*/ 
/*Extent by Bishare Sufi*/ /* this code is improved and has a new version we
tested different states given values and checked if the output 
is as aspected */
/* compile with something like this:
    gcc cunit_moto_driver_functions.c ../src/moto_driver_functions.c -DPC 
    -o cunit_moto_driver_functions -lcunit
*/

#include <stdio.h>
#include "CUnit/CUnit.h"
#include "../src/moto_driver_functions.h"
/*this is where right- left- front- and rearPulse comes from as extern
unsigned chars, originating from the tested .c-file*/

/*test_increaseMotorPulse checks so that expected results are returned, even
when it comes to the higher and lower limits of the spectra*/
void test_moto_startMotors(void){

    moto_startMotors();
    CU_ASSERT(rightPulse==40);
    CU_ASSERT(leftPulse==40);
    CU_ASSERT(frontPulse==40);
    CU_ASSERT(rearPulse==40);
}

void test_moto_stopMotors(void){

    moto_stopMotors();
    CU_ASSERT(rightPulse==0);
    CU_ASSERT(leftPulse==0);
    CU_ASSERT(frontPulse==0);
    CU_ASSERT(rearPulse==0);
}

/*added motor tests asserts by Bishare Sufi*/
/* all asserts and tests in this file are passed,
   but we did new test for the latest version */

void test_moto_hover(void){
    
      moto_hover();
      CU_ASSERT(rightPulse == 90);
      CU_ASSERT(leftPulse == 90);
      CU_ASSERT(frontPulse == 90);
      CU_ASSERT(rearPulse == 90);

}

void test_moto_goForward(void){
     
     moto_goForward();
     CU_ASSERT(frontPulse == 88);
     CU_ASSERT(rearPulse == 92);

}

void test_moto_goBackward(void){
     
     moto_goBackward();
     CU_ASSERT(frontPulse == 90);
     CU_ASSERT(rearPulse == 90);

} 

void test_moto_strafeRight(void){
     
     moto_strafeRight();
     CU_ASSERT(leftPulse == 92);
     CU_ASSERT(rightPulse == 88);

}

void test_moto_strafeLeft(void){
     
     moto_strafeLeft();
     CU_ASSERT(leftPulse == 90);
     CU_ASSERT(rightPulse == 90);

}

void test_moto_rotateLeft(void){

     moto_rotateLeft();
     CU_ASSERT(leftPulse == 92);
     CU_ASSERT(rightPulse == 92);
     CU_ASSERT(frontPulse == 88);
     CU_ASSERT(rearPulse == 88);

}

void test_moto_rotateRight(void){

     moto_rotateRight();
     CU_ASSERT(leftPulse == 90);
     CU_ASSERT(rightPulse == 90);
     CU_ASSERT(frontPulse == 90);
     CU_ASSERT(rearPulse == 90);

}

void test_moto_increaseAllNormal(void){

     moto_increaseAllNormal();
     CU_ASSERT(rightPulse == 92);
     CU_ASSERT(leftPulse == 92);
     CU_ASSERT(frontPulse == 92);
     CU_ASSERT(rearPulse == 92);

}

void test_moto_increaseAllPanic(void){

     moto_increaseAllPanic();
     CU_ASSERT(rightPulse == 96);
     CU_ASSERT(leftPulse == 96);
     CU_ASSERT(frontPulse == 96);
     CU_ASSERT(rearPulse == 96);

}

void test_moto_decreaseAllNormal(void){

     moto_decreaseAllNormal();
     CU_ASSERT(rightPulse == 94);
     CU_ASSERT(leftPulse == 94);
     CU_ASSERT(frontPulse == 94);
     CU_ASSERT(rearPulse == 94);

}

void test_moto_decreaseAllPanic(void){

     moto_decreaseAllPanic();
     CU_ASSERT(rightPulse == 90);
     CU_ASSERT(leftPulse == 90);
     CU_ASSERT(frontPulse == 90);
     CU_ASSERT(rearPulse == 90);

}

void test_moto_increaseLeftNormal(void){
 
     moto_increaseLeftNormal();
     CU_ASSERT(leftPulse == 92);

}

void test_moto_increaseRightNormal(void){

     moto_increaseRightNormal();
     CU_ASSERT(rightPulse == 92);

}

void test_moto_increaseFrontNormal(void){

     moto_increaseFrontNormal();
     CU_ASSERT(frontPulse == 92);

}

void test_moto_increaseRearNormal(void){

     moto_increaseRearNormal();
     CU_ASSERT(rearPulse == 92);

}

void test_moto_increaseLeftPanic(void){

     moto_increaseLeftPanic();
     CU_ASSERT(leftPulse == 96);

}

void test_moto_increaseRightPanic(void){

     moto_increaseRightPanic();
     CU_ASSERT(rightPulse == 96);

}

void test_moto_increaseFrontPanic(void){

     moto_increaseFrontPanic();
     CU_ASSERT(frontPulse == 96);

}

void test_moto_increaseRearPanic(void){

     moto_increaseRearPanic();
     CU_ASSERT(rearPulse == 96);

}

void test_moto_decreaseLeftNormal(void){

     moto_decreaseLeftNormal();
     CU_ASSERT(leftPulse == 94);
     
}

void test_moto_decreaseRightNormal(void){

     moto_decreaseRightNormal();
     CU_ASSERT(rightPulse == 94);

}

void test_moto_decreaseFrontNormal(void){

     moto_decreaseFrontNormal();
     CU_ASSERT(frontPulse == 94);

}

void test_moto_decreaseRearNormal(void){

     moto_decreaseRearNormal();
     CU_ASSERT(rearPulse == 94);

}

void test_moto_decreaseLeftPanic(void){

     moto_decreaseLeftPanic();
     CU_ASSERT(leftPulse == 90);

}

void test_moto_decreaseRightPanic(void){

     moto_decreaseRightPanic();
     CU_ASSERT(rightPulse == 90);

}

void test_moto_decreaseFrontPanic(void){

     moto_decreaseFrontPanic();
     CU_ASSERT(frontPulse == 90);

}

void test_moto_decreaseRearPanic(void){

     moto_decreaseRearPanic();
     CU_ASSERT(rearPulse == 90);

}

void test_printMotorStatus(void){

     printMotorStatus();
     CU_ASSERT(leftPulse == 90);
     CU_ASSERT(rightPulse == 90);
     CU_ASSERT(frontPulse == 90);
     CU_ASSERT(rearPulse == 90);

}

void test_sendMsg(void){

     sendMsg();
     CU_ASSERT(leftPulse == 90);
     CU_ASSERT(rightPulse == 90);
     CU_ASSERT(frontPulse == 90);
     CU_ASSERT(rearPulse == 90);

}


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
/* add start stop motor tests */

    CU_pSuite start_stop = CU_add_suite("start_stop_motors",NULL,NULL);    
    check_add_ok("Suite start_stop_motors");

    CU_add_test(start_stop, "Test start motors ", test_moto_startMotors);
    check_add_ok("Test test_moto_startMotors");
    
    CU_add_test(start_stop, "Test stop motors ", test_moto_stopMotors);
    check_add_ok("Test test_moto_stopMotors");

/*added motor tests by Bishare Sufi*/
/* here we add a new test for each function */
/* all tests are passed */

    CU_add_test(start_stop, "Test moto hover ", test_moto_hover);
    check_add_ok("Test test_moto_hover"); 

    CU_add_test(start_stop, "Test go forward ", test_moto_goForward);
    check_add_ok("Test test_go_forward");

    CU_add_test(start_stop, "Test go backward ", test_moto_goBackward);
    check_add_ok("Test test_go_backward");

    CU_add_test(start_stop, "Test strafeRight ", test_moto_strafeRight);
    check_add_ok("Test test_strafeRight");
    
    CU_add_test(start_stop, "Test strafeLeft ", test_moto_strafeLeft);
    check_add_ok("Test test_strafeLeft");

    CU_add_test(start_stop, "Test rotateLeft ", test_moto_rotateLeft);
    check_add_ok("Test test_rotate_left");

    CU_add_test(start_stop, "Test rotateRight ", test_moto_rotateRight);
    check_add_ok("Test test_rotate_right");
    
    CU_add_test(start_stop, "Test increase all normal ", test_moto_increaseAllNormal);
    check_add_ok("Test test_increase_all_normal");

    CU_add_test(start_stop, "Test increase all panic ", test_moto_increaseAllPanic);
    check_add_ok("Test test_increase_all_panic");

    CU_add_test(start_stop, "Test decrease all normal ", test_moto_decreaseAllNormal);
    check_add_ok("Test test_decrease_all_normal");

    CU_add_test(start_stop, "Test decrease all panic ", test_moto_decreaseAllPanic);
    check_add_ok("Test test_decrease_all_panic");

    CU_add_test(start_stop, "Test increaseLeftNormal ", test_moto_increaseLeftNormal);
    check_add_ok("Test test_increase_left_normal");

    CU_add_test(start_stop,"Test increaseRightNormal",test_moto_increaseRightNormal);
    check_add_ok("Test test_increase_right_normal");

    CU_add_test(start_stop,"Test increaseFrontNormal",test_moto_increaseFrontNormal);
    check_add_ok("Test test_increase_front_normal");

    CU_add_test(start_stop,"Test increaseRearNormal ", test_moto_increaseRearNormal);
    check_add_ok("Test test_increase_rear_normal"); 

    CU_add_test(start_stop, "Test increaseLeftPanic ", test_moto_increaseLeftPanic);
    check_add_ok("Test test_increase_left_panic");

    CU_add_test(start_stop, "Test increaseRightPanic ", test_moto_increaseRightPanic);
    check_add_ok("Test test_increase_right_panic");

    CU_add_test(start_stop, "Test increaseFrontPanic ", test_moto_increaseFrontPanic);
    check_add_ok("Test test_increase_front_panic");

    CU_add_test(start_stop, "Test increaseRearPanic ", test_moto_increaseRearPanic);
    check_add_ok("Test test_increase_rear_panic");   

    CU_add_test(start_stop, "Test decreaseLeftNormal ", test_moto_decreaseLeftNormal);
    check_add_ok("Test test_decrease_left_normal");

    CU_add_test(start_stop, "Test decreaseRightNormal ", test_moto_decreaseRightNormal);
    check_add_ok("Test test_decrease_right_normal");

    CU_add_test(start_stop, "Test decreaseFrontNormal ", test_moto_decreaseFrontNormal);
    check_add_ok("Test test_decrease_front_normal");

    CU_add_test(start_stop, "Test decreaseRearNormal ", test_moto_decreaseRearNormal);
    check_add_ok("Test test_decrease_rear_normal");

    CU_add_test(start_stop, "Test decreaseLeftPanic ", test_moto_decreaseLeftPanic);
    check_add_ok("Test test_decrease_left_panic");

    CU_add_test(start_stop, "Test decreaseRightPanic ", test_moto_decreaseRightPanic);
    check_add_ok("Test test_decrease_right_panic");

    CU_add_test(start_stop, "Test decreaseFrontPanic ", test_moto_decreaseFrontPanic);
    check_add_ok("Test test_decrease_front_panic");

    CU_add_test(start_stop, "Test decreaseRearPanic ", test_moto_decreaseRearPanic);
    check_add_ok("Test test_decrease_rear_panic");

    CU_add_test(start_stop, "Test printMotorStatus ", test_printMotorStatus);
    check_add_ok("Test test_print_motor_status");

    CU_add_test(start_stop, "Test sendMsg ", test_sendMsg);
    check_add_ok("Test test_send_MSG");

    CU_console_run_tests();
    CU_cleanup_registry();

}
