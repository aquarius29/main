/*@uthor Bishare_sufi*/
#include <stdio.h>
#include "CUnit/CUnit.h"
#include "../src/extract_states.h"

/* run cunit with gcc cunit_extractStates.c ../src/exract_states.c -DPC -o 
cunit_extractStates  -lcunit */   /* ./cunit_extractStates */

void test_motors(void){

/*asserts for generate function */
/* here we test only one function, because this code is not used*/

CU_ASSERT(generate_value_Con_motor(FORWARD) == FORWARD);
CU_ASSERT(generate_value_Con_motor(BACKWARD) == BACKWARD);
CU_ASSERT(generate_value_Con_motor(TURN_LEFT) == TURN_LEFT);
CU_ASSERT(generate_value_Con_motor(TURN_RIGHT) == TURN_RIGHT);

}

void test_check(char* msg){
if(CU_get_error() == CUE_SUCCESS){
  fprintf(stdout, "Passed successfully!\n", msg);
}                                                   
else{                                               
     fprintf(stdout, "%s failed\n", msg);
}
}

/* main function for suite test*/

int main(int argc){
CU_ErrorCode erc = CU_initialize_registry();
if(erc == CUE_SUCCESS){
    fprintf(stdout,"\ntest register initialized successfully!\n");  
  }
else{
    fprintf(stdout, "failed to initialize test register");
return;
}

/* add test for the states */

   CU_pSuite generate_value_Con_motor = CU_add_suite("Extract states", NULL, NULL);
   test_check("Suite extract_states");

   CU_add_test(generate_value_Con_motor, "Test motors", test_motors);
   test_check("Test test_motors");

   CU_console_run_tests();
   CU_cleanup_registry();

}
