#include "CUnit/Basic.h"
#include "../src/arduino/robin_impl_src/sched_scheduler.h"

ProcessData *l_processData;

/* Set up and clean up test suite */
int init_suite(void)
{
    initProcessData();
    processData = sched_processData;
    return 0;
}

int clean_suite(void) 
{
    endProcesses();
    return 0;
}

/* Assert that processData struct is nulled and ready after init */
void testSched1(void) 
{
    CU_ASSERT(l_processData->ProcessQueue == 0);
    CU_ASSERT(l_processData->CurrentQueueSize == 0);
    CU_ASSERT(l_processData->IdleProcess == 1); //Idle process should be 1 at init
}
