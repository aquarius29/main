#include "CUnit/Basic.h"
#include <string.h>
#include <malloc.h>
#include "../src/arduino/robin_impl_src/sched_scheduler.h"

ProcessData *l_processData;
Process *l_pProcess;
Task *l_pTask_1;
Task *l_pTask_2;

int init_suite(void)
{
    initProcessData();
    l_processData = getProcessData();
    return 0;
}

int clean_suite(void)
{
    if(l_processData != 0)
        cleanProcessData();
    if(l_pProcess != 0)
        endProcess(l_pProcess);
    return 0;
}

/* SUITE_1
* Test cases part of the ProcessData struct data 
*/

/* Test case 1: Test that the processData is correctly initialized */
void testSched1(void)
{
    CU_ASSERT(l_processData->ProcessQueue[0] == 0);
    CU_ASSERT(l_processData->CurrentQueueSize == 0);
    CU_ASSERT(l_processData->IdleProcessToSchedule == 1);
    CU_ASSERT(l_processData->TotalExecutionTime == 0);
}

/* Test case 2: createProcessQueue does not create a processQueue which 
* excides the TIMEFRAME
*/
void testSched2(void)
{
    createProcessQueue();

    /* Make sure that the first process to run is the motor process */
    CU_ASSERT(l_processData->ProcessQueue[0]->Pid == MOTOR_PID);
    CU_ASSERT(l_processData->IdleProcessToSchedule != 0);

    CU_ASSERT(l_processData->CurrentQueueSize != 0);
    CU_ASSERT(l_processData->CurrentQueueSize <= MAX_PROC_ITER);

    CU_ASSERT(l_processData->TotalExecutionTime != 0);
    CU_ASSERT(l_processData->TotalExecutionTime < TIMEFRAME_MS);
}

/* Test case 3: peekProcess should return the 
* valid task att correct layer and not affect the actual queue memory */
void testSched3(void)
{
    int8_t idle = l_processData->IdleProcessToSchedule;
    int8_t size = l_processData->CurrentQueueSize;

    Task *pTask = peekProcess(l_processData->ProcessQueue[0], 0);
    CU_ASSERT(pTask == l_processData->ProcessList[0]->firstTask);
    if(l_processData->ProcessQueue[0]->no_tasks > 1)
    {
        pTask = peekProcess(l_processData->ProcessQueue[0], 1);
        CU_ASSERT(pTask == 
            l_processData->ProcessList[0]->firstTask->nextTask);
    }
    else
    {
        /* Even though the layer goes deeper than the number of tasks
        * the returned task should be correct since the layer should reset
        */
        pTask = peekProcess(l_processData->ProcessQueue[0], 1);
        CU_ASSERT(pTask == l_processData->ProcessList[0]->firstTask);
    }

    /* Make sure the queue wasn't affected by the peek */
    CU_ASSERT(l_processData->IdleProcessToSchedule == idle);
    CU_ASSERT(l_processData->CurrentQueueSize == size);
}

/* Test case 4: Make sure that enqueueProcess functions */
void testSched4(void)
{
    nullQueue();
    Process *l_pProcess = l_processData->ProcessList[0]; /* Motor process */
    l_processData->IdleProcessToSchedule = 1; /* Reset the scheduling */
    enqueueProcess(l_pProcess);

    CU_ASSERT(l_processData->CurrentQueueSize == 1);
    CU_ASSERT(l_processData->ProcessQueue[0] == l_pProcess);
}

/* Test case 5: nullQueue properly nulls the processQueue */
void testSched5(void)
{
    nullQueue();
    CU_ASSERT(l_processData->TotalExecutionTime == 0);
    CU_ASSERT(l_processData->CurrentQueueSize == 0);
    CU_ASSERT(l_processData->IdleProcessToSchedule != 0);
    CU_ASSERT(l_processData->ProcessQueue[0] == 0);
}

