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
#include <stdint.h>

#ifdef WINDOWS
#include <Windows.h> /* for windows timing functions */
#else
#include <unistd.h>
#endif /* WINDOWS */

#elif ARDUINO
/* ARDUINO stuff here */
#endif /* PC ARDUINO */

#include "sched_batman_scheduler.h"

void sched_batman_init(void) {
    init_process_data();
}

void sched_batman_run(void) {
    int16_t k;
    double time;
    ProcessData *processData;
    Process ** processQueue;
    int16_t timeFrame;
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

    timeFrame = TIMEFRAME_MS;

    processData = get_process_data();
    processQueue = processData->processQueue;

#ifdef PC
    printf("starting scheduler: running processes\n");
#endif /* PC */
    for(k = 0; k < 10; k++) //TODO: iterations?
    {
        int16_t i;
        int16_t syncTime;
#ifdef PC
        assert((start = clock()) != -1);
#endif /* PC */

        create_process_queue(timeFrame);

        for(i = 0; i < processData->currentQueueSize; i++){
            run_process(i);
        }
#ifdef PC
        stop = clock();
        time = (double)(stop-start);

        syncTime = (int)(timeFrame - time);
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
                fprintf(file, "Sync. Time: %d ms\n", (syncTime));
            }
            else
            {
                fprintf(file, "Timeframe was exceded by: %d ms\n", (syncTime * -1));
            }
        #endif /* LOG */

        if(syncTime >= 0)
        {
#ifdef WINDOWS
            Sleep(syncTime);
#else
            usleep(syncTime);
#endif /* WINDOWS */
            timeFrame = TIMEFRAME_MS;
        }
        else if((syncTime * -1) > 1000)
        {
            /* DEADLINE has been exceeded
            /* System faulure: THIS IS DANGEROUS */
            break;
        }
        else 
        {
            /* If the timeframe was exceeded with more time than what fits in the TIMEFRAME
            * then the timeframe should be set to the time of the last timeframe since the other
            * timeframes will equal to 0 there is no point in running them */
            timeFrame = (syncTime * -1) % TIMEFRAME_MS; /* Setting the (last) timeframe  */
        }
#elif ARDUINO
        /* TODO: Put arduino timing logic here OR 
        * change time functions in PC version with #ifdef's */
#endif /* ARDUINO */

#ifdef PC
        printf(".");
#endif /* PC */
#ifdef LOG
        fprintf(file, "==================\n");
#endif
    }
    #ifdef LOG
    fprintf(file, "******************************************\n");
    fclose(file);
    #endif
#ifdef PC
    printf("\n\nShutting down scheduler............");
#endif
    clean_process_data();
#ifdef PC
    printf("DONE\n");
#endif
}

/*
int main(void){
    init();
    run();
    clean_process_data();
    return 0;
}
*/