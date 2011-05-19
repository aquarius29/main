/*Skeleton created by Magnus Bergqvist*/
/* This particular set of test cases created by Kristofer Hansson Aspman */
/* compile with something like this:
    gcc cunit_moto_msg_handler.c ../src/moto_msg_handler.c 
    ../src/moto_driver_functions.c ../src/moto_stubs.c -DPC 
    -o cunit_moto_msg_handler -lcunit
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "CUnit/CUnit.h"
#include "cunit_master_test_suite.h"
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

uint16_t right_motor = 0;
uint16_t left_motor = 0;
uint16_t front_motor = 0;
uint16_t rear_motor = 0;

/*To be able to send a struct to certain functions*/
msg_pointer testStructPtr;

/*current_value is used to temporarily store values for later comparsion*/
void current_value(){
    right_motor= rightPulse;
    left_motor= leftPulse;
    front_motor = frontPulse;
    rear_motor = rearPulse;
}

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

 /* test _examineID_start testes if  the start command is send that the moters will
* be in IDLE_SPEED
* Added by Rahwa Bahta
*/
 void test_examineID_start(void){
	
	
    testStructPtr = malloc(sizeof(msg));   
    
    testStructPtr -> ID = 1;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;

    examineID(  testStructPtr);
	
    CU_ASSERT(rightPulse==IDLE_SPEED);
    CU_ASSERT(leftPulse==IDLE_SPEED);
    CU_ASSERT(frontPulse==IDLE_SPEED);
    CU_ASSERT(rearPulse==IDLE_SPEED);
/*copy all current value to  current value variables*/
    current_value();
	
}

/*
 *   to be tested:
 *   controlMotors()
 *   specialMotorCommand()
 *
 */
void examineID_controlMotors(void){
    /* Allocate memory, freed in the last statement of this function*/
    testStructPtr = malloc(sizeof(msg));   
/* increase all motor speed normal step*/
    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 1;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 1;
    printf("Before examineID\n");
    examineID(testStructPtr);
    printf("After examineID\n");	
    CU_ASSERT(rightPulse== right_motor + NORMAL_STEP);
    CU_ASSERT(leftPulse== left_motor + NORMAL_STEP);
    CU_ASSERT(frontPulse== front_motor + NORMAL_STEP);
    CU_ASSERT(rearPulse== rear_motor + NORMAL_STEP);

    current_value();
	
/* Increase all motor speed panic step*/

    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 1;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 1;
    
    examineID(testStructPtr);
    
    CU_ASSERT(rightPulse== right_motor + PANIC_STEP);
    CU_ASSERT(leftPulse== left_motor + PANIC_STEP);
    CU_ASSERT(frontPulse== front_motor + PANIC_STEP);
    CU_ASSERT(rearPulse== rear_motor + PANIC_STEP);
    
    current_value();
  
/*Decrease all motor speed normal step */
    testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 1;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 1;
	
    examineID(testStructPtr);
	
    CU_ASSERT(rightPulse== right_motor - NORMAL_STEP);
    CU_ASSERT(leftPulse== left_motor - NORMAL_STEP);
    CU_ASSERT(frontPulse== front_motor -  NORMAL_STEP);
    CU_ASSERT(rearPulse== rear_motor - NORMAL_STEP);

    current_value();

/*Decrease all panic motors speed panic step*/

    testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 1;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 1;
	
    examineID(testStructPtr);
	
    CU_ASSERT(rightPulse== right_motor - PANIC_STEP);
    CU_ASSERT(leftPulse== left_motor - PANIC_STEP);
    CU_ASSERT(frontPulse== front_motor - PANIC_STEP);
    CU_ASSERT(rearPulse== rear_motor - PANIC_STEP);

    current_value();
    
/*Increase right motor speed normal step*/

    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    CU_ASSERT(rightPulse== right_motor + NORMAL_STEP );
    current_value();
    
/*Decrease right motor speed normal step*/

   testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    CU_ASSERT(rightPulse== right_motor - NORMAL_STEP);
    current_value();
    
/*Increase right motor speed panic step*/

    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    CU_ASSERT(rightPulse== right_motor + PANIC_STEP);
    current_value();
    
    
/*Decrease right motor speed panic step*/

   testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    CU_ASSERT(rightPulse== right_motor - PANIC_STEP);
    current_value();
    
/*Increase left motor speed normal step*/

    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 0;
    testStructPtr -> right  =0;
    testStructPtr -> left = 1;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    CU_ASSERT(leftPulse== left_motor + NORMAL_STEP);
    current_value();
    
/*Decrease left motor speed normal step*/

   testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 0;
    testStructPtr -> right  =0 ;
    testStructPtr -> left = 1;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    CU_ASSERT(leftPulse== left_motor - NORMAL_STEP);
    current_value();
    
/*Increase left motor speed panic step*/

    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 1;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    CU_ASSERT(leftPulse== left_motor + PANIC_STEP);
    current_value();

/*Decrease left motor seed panic step*/

    testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 1;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    
    CU_ASSERT(leftPulse== left_motor - PANIC_STEP);
    
    current_value();
    
/*Increase front motor speed normal speed*/

    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    
    CU_ASSERT(frontPulse== front_motor + NORMAL_STEP);
    
    current_value();
    
/*Decrease front motor speed normal step*/

    testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    
    CU_ASSERT(frontPulse== front_motor - NORMAL_STEP);
    
    current_value();
    
/* Increase front motor speed panic step*/
    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    
    CU_ASSERT(frontPulse== front_motor + PANIC_STEP);
    
    current_value();
    
/*Decrease front motor speed panic step*/
    testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 0;
    
    examineID(testStructPtr);
    
    CU_ASSERT(frontPulse== front_motor - PANIC_STEP);
    
    current_value();
    
/* Increase rear motor speed normal speed*/
    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 1;
    
    examineID(testStructPtr);
    
    CU_ASSERT(rearPulse== rear_motor + NORMAL_STEP);
    
    current_value();
    
/*Decrease rear motor speed normal speed*/
    testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 1;
    
    examineID(testStructPtr);
    
    CU_ASSERT(rearPulse== rear_motor - NORMAL_STEP);
    
    current_value();
    
/*Increase rear motor speed panic step*/
    testStructPtr -> ID = 2;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 1;
    
    examineID(testStructPtr);
    
    CU_ASSERT(rearPulse== rear_motor + PANIC_STEP);
    
    current_value();

/*Decrease rear motor speed panic step*/
    testStructPtr -> ID = 2;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 1;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 1;
    
    examineID(testStructPtr);
    
    CU_ASSERT(rearPulse== rear_motor - PANIC_STEP);
    
    current_value();
    free(testStructPtr);
}

