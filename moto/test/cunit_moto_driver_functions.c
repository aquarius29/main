/*!
 * @file cunit_moto_driver_functions.c
 * @brief cunit tests for moto_driver_functions.c
 * @date 2011-04-25
 * @author Magnus Bergqvist
 * extent by @Bishare Sufi
 * @version 5
 * @history 2011-04-07 - created first draft \n
            2011-04-15 - adjusted it for new moto_driver_functions.c \n
            2011-04-18 - updated and new tests added
            2011-04-23 - new tests added, auto adjustment possibilities \n
                         to code changes was added
            2011-04-25 - new tests added and minor adjustments to other
 * @details compile with something like this: \n
    gcc cunit_moto_driver_functions.c cunit_stubs.c \n
    ../src/moto_driver_functions.c -DPC \n
    -o cunit_moto_driver_functions -lcunit
 */

#include <stdio.h>
#include "CUnit/CUnit.h"
#include "../src/moto_stubs.h" /* test stubs to replace arduino functions */
#include "cunit_master_test_suite.h"

#include "../src/moto_driver_functions.h"
/* 
 * moto_driver_functions.h is where right- left- front- and rearPulse 
 * comes from, originating from the tested .c-file
 */
 

/* Variables to temporary store the values for comparsion in */ 
int rightP;
int leftP;
int frontP;
int rearP;

/* 
 * A function that eases up the work of storing motor signal values in \n
 * the temporary variables in a convenient way
 */
void temp_copy(void){
    rightP = rightPulse;
    leftP = leftPulse;
    frontP = frontPulse;
    rearP = rearPulse;
}

/* 
 * test_moto_startMotors checks so that expected predefined 
 * values are returned
 */
void test_moto_startMotors(void){

    moto_startMotors();
    CU_ASSERT(rightPulse==IDLE_SPEED);
    CU_ASSERT(leftPulse==IDLE_SPEED);
    CU_ASSERT(frontPulse==IDLE_SPEED);
    CU_ASSERT(rearPulse==IDLE_SPEED);
}

/* 
 * test_moto_stopMotors checks so that expected predefined 
 * values are returned
 */
void test_moto_stopMotors(void){

    moto_stopMotors();
    CU_ASSERT(rightPulse==STOP_PULSE);
    CU_ASSERT(leftPulse==STOP_PULSE);
    CU_ASSERT(frontPulse==STOP_PULSE);
    CU_ASSERT(rearPulse==STOP_PULSE);
}

/* 
 * test_moto_increaseAllNormal checks so that expected predefined 
 * values are returned
 */
void test_moto_increaseAllNormal(void){

    moto_startMotors();
    temp_copy(); /*copy all motor values to temp variables*/

    moto_increaseAllNormal();

    CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
    CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
    CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
    CU_ASSERT(rearPulse == rearP + NORMAL_STEP);
    
    /*
     * Set all motor pulses close to an upper value and see if the
     * logic will keep the value of exceeding it's maximum.
     */
    rightPulse = MAX_PULSE_RIGHT - (NORMAL_STEP * 2);
    leftPulse = MAX_PULSE_LEFT - (NORMAL_STEP * 2);
    frontPulse = MAX_PULSE_FRONT - (NORMAL_STEP * 2);
    rearPulse = MAX_PULSE_REAR - (NORMAL_STEP * 2);
     
    temp_copy();
          
    moto_increaseAllNormal();
    CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
    CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
    CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
    CU_ASSERT(rearPulse == rearP + NORMAL_STEP);
    
    temp_copy();
    
    moto_increaseAllNormal();
    CU_ASSERT(rightPulse == MAX_PULSE_RIGHT);
    CU_ASSERT(leftPulse == MAX_PULSE_LEFT);
    CU_ASSERT(frontPulse == MAX_PULSE_FRONT);
    CU_ASSERT(rearPulse == MAX_PULSE_REAR);
    
    moto_increaseAllNormal();
    CU_ASSERT(rightPulse == MAX_PULSE_RIGHT);
    CU_ASSERT(leftPulse == MAX_PULSE_LEFT);
    CU_ASSERT(frontPulse == MAX_PULSE_FRONT);
    CU_ASSERT(rearPulse == MAX_PULSE_REAR);
}
/* 
 * test_moto_decreaseAllNormal checks so that expected predefined 
 * values are returned
 */
