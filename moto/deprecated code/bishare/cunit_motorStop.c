/*@uthor Bishare_sufi*/
#include <stdio.h>
#include "CUnit/CUnit.h"
#include "../src/motor_stop.h"

/* run cunit with gcc cunit_motorStop.c ../src/motor_stop.c -DPC -o 
cunit_motorStop -lcunit */   /* ./cunit_motorStop */

void test_motor(void){
CU_ASSERT(stop() == 1); /* one assert test for stop function */
}

void test_check(char* msg){
if(CU_get_error() == CUE_SUCCESS){
  fprintf(stdout, "%s passed successfully!\n", msg);
}
else
{
    fprintf(stdout, "%s failed\n", msg);
return;
}
}


/* main function*/

int main(int argc){
CU_ErrorCode er = CU_initialize_registry();
if(er == CUE_SUCCESS){
    fprintf(stdout, "\nTest register initialized successfully!\n");
   }

else{
     fprintf(stdout, "Failed to initialize test register");
return;
}

/* add motor stop test */

   CU_pSuite stop = CU_add_suite("Stop_motor", NULL, NULL); 
   test_check("Suite stop motor");

   CU_add_test(stop, "Test stop motor", test_motor);
   test_check("Test test_motor");

   CU_console_run_tests();
   CU_cleanup_registry();
}
