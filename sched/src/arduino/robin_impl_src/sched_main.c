#include <stdio.h>
#include "sched_scheduler.h"

void init(void){
    initProcessData();
}

void run(void){
    int k;
    ProcessData *processData = getProcessData();
    Process** processQueue = processData->ProcessQueue;

    for(k = 0; k < 5; k++) //TODO: 2?
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
    getch();
    return 0;
}