void test_moto_decreaseAllNormal(void){

    temp_copy();

    moto_decreaseAllNormal();
    CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
    CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
    CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
    CU_ASSERT(rearPulse == rearP - NORMAL_STEP);
    
    rightPulse = MIN_PULSE_RIGHT + (NORMAL_STEP * 2);
    leftPulse = MIN_PULSE_LEFT + (NORMAL_STEP * 2);
    frontPulse = MIN_PULSE_FRONT + (NORMAL_STEP * 2);
    rearPulse = MIN_PULSE_REAR + (NORMAL_STEP * 2);
     
    temp_copy();
          
    moto_decreaseAllNormal();
    CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
    CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
    CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
    CU_ASSERT(rearPulse == rearP - NORMAL_STEP);
    
    temp_copy();
    
    moto_decreaseAllNormal();
    CU_ASSERT(rightPulse == MIN_PULSE_RIGHT);
    CU_ASSERT(leftPulse == MIN_PULSE_LEFT);
    CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
    CU_ASSERT(rearPulse == MIN_PULSE_REAR);
    
    moto_decreaseAllNormal();
    CU_ASSERT(rightPulse == MIN_PULSE_RIGHT);
    CU_ASSERT(leftPulse == MIN_PULSE_LEFT);
    CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
    CU_ASSERT(rearPulse == MIN_PULSE_REAR);

}

void test_moto_increaseAllPanic(void){

    temp_copy(); /*copy all motor values to temp variables*/
    moto_increaseAllPanic();

    CU_ASSERT(rightPulse == rightP + PANIC_STEP);
    CU_ASSERT(leftPulse == leftP + PANIC_STEP);
    CU_ASSERT(frontPulse == frontP + PANIC_STEP);
    CU_ASSERT(rearPulse == rearP + PANIC_STEP);
    
    /*
     * Set all motor pulses close to an upper value and see if the
     * logic will keep the value of exceeding it's maximum.
     */
    rightPulse = MAX_PULSE_RIGHT - (PANIC_STEP * 2);
    leftPulse = MAX_PULSE_LEFT - (PANIC_STEP * 2);
    frontPulse = MAX_PULSE_FRONT - (PANIC_STEP * 2);
    rearPulse = MAX_PULSE_REAR - (PANIC_STEP * 2);
     
    temp_copy();
          
    moto_increaseAllPanic();
    CU_ASSERT(rightPulse == rightP + PANIC_STEP);
    CU_ASSERT(leftPulse == leftP + PANIC_STEP);
    CU_ASSERT(frontPulse == frontP + PANIC_STEP);
    CU_ASSERT(rearPulse == rearP + PANIC_STEP);
    
    temp_copy();
    
    moto_increaseAllPanic();
    CU_ASSERT(rightPulse == MAX_PULSE_RIGHT);
    CU_ASSERT(leftPulse == MAX_PULSE_LEFT);
    CU_ASSERT(frontPulse == MAX_PULSE_FRONT);
    CU_ASSERT(rearPulse == MAX_PULSE_REAR);
    
    moto_increaseAllPanic();
    CU_ASSERT(rightPulse == MAX_PULSE_RIGHT);
    CU_ASSERT(leftPulse == MAX_PULSE_LEFT);
    CU_ASSERT(frontPulse == MAX_PULSE_FRONT);
    CU_ASSERT(rearPulse == MAX_PULSE_REAR);
}

