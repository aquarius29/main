/*!
*   @file sched_main.c
*   
*   @brief Main scheduling loop.
*
*   @author Anders Treptow
*   @date 2011-04-19
*
*   @history    2011-03-29 wrote prototype
*               2011-04-12 updated process run structure
*/

#include <stdio.h>

#ifdef PC
#include <time.h>
#endif

#include "sched_scheduler.h"

void init(void) {
    initProcessData();
}

void run(void) {
    int k;
    ProcessData *processData = getProcessData();
    Process** processQueue = processData->ProcessQueue;

    for(k = 0; k < 15; k++) //TODO: 15?
    {
        int i;
        createProcessQueue();
        printf("Running processes\n==================\n");
        for(i = 0; i < processData->CurrentQueueSize; i++)
        {
            runProcess(i);
        }
        printf("\n");
    }
}

int main(void){
    init();
    run();
    cleanProcessData();
    return 0;
}