void examineID_specialCommands(void){

/* Sets the initial pulses to hover */
    rightPulse = HOVER_PULSE_RIGHT;
    leftPulse = HOVER_PULSE_LEFT;
    frontPulse = HOVER_PULSE_FRONT;
    rearPulse = HOVER_PULSE_REAR;

    right_motor = HOVER_PULSE_RIGHT;
    left_motor = HOVER_PULSE_LEFT;
    front_motor = HOVER_PULSE_FRONT;
    rear_motor = HOVER_PULSE_REAR;

/* Allocate memory, freed in the last statement of this function*/
    testStructPtr = malloc(sizeof(msg));   
/*Increase rear and decrease front motor speed normal step*/
    testStructPtr -> ID = 3;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 1;
	
    examineID(testStructPtr);
    CU_ASSERT(frontPulse== front_motor - NORMAL_STEP);
    CU_ASSERT(rearPulse== rear_motor + NORMAL_STEP);
    current_value();
    
/*Increase front and decrease rear motor speed normal step*/
    testStructPtr -> ID = 3;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 1;
    testStructPtr -> rear = 1;
	
    examineID(testStructPtr);
    CU_ASSERT(frontPulse== front_motor +NORMAL_STEP);
    CU_ASSERT(rearPulse== rear_motor - NORMAL_STEP);
    current_value();

/*Increase left and decrease right motor speed normal step*/
    testStructPtr -> ID = 3;
    testStructPtr -> increase = 1;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 1;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
	
    examineID(testStructPtr);
    CU_ASSERT(leftPulse== left_motor +NORMAL_STEP);
    CU_ASSERT(rightPulse== right_motor - NORMAL_STEP);
    current_value();
    
    /*Increase right and decrease left motor speed normal step*/
    testStructPtr -> ID = 3;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 1;
    testStructPtr -> left = 1;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
	
    examineID(testStructPtr);
    CU_ASSERT(leftPulse== left_motor - NORMAL_STEP);
    CU_ASSERT(rightPulse== right_motor + NORMAL_STEP);
    current_value(); 
    
/*Go forward*/
//---------------------------------------------------------------------------------------------> to be added
    free(testStructPtr);
}

/*tests examineID function by sending stop command and check 
*if each motors speed changes to zero
*Added by Rahwa Bahta
*/

void test_examineID_stop(void){
	
    testStructPtr -> ID = 0;
    testStructPtr -> increase = 0;
    testStructPtr -> panic = 0;
    testStructPtr -> right  = 0;
    testStructPtr -> left = 0;
    testStructPtr -> front = 0;
    testStructPtr -> rear = 0;
   

    examineID(testStructPtr);
    
    CU_ASSERT(rightPulse==STOP_PULSE);
    CU_ASSERT(leftPulse==STOP_PULSE);
    CU_ASSERT(frontPulse==STOP_PULSE);
    CU_ASSERT(rearPulse==STOP_PULSE);
	
    current_value();
    free(testStructPtr);
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
/* add start stop motor tests */

    CU_pSuite msg_handler = CU_add_suite("msg_handler",NULL,NULL);    
    check_add_ok("suite msg_handler");
    
    CU_pSuite examineID = CU_add_suite("examine_ID",NULL,NULL);
    check_add_ok("suite examine_ID");

    CU_add_test(msg_handler, "test_moto_examineID", test_moto_examineID);
    check_add_ok("test test_moto_examineID");
    
    CU_add_test(msg_handler, "test_moto_examineID_bad_msg",
        test_moto_examineID_bad_msg);
    check_add_ok("test test_moto_examineID_bad_msg");

    CU_add_test(msg_handler, "test_moto_controlMotors", test_moto_controlMotors);
    check_add_ok("test test_moto_controlMotors");

    CU_add_test(msg_handler, "test_moto_specialMotorCommand", test_moto_specialMotorCommand);
    check_add_ok("test test_moto_specialMotorCommand");
    
    CU_add_test(examineID, "test_examineID_start", test_examineID_start);
    check_add_ok("test test_examineID_start");    
    
    CU_add_test(examineID, "test_examineID_stop", test_examineID_stop);
    check_add_ok("test test_examineID_stop");  
    
    CU_add_test(examineID, "examineID_controlMotors", examineID_controlMotors);
    check_add_ok("examineID_controlMotors");  
    
    CU_add_test(examineID, "examineID_specialCommands", examineID_specialCommands);
    check_add_ok("examineID_specialCommands");  
    

    CU_console_run_tests();
    CU_cleanup_registry();
}
#endif