void test_moto_decreaseAllPanic(void){

/* decrease all pulses panic step the motors are reacting as expected */

    temp_copy();

    moto_decreaseAllPanic();
    CU_ASSERT(rightPulse == rightP - PANIC_STEP);
    CU_ASSERT(leftPulse == leftP - PANIC_STEP);
    CU_ASSERT(frontPulse == frontP - PANIC_STEP);
    CU_ASSERT(rearPulse == rearP - PANIC_STEP);
    
    rightPulse = MIN_PULSE_RIGHT + (PANIC_STEP * 2);
    leftPulse = MIN_PULSE_LEFT + (PANIC_STEP * 2);
    frontPulse = MIN_PULSE_FRONT + (PANIC_STEP * 2);
    rearPulse = MIN_PULSE_REAR + (PANIC_STEP * 2);


    temp_copy();
          
    moto_decreaseAllPanic();
    CU_ASSERT(rightPulse == rightP - PANIC_STEP);
    CU_ASSERT(leftPulse == leftP - PANIC_STEP);
    CU_ASSERT(frontPulse == frontP - PANIC_STEP);
    CU_ASSERT(rearPulse == rearP - PANIC_STEP);
    
    temp_copy();
    
    moto_decreaseAllPanic();
    CU_ASSERT(rightPulse == MIN_PULSE_RIGHT);
    CU_ASSERT(leftPulse == MIN_PULSE_LEFT);
    CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
    CU_ASSERT(rearPulse == MIN_PULSE_REAR);
    
    moto_decreaseAllPanic();
    CU_ASSERT(rightPulse == MIN_PULSE_RIGHT);
    CU_ASSERT(leftPulse == MIN_PULSE_LEFT);
    CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
    CU_ASSERT(rearPulse == MIN_PULSE_REAR);

}

/* @uthor Bishare Sufi */
/* this code has been improved once the old version is in deprecate folder */

/* this code has been improved once the old cunit test
   for this file is in deprecate folder */


void test_moto_hover(void){

      /* all motors are on hover level*/
     /* the motors are reacting as expected */
    
      moto_hover();
      CU_ASSERT(rightPulse == HOVER_PULSE_RIGHT);
      CU_ASSERT(leftPulse == HOVER_PULSE_LEFT);
      CU_ASSERT(frontPulse == HOVER_PULSE_FRONT);
      CU_ASSERT(rearPulse == HOVER_PULSE_REAR);

      rightPulse = MIN_PULSE_RIGHT + (NORMAL_STEP * 30);
      leftPulse = MIN_PULSE_LEFT + (NORMAL_STEP * 30);
      frontPulse = MIN_PULSE_FRONT + (NORMAL_STEP * 30);
      rearPulse = MIN_PULSE_REAR + (NORMAL_STEP * 30);

      moto_hover();
      CU_ASSERT(rightPulse == HOVER_PULSE_RIGHT);
      CU_ASSERT(leftPulse == HOVER_PULSE_LEFT);
      CU_ASSERT(frontPulse == HOVER_PULSE_FRONT);
      CU_ASSERT(rearPulse == HOVER_PULSE_REAR);

      rightPulse = MIN_PULSE_RIGHT - (NORMAL_STEP * 30);
      leftPulse = MIN_PULSE_LEFT - (NORMAL_STEP * 30);
      frontPulse = MIN_PULSE_FRONT - (NORMAL_STEP * 30);
      rearPulse = MIN_PULSE_REAR - (NORMAL_STEP * 30);

      moto_hover();
      CU_ASSERT(rightPulse == HOVER_PULSE_RIGHT);
      CU_ASSERT(leftPulse == HOVER_PULSE_LEFT);
      CU_ASSERT(frontPulse == HOVER_PULSE_FRONT);
      CU_ASSERT(rearPulse == HOVER_PULSE_REAR);


      rightPulse = MAX_PULSE_RIGHT - (NORMAL_STEP * 80);
      leftPulse = MAX_PULSE_LEFT - (NORMAL_STEP * 80);
      frontPulse = MAX_PULSE_FRONT - (NORMAL_STEP * 80);
      rearPulse = MAX_PULSE_REAR - (NORMAL_STEP * 80);

/* the motors are responding as expected */

     temp_copy();
     moto_hover();

     rightPulse = MIN_PULSE_RIGHT + (NORMAL_STEP * 200);

     leftPulse = MIN_PULSE_LEFT + (NORMAL_STEP * 200);

     frontPulse = MIN_PULSE_FRONT + (NORMAL_STEP * 200);

     rearPulse = MIN_PULSE_REAR + (NORMAL_STEP * 200);

     temp_copy();
     moto_hover();

     rightPulse = MIN_PULSE_RIGHT - (NORMAL_STEP * 200);

     leftPulse = MIN_PULSE_LEFT - (NORMAL_STEP * 200);

     frontPulse = MIN_PULSE_FRONT - (NORMAL_STEP * 200);

     rearPulse = MIN_PULSE_REAR - (NORMAL_STEP * 200);

      moto_hover();
      CU_ASSERT(rightPulse == HOVER_PULSE_RIGHT);
      CU_ASSERT(leftPulse == HOVER_PULSE_LEFT);
      CU_ASSERT(frontPulse == HOVER_PULSE_FRONT);
      CU_ASSERT(rearPulse == HOVER_PULSE_REAR);

      rightPulse = MAX_PULSE_RIGHT + (NORMAL_STEP * 8);
      leftPulse = MAX_PULSE_LEFT + (NORMAL_STEP * 8);
      frontPulse = MAX_PULSE_FRONT + (NORMAL_STEP * 8);
      rearPulse = MAX_PULSE_REAR + (NORMAL_STEP * 8);

     temp_copy();
     moto_hover();

     rightPulse = MAX_PULSE_RIGHT - (NORMAL_STEP * 100);

     leftPulse = MAX_PULSE_LEFT - (NORMAL_STEP * 100);

     frontPulse = MAX_PULSE_FRONT - (NORMAL_STEP * 100);

     rearPulse = MAX_PULSE_REAR - (NORMAL_STEP *100);

     temp_copy();
     moto_hover();

     rightPulse = MAX_PULSE_RIGHT + (NORMAL_STEP * 100);

     leftPulse = MAX_PULSE_LEFT + (NORMAL_STEP * 100);

     frontPulse = MAX_PULSE_FRONT + (NORMAL_STEP * 100);

     rearPulse = MAX_PULSE_REAR + (NORMAL_STEP * 100);

      moto_hover();
      CU_ASSERT(rightPulse == HOVER_PULSE_RIGHT);
      CU_ASSERT(leftPulse == HOVER_PULSE_LEFT);
      CU_ASSERT(frontPulse == HOVER_PULSE_FRONT);
      CU_ASSERT(rearPulse == HOVER_PULSE_REAR);


}

