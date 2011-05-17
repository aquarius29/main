/*Skeleton created by Magnus Bergqvist*/
/* This particular set of test cases created by Kristofer Hansson Aspman */
/* compile with something like this:
    gcc cunit_moto_msg_handler.c ../src/moto_msg_handler.c -DPC 
    -o cunit_moto_msg_handler -lcunit
*/

#include <stdio.h>
#include <stdint.h>
#include "CUnit/CUnit.h"
#include "cunit_moto_msg_handler.h"
#include "../src/moto_driver_functions.h"



/*Holds the definition of the type msg and the macros INT_TO_BITFIELD(a)
and BITFIELD_TO_CHAR(a)*/
#include "../src/moto_msg_manipulation.h"
/*Includes the tested functions examineID, ...*/
#include "../src/moto_msg_handler.h"

uint16_t rightPulse = IDLE_SPEED;
uint16_t leftPulse = IDLE_SPEED;
uint16_t frontPulse = IDLE_SPEED;
uint16_t rearPulse = IDLE_SPEED;

/*test_examineID checks so that the function returns 0 when a properly*/
/* formatted message is sent in as argument to the function */
void test_moto_examineID(void){

    msg binary;
    uint8_t a = 0xa3;
    binary = INT_TO_BITFIELD(&a);
    msg_pointer mp = &binary;
    
    CU_ASSERT(examineID(mp)==0);
}


/*test_examineID_bad_msg checks so that the function returns 1 when the bad*/
/* message (0xF) is sent in as argument to the function */
void test_moto_examineID_bad_msg(void){

    msg binary;
    uint8_t a = 0xF;
    binary = INT_TO_BITFIELD(&a);
    msg_pointer mp = &binary;   
    CU_ASSERT(examineID(mp)==1);
}


/* test_moto_controlMotors and test_moto_specialMotorCommand
 * added by Björn Eriksson.
 */




void test_moto_controlMotors(void){
    leftPulse = IDLE_SPEED;
    rightPulse = IDLE_SPEED;
    frontPulse = IDLE_SPEED;
    rearPulse = IDLE_SPEED;
    msg binary;
    /* increase rear motor message */
    uint8_t a = 0xA1;
    binary = INT_TO_BITFIELD(&a);
    msg_pointer mp = &binary;
    controlMotors(mp);
    CU_ASSERT(leftPulse == IDLE_SPEED);
    CU_ASSERT(rightPulse == IDLE_SPEED);
    CU_ASSERT(frontPulse == IDLE_SPEED);
    CU_ASSERT(rearPulse == (IDLE_SPEED + NORMAL_STEP));

    /* decrease right motor message */
    a = 0x88;
    binary = INT_TO_BITFIELD(&a);
    mp = &binary;
    controlMotors(mp);
    CU_ASSERT(leftPulse == IDLE_SPEED);
    CU_ASSERT(rightPulse == (IDLE_SPEED - NORMAL_STEP));
    CU_ASSERT(frontPulse == IDLE_SPEED);
    CU_ASSERT(rearPulse == (IDLE_SPEED + NORMAL_STEP));

}

void test_moto_specialMotorCommand(void){
    msg binary;
    /* a = hover message */
    uint8_t a = 0xFF;
    binary = INT_TO_BITFIELD(&a);
    msg_pointer mp = &binary;
    specialMotorCommand(mp);
    CU_ASSERT(leftPulse == HOVER_PULSE_LEFT);
    CU_ASSERT(rightPulse == HOVER_PULSE_RIGHT);
    CU_ASSERT(frontPulse == HOVER_PULSE_FRONT);
    CU_ASSERT(rearPulse == HOVER_PULSE_REAR);
    /* a = strafe left message */
    a = 0xCC;
    binary = INT_TO_BITFIELD(&a);
    mp = &binary;
    specialMotorCommand(mp);
    CU_ASSERT(leftPulse == (HOVER_PULSE_LEFT - NORMAL_STEP));
    CU_ASSERT(rightPulse == (HOVER_PULSE_RIGHT + NORMAL_STEP));
    CU_ASSERT(frontPulse == HOVER_PULSE_FRONT);
    CU_ASSERT(rearPulse == HOVER_PULSE_REAR);
    /* a = decrease all panic message */
    leftPulse = 1450;
    rightPulse = 1550;
    frontPulse = 1500;
    rearPulse = 1500;
    a = 0xD0;
    binary = INT_TO_BITFIELD(&a);
    mp = &binary;
    specialMotorCommand(mp);
    CU_ASSERT(leftPulse == (1450 - PANIC_STEP));
    CU_ASSERT(rightPulse == (1550 - PANIC_STEP));
    CU_ASSERT(frontPulse == (1500 - PANIC_STEP));
    CU_ASSERT(rearPulse == (1500 - PANIC_STEP));    
}

/*
 *   to be tested:
 *   controlMotors()
 *   specialMotorCommand()
 *
 */

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

    CU_console_run_tests();
    CU_cleanup_registry();
}
#endif
