/*Created by Magnus Bergqvist*/

#include <stdio.h>
#include "CUnit/CUnit.h"
#include "motorcontrol.h"

/* compile with something like this:  gcc function.c -o function -lcunit */

int plus_one(int num){
    if(num+1 > 0){
        return num+1;
    }
    else{
        return 0;
    }
}

void test_increaseMotorPulse(void){
    CU_ASSERT(increaseMotorPulse(1,0)==3);
    CU_ASSERT(increaseMotorPulse(1,55)==58);
    CU_ASSERT(increaseMotorPulse(1,252)==255);
    CU_ASSERT(increaseMotorPulse(1,254)==255);
    CU_ASSERT(increaseMotorPulse(1,255)==255);
}

void test_increaseMotorPulseX2(void){
    CU_ASSERT(increaseMotorPulseX2(1,0)==6);
    CU_ASSERT(increaseMotorPulseX2(1,55)==61);
    CU_ASSERT(increaseMotorPulseX2(1,249)==255);
    CU_ASSERT(increaseMotorPulseX2(1,254)==255);
    CU_ASSERT(increaseMotorPulseX2(1,255)==255);
}

void test_decreaseMotorPulse(void){
    CU_ASSERT(decreaseMotorPulse(1,0)==3);
    CU_ASSERT(decreaseMotorPulse(1,3)==3);
    CU_ASSERT(decreaseMotorPulse(1,2)==3);
    CU_ASSERT(decreaseMotorPulse(1,55)==52);
    CU_ASSERT(decreaseMotorPulse(1,255)==252);
}

void test_decreaseMotorPulseX2(void){
    CU_ASSERT(decreaseMotorPulseX2(1,0)==3);
    CU_ASSERT(decreaseMotorPulseX2(1,6)==3);
    CU_ASSERT(decreaseMotorPulseX2(1,2)==3);
    CU_ASSERT(decreaseMotorPulseX2(1,55)==49);
    CU_ASSERT(decreaseMotorPulseX2(1,255)==249);
}


void check_add_ok(char* msg){

    if(CU_get_error() == CUE_SUCCESS){
            fprintf(stdout, "%s created successfully!\n",msg);
    }
    else{
        fprintf(stdout, "failed to create %s\n",msg);
        return;
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
/* add motor control increase tests */

    CU_pSuite increase = CU_add_suite("increase_motor",NULL,NULL);    
    check_add_ok("suite increase motor");

    CU_add_test(increase, "TestIncreaseMotorPulse", test_increaseMotorPulse);
    check_add_ok("test TestIncreaseMotorPulse");
    
    CU_add_test(increase, "TestIncreaseMotorPulseX2",
        test_increaseMotorPulseX2);
    check_add_ok("test TestIncreaseMotorPulseX2");
    
/***************************************************************************/
/* add motor control decrease tests*/

    CU_pSuite decrease = CU_add_suite("decrease_motor",NULL,NULL);    
    check_add_ok("suite decrease motor");

    CU_add_test(decrease, "TestDecreaseMotorPulse", test_decreaseMotorPulse);
    check_add_ok("test TestDecreaseMotorPulse");
    
    CU_add_test(decrease, "TestDecreaseMotorPulseX2",
        test_decreaseMotorPulseX2);
    check_add_ok("test TestDecreaseMotorPulseX2");
    
/***************************************************************************/

    CU_console_run_tests();
    CU_cleanup_registry();
}