void test_moto_goForward(void){

     /* go forward normal steps */
     /* all motors are on hover level*/
     /* the motors are reacting as expected */

/* go forward test function all motors are allready in the hover
   level the pulses of the motors have to be between min and max pulses
   and any where between min and max pulses has to pass  the motors are
   reacting as expected and does not exceed max or min levels */
     
     temp_copy();
     moto_goForward();
     CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

     frontPulse = MIN_PULSE_FRONT + (NORMAL_STEP * 2);
     rearPulse = MAX_PULSE_REAR - (NORMAL_STEP * 2);

     temp_copy();
     moto_goForward();
     CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);


     frontPulse == MIN_PULSE_FRONT + (NORMAL_STEP * 12);
     rearPulse == MAX_PULSE_REAR - (NORMAL_STEP * 12);

     /* motors are responding exactly as expected "vatten tät code?" */
  
     temp_copy();
     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);

     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);
     
     moto_goForward();
     CU_ASSERT(frontPulse == MIN_PULSE_FRONT);
     CU_ASSERT(rearPulse == MAX_PULSE_REAR);
    
}

void test_moto_goBackward(void){

     /* go backward normal steps  */
     /* all motors are on hover level*/
     /* the motors are responding as expected and not exceeding the 
        boundaries*/
  

/* go backward test function all motors are in the hover
   level the pulses of the motors have to be between min and max pulses
   and any where between min and max pulses has to pass  the motors are
   reacting as expected and does not exceed max or min levels */

/* motors are on hover level */
  
     moto_hover();
     temp_copy();
     moto_goBackward();

     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

     /* it is not exceeding the boundaries, "vatten tät code?" */

     frontPulse == MAX_PULSE_FRONT - (NORMAL_STEP * 100);
     rearPulse == MIN_PULSE_REAR + (NORMAL_STEP * 100);

     temp_copy();
     moto_goBackward();

     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

     temp_copy();
     moto_goBackward();

     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);


     moto_hover();
     temp_copy();
     moto_goBackward();
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

     frontPulse == MAX_PULSE_FRONT - (NORMAL_STEP * 120);
     rearPulse == MIN_PULSE_REAR + (NORMAL_STEP * 120);

     temp_copy();
     moto_goBackward();
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

}     