/* SUITE_2
* Test cases for functions that handle processes 
*/

/* Test case 6: createProcess creates an empty process */
void testSched6(void)
{
    l_pProcess = createProcess("Test process", 99);
    CU_ASSERT(l_pProcess != 0);
    CU_ASSERT(l_pProcess->Pid == 99);
    CU_ASSERT(l_pProcess->no_tasks == 0);
    CU_ASSERT(l_pProcess->firstTask == 0);
    CU_ASSERT(l_pProcess->lastTask == 0);
    CU_ASSERT(l_pProcess->idleTask == 0);
    CU_ASSERT(l_pProcess->priority == 0); //priority?
    CU_ASSERT(!strncmp(l_pProcess->name, "Test process", sizeof("Test process"))); //name?
}

int16_t testFuncPtr(void)
{
    return 255; /* Some value just to test other than 0 */
}

/* Test case 7: enqueueTask properly enqueues tasks both for process and linked tasks */
void testSched7(void)
{
    if(l_pProcess != 0)
    {
        l_pTask_1 = createTask("Test task 1", &testFuncPtr, 5);
        CU_ASSERT(!strncmp(l_pTask_1->name, 
            "Test task 1", sizeof("Test task 1")));
        CU_ASSERT(l_pTask_1->executionTime == 5);
        CU_ASSERT(l_pTask_1->functionPointer == &testFuncPtr);
        CU_ASSERT(l_pTask_1->nextTask == 0);

        enqueueTask(l_pProcess, l_pTask_1);
        CU_ASSERT(l_pProcess->no_tasks == 1);
        CU_ASSERT(l_pProcess->firstTask == l_pTask_1);
        CU_ASSERT(l_pProcess->firstTask == l_pProcess->lastTask 
            && l_pProcess->firstTask == l_pProcess->idleTask);

        l_pTask_2 = createTask("Test task 2", &testFuncPtr, 10);
        enqueueTask(l_pProcess, l_pTask_2);
        CU_ASSERT(l_pProcess->no_tasks == 2);
        CU_ASSERT(l_pProcess->lastTask == 
            l_pTask_2 && l_pProcess->firstTask != l_pTask_2);
        CU_ASSERT(l_pProcess->idleTask == l_pProcess->firstTask);

        CU_ASSERT(l_pTask_1->nextTask != 0);
        CU_ASSERT(l_pTask_1->nextTask == l_pTask_2);
    }
}

void testSched8(void)
{
    if(l_pProcess != 0 && l_pProcess->no_tasks > 1)
    {
        Task *idle = l_pProcess->idleTask;
        /*int16_t return = */runIdleTask(l_pProcess); 
        /* does not return any value yet */
        CU_ASSERT(l_pProcess->idleTask != idle);
        CU_ASSERT(l_pProcess->firstTask == idle);
    }
}

int main(void)
{
    CU_pSuite pSuite1 = 0; /* Suite handles the ProcessData */
    CU_pSuite pSuite2 = 0;

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite1 = CU_add_suite("ProcessData | Suite_1", init_suite, clean_suite);
   pSuite2 = CU_add_suite("Process and Task | Suite_2", init_suite, clean_suite);
   if (NULL == pSuite1 || NULL == pSuite2) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (0 == CU_add_test(pSuite1, "test of initProcessData", testSched1)
       || 0 == CU_add_test(pSuite1, "test of createProcessQueue", testSched2)
        || 0 == CU_add_test(pSuite1, "test of peekProcess", testSched3)
        || 0 == CU_add_test(pSuite1, "test of enqueueProcess", testSched4)
        || 0 == CU_add_test(pSuite1, "test of nullQueue", testSched5)
        || 0 == CU_add_test(pSuite2, "test of createProcess", testSched6)
        || 0 == CU_add_test(pSuite2, "test of create & enqueueTask", testSched7)
        || 0 == CU_add_test(pSuite2, "test of runIdleTask", testSched8))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}