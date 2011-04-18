#include <stdio.h>

#ifdef PC
#include <time.h>
#endif

#include "sched_scheduler.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void init(void){
    initProcessData();
}

void run(void){
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
    _CrtDumpMemoryLeaks();
    getch();
    return 0;
}