void test_moto_strafeRight(void){

     /* turn right normal steps */
     /* all motors are on hover level*/
     /* the motors are responding as expected and not exceeding the 
        boundaries*/
     
 /* moto_strafeRight here the motors are reacting as expected 
    starting from hover increasing left pulse and at the same time
    decreasing right pulse */

 /* motors are on hover level */

     moto_hover();
     temp_copy();
     moto_strafeRight();

     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);

     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
    
     
     /*motors are reacting as expected*/

     temp_copy();
     moto_strafeRight();

     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);

     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);

     temp_copy();
     moto_strafeRight();
     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);

     leftPulse == MAX_PULSE_LEFT - (NORMAL_STEP *60);
     rightPulse == MIN_PULSE_RIGHT + (NORMAL_STEP *60);

     temp_copy();
     moto_strafeRight();
     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);


}

void test_moto_strafeLeft(void){

     /* turn left normal steps */
     /* all motors are on hover level*/
     /* the motors are responding as expected and not exceeding the 
        boundaries*/

     /* moto_strafeLeft here the motors are reacting as expected 
        increasing right pulse and at the same time decreasing
        the left pulse */
      
     /* motors are on hover level */

     moto_hover();
     temp_copy();
     moto_strafeLeft();

     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);

     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP); 

     temp_copy();
     moto_strafeLeft();

     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);

     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);

     moto_hover();
     temp_copy();
     moto_strafeLeft();
     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);

     leftPulse == MIN_PULSE_LEFT + (NORMAL_STEP * 80);
     rightPulse == MAX_PULSE_RIGHT - (NORMAL_STEP * 80);

     temp_copy();
     moto_strafeLeft();
     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);

}

void test_moto_rotateLeft(void){

     /* rotate to the left normal steps */
     /* all motors are on hover level*/
     /* the motors are responding as expected and not exceeding the 
        boundaries*/
     
 /* moto_rotateLeft rotate to the left without exceeding
    the boundaries min and max pulses and the motors are reacting as 
    expected */

     /* motors are on hover level rotate to the left normal steps */

     moto_hover();
     temp_copy();
     moto_rotateLeft();

     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);


     temp_copy();
     moto_rotateLeft();

     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

     moto_hover();
     temp_copy();
     moto_rotateLeft();
     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

     leftPulse == MAX_PULSE_LEFT - (NORMAL_STEP * 400);
     rightPulse == MAX_PULSE_RIGHT - (NORMAL_STEP * 400);
     frontPulse == MIN_PULSE_FRONT + (NORMAL_STEP * 400);
     rearPulse == MIN_PULSE_REAR + (NORMAL_STEP * 400);

     temp_copy();
     moto_rotateLeft();
     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);

     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP);  
 
     temp_copy();
     moto_rotateLeft();

     CU_ASSERT(leftPulse == leftP + NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP + NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP - NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP - NORMAL_STEP); 

}

void test_moto_rotateRight(void){

     /* rotate to the right normal steps */
     /* all motors are on hover level*/
     /* the motors are responding as expected and not exceeding the 
        boundaries*/

 /* moto_rotateRight rotate to the right without exceeding
    the boundaries min and max pulses and the motors are reacting as 
    expected */

  /* motors are on hover level rotate to the right normal steps */
       
     moto_hover();
     temp_copy();
     moto_rotateRight();

     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

     temp_copy();
     moto_rotateRight();

     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

     moto_hover();
     temp_copy();
     moto_rotateRight();
     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

     leftPulse == MIN_PULSE_LEFT + (NORMAL_STEP * 140);
     rightPulse == MIN_PULSE_RIGHT + (NORMAL_STEP * 140);
     frontPulse == MAX_PULSE_FRONT - (NORMAL_STEP * 140);
     rearPulse == MAX_PULSE_REAR - (NORMAL_STEP * 140);

     temp_copy();
     moto_rotateRight();
     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

     moto_hover();
     temp_copy();
     moto_rotateRight();
     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

     leftPulse == MIN_PULSE_LEFT + (NORMAL_STEP * 800);
     rightPulse == MIN_PULSE_RIGHT + (NORMAL_STEP * 800);
     frontPulse == MAX_PULSE_FRONT - (NORMAL_STEP * 800);
     rearPulse == MAX_PULSE_REAR - (NORMAL_STEP * 800);

     temp_copy();
     moto_rotateRight();
     CU_ASSERT(leftPulse == leftP - NORMAL_STEP);
     CU_ASSERT(rightPulse == rightP - NORMAL_STEP);
     CU_ASSERT(frontPulse == frontP + NORMAL_STEP);
     CU_ASSERT(rearPulse == rearP + NORMAL_STEP);

}

