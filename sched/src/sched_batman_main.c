/*!
*   @file sched_main.c
*   
*   @brief Main scheduling loop.
*
*   @author Anders Treptow
*   @date 2011-04-19
*
*   @history    2011-03-29 - wrote prototype
*               2011-04-12 - updated process run structure
*               2011-04-22 - wrote timing logic and logging
*/

#ifdef PC
#include <assert.h>
#include <time.h>
#include <stdio.h>

#ifdef WINDOWS
#include <Windows.h> /* for windows timing functions */
#else
#include <unistd.h>
#endif /* WINDOWS */

#elif
/* ARDUINO stuff here */
#endif /* PC ARDUINO */

#include "sched_batman_scheduler.h"

void sched_batman_init(void) {
    init_process_data();
}

void sched_batman_run(void) {
    int16_t k;
    double time;
    int8_t excessTime;
    ProcessData *processData;
    Process ** processQueue;
#ifdef PC
    clock_t start;
    clock_t stop;

#ifdef LOG
    FILE *file;
    file = fopen("scheduler_log.txt", "a+");
        fprintf(file, "SCHEDULER LOG\n****************************\n");
#endif /* LOG */

    time = 0.0;
#endif

    excessTime = 0;

    processData = get_process_data();
    processQueue = processData->processQueue;

#ifdef PC
    printf("starting scheduler: running processes\n");
#endif /* PC */
    for(k = 0; k < 500; k++) //TODO: iterations?
    {
        int16_t i;
        int16_t syncTime;
#ifdef PC
        assert((start = clock()) != -1);
#endif /* PC */
        create_process_queue(excessTime);
#ifdef DEBUG
        printf("Running processes\n==================\n");
#endif /* DEBUG */
        for(i = 0; i < processData->currentQueueSize; i++){
            run_process(i);
        }
    #ifdef PC
        stop = clock();
        time = (double)(stop-start);

        #ifdef DEBUG
            printf("ExecutionTime: %d\n", (int)time);
        #endif /* DEBUG */
        syncTime = (int)(TIMEFRAME_MS - time);
        #ifdef LOG
            fprintf(file, "Ran: %d processes\n", 
                processData->currentQueueSize);
            for(i = 0; i < processData->currentQueueSize; i++)
            {
                fprintf(file, "PID: %d\n", processData->processQueue[i]->Pid);
            }
            fprintf(file, "Total Execution Time: %d ms\n", (int)(time));
            if(syncTime > 0)
            {
                fprintf(file, "Sync. Time: %d ms\n", (syncTime - excessTime));
            }
            else
            {
                fprintf(file, "Timeframe was exceded by: %d ms\n", (syncTime * -1));
            }
        #endif /* LOG */

        if(syncTime > 0)
        {
#ifdef DEBUG
                printf("Synchronize: %d\n", syncTime);
#endif /* DEBUG */
            if(syncTime - excessTime > 0 && syncTime - excessTime < TIMEFRAME_MS)
            {
#ifdef WINDOWS
                Sleep(syncTime - excessTime);
#else
                usleep(syncTime - excessTime);
#endif /* WINDOWS */
            }
            else
            {
                /*TODO: Something is very wrong...*/
            }
               
            excessTime = 0; /* Reset excessTime */
        }
        else 
        {
#ifdef DEBUG
            printf("Correcting next iteration with: %d\n", excessTime);
            printf("Failed to keep time constraint!\n");
#endif
            excessTime = syncTime * -1; /* Making it non-negative */
        }
#endif /* PC */
#ifdef ARDUINO
        /* TODO: Put arduino timing logic here */
#endif
#ifdef DEBUG
        printf("\n");
#elif PC
        printf(".");
#endif /* DEBUG PC */
#ifdef LOG
        fprintf(file, "==================\n");
#endif
    }
    #ifdef LOG
    fprintf(file, "******************************************\n");
    fclose(file);
    #endif
    clean_process_data();
}

/*
int main(void){
    init();
    run();
    clean_process_data();
    return 0;
}
*/