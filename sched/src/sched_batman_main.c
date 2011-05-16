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
#include <time.h>
#include <stdio.h>
#include <stdint.h>

#ifdef WINDOWS
#include <Windows.h> /* for windows timing functions */
#else
#include <unistd.h>
#endif /* WINDOWS */

#elif ARDUINO
#include "WProgram.h"
#endif /* PC ARDUINO */

#include "sched_batman_scheduler.h"

void sched_batman_init(void) {
#ifdef ARDUINO
    
#endif
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

#elif ARDUINO
    int32_t start;
    int32_t stop;

#endif /* PC ARDUINO */

    time = 0.0;

    timeFrame = TIMEFRAME_MS;

    processData = get_process_data();
    processQueue = processData->processQueue;

#ifdef PC
    printf("starting scheduler: running processes\n");
#endif /* PC */

    //for(k = 0; k < 500; k++) //TODO: iterations?
    while(1)
    {
        int16_t i;
        int16_t syncTime;
#ifdef PC
        start = clock();
#elif ARDUINO

        analogWrite(13, 255);
        delay(1000);
        analogWrite(13, 0);
        delay(1000);

        start = millis();

#endif /* PC ARDUINO */

        create_process_queue(timeFrame);

        for(i = 0; i < processData->currentQueueSize; i++)
        {
            run_process(i);
        }
#ifdef PC
        stop = clock();
#elif ARDUINO
        stop = millis();
#endif
        time = (double)(stop-start);

        syncTime = (int)(timeFrame - time);
#ifdef PC
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
#endif

        if(syncTime >= 0)
        {
#ifdef PC
#ifdef WINDOWS
            Sleep(syncTime);
#else
            usleep(syncTime);
#endif /* WINDOWS */
#elif ARDUINO
            
            delay(syncTime);
#endif /* PC */
            timeFrame = TIMEFRAME_MS;
        }
        else if((syncTime * -1) > 1000)
        {
            /* DEADLINE has been exceeded
            /* System faulure: THIS IS DANGEROUS */
            //break;
        }
        else 
        {
            /* If the timeframe was exceeded with more time than what fits in the TIMEFRAME
            * then the timeframe should be set to the time of the last timeframe since the other
            * timeframes will equal to 0 there is no point in running them */
            timeFrame = (syncTime * -1) % TIMEFRAME_MS; /* Setting the (last) timeframe  */
        }

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