#ifndef MASTER_TEST_SUITE

/*
 * check_add_ok() gives a print_out on the screen when a test suite or a test
 * has been created, the char** passed to this function should always be in
 * the style:
 *    suite "suite name"
 *    test "test name"
 */
void check_add_ok(char* msg){

    if(CU_get_error() == CUE_SUCCESS){
            fprintf(stdout, "%s created successfully!\n",msg);
    }
    else{
        fprintf(stdout, "failed to create %s\n",msg);
    }
}

/*
 * main() is where the test suites are set up and the tests are added to them
 * This requires that the test functions are created above this point in the
 * file
 */
int main(int argc){
    /* Initialize test registry and act upon the success/failure of it */
    CU_ErrorCode ec = CU_initialize_registry();
    if(ec == CUE_SUCCESS){
        fprintf(stdout, "\ntest register initialized successfully!\n");
    }
    else{
        fprintf(stdout, "Failed to initialize test register");
        return 1;
    }   


    /*--------------------------------------------------------------------*/
    /* Create a test suite for start_stop functions */
    CU_pSuite start_stop = CU_add_suite("start_stop_motors",NULL,NULL);    
    check_add_ok("suite start_stop_motors");

    /* Add appropriate test functions to the start_stop suite */
    CU_add_test(start_stop, "test_moto_startMotors", test_moto_startMotors);
    check_add_ok("test test_moto_startMotors");
    
    CU_add_test(start_stop, "test_moto_stopMotors",
        test_moto_stopMotors);
    check_add_ok("test test_moto_stopMotors");
    
    /*--------------------------------------------------------------------*/
    
    /* Create a test suite for increase/decrease all-functions */
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

     
    /* @uthor Bishare Sufi */

    /* added appropriate test functions to the suite */

    CU_add_test(increase_decrease_all, "test_moto_hover", test_moto_hover);
    check_add_ok("Test test_moto_hover");

    CU_add_test(increase_decrease_all, "test_moto_goForward", 
        test_moto_goForward);
    check_add_ok("Test test_moto_goForward");

    CU_add_test(increase_decrease_all, "test_moto_goBackward",
        test_moto_goBackward);
    check_add_ok("Test test_moto_goBackward");

    CU_add_test(increase_decrease_all, "test_moto_strafeRight",
        test_moto_strafeRight);
    check_add_ok("Test test_moto_strafeRight");

/* added appropriate test functions to the suite */

    CU_add_test(increase_decrease_all, "test_moto_strafeLeft",
        test_moto_strafeLeft);
    check_add_ok("Test test_moto_strafeLeft");
    
    CU_add_test(increase_decrease_all, "test_moto_ rotateLeft",
        test_moto_rotateLeft);
    check_add_ok("Test test_moto_rotateLeft");

    CU_add_test(increase_decrease_all, "test_moto_rotateRight",
        test_moto_rotateRight);
    check_add_ok("Test test_moto_rotateRight");


    
    /*--------------------------------------------------------------------*/

    CU_console_run_tests(); /* control test manually from console */
    //CU_automated_run_tests(); /* run tests automatically */
    //CU_list_tests_to_file(); /* print out to xml-file */
    CU_cleanup_registry(); /* a call to a self explanatory function name ;)*/
}
#endif /* #ifndef MASTER_TEST_SUITE */
