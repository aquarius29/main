#include <stdio.h>
#include "sched_scheduler.h"

void init(void)
{
    initProcessData();
}

void runtime(void)
{
    int k;
    for(k = 0; k < 2; k++)
    {
        int i;
        Process** processQueue = getQueuePtr();
        createProcessQueue();
        printf("Running processes\n==================\n");
        for(i = 0; i < *getCurrentQueueSize(); i++)
        {
            runIdleTask(processQueue[i]);
        }
        printf("\n");
    }
}

int main(void)
{
    init();
    runtime();
    return 0;
}