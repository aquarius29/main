#include "CUnit/Basic.h"
#include "../src/arduino/robin_impl_src/sched_scheduler.h"

ProcessData *l_processData;

int init_suite(void)
{
    initProcessData();
    l_processData = getProcessData();
    return 0;
}

int clean_suite(void)
{
    cleanProcessData();
    return 0;
}

/* Test case 1: The processData is correctly initialized */
void testSched1(void)
{
    CU_ASSERT(l_processData->ProcessQueue[0] == 0);
    CU_ASSERT(l_processData->LastProcess == 0);
    CU_ASSERT(l_processData->IdleProcess == 1);
    CU_ASSERT(l_processData->TotalExecutionTime == 0);
}

/* Test case 2: createProcessQueue does not create a processQueue which 
* excides the TIMEFRAME
*/
void testSched2(void)
{
    createProcessQueue();
    CU_ASSERT(l_processData->TotalExecutionTime != 0);
    CU_ASSERT(l_processData->TotalExecutionTime < 50);
}

/* Test case 3: peekIdleProcess should return the valid idle process */
void testSched3(void)
{
    Process *pProcess = peekIdleProcess();
    CU_ASSERT(pProcess->Pid == MOTOR_PID);
    printf("%d\n", pProcess->Pid);
}

/* Test case 4: nullQueue properly nulls the processQueue */
void testSched4(void)
{
    nullQueue();
    CU_ASSERT(l_processData->TotalExecutionTime == 0);
    CU_ASSERT(l_processData->CurrentQueueSize == 0);
    CU_ASSERT(l_processData->LastProcess != 0);
}

int main(void)
{
    CU_pSuite pSuite = 0;

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (0 == CU_add_test(pSuite, "test of initProcessData", testSched1)
       || 0 == CU_add_test(pSuite, "test of createProcessQueue", testSched2)
           || 0 == CU_add_test(pSuite, "test of peekIdleProcess", testSched3)
               || 0 == CU_add_test(pSuite, "test of nullQueue", testSched4))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}