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
*/

#include <stdio.h>
#ifdef PC
#include <assert.h>
#include <time.h>

#ifdef WINDOWS
#include <Windows.h> /* for windows timing functions */
#else
#include <unistd.h>
#endif /* WINDOWS */

#endif /* PC */

#include "sched_batman_scheduler.h"


void init(void) {
    init_process_data();
}

void run(void) {
    int k;
    double time;
    int16_t excessTime;
    ProcessData *processData;
    Process ** processQueue;
    #ifdef PC
        clock_t start;
        clock_t stop;

        #ifdef LOG
        FILE *file;
        file = fopen("scheduler_log.txt", "a+");
            fprintf(file, "SCHEDULER LOG:\n****************************\n");
        #endif /* LOG */

        time = 0.0;
    #endif

    excessTime = 0;

    processData = get_process_data();
    processQueue = processData->processQueue;

    for(k = 0; k < 500; k++) //TODO: 15?
    {
        int16_t i;
        int16_t syncTime;
        #ifdef PC
            assert((start = clock()) != -1);
        #endif /* PC */
        create_process_queue(excessTime);
        printf("Running processes\n==================\n");
        for(i = 0; i < processData->currentQueueSize; i++)
        {
            run_process(i);
        }
        #ifdef PC
            stop = clock();
            time = (double)(stop-start);

            printf("ExecutionTime: %d\n", (int)time);
            syncTime = (int)(50 - time);
            #ifdef LOG
                fprintf(file, "Ran: %d processes\n", 
                    processData->currentQueueSize);
                for(i = 0; i < processData->currentQueueSize; i++)
                {
                    fprintf(file, "PID: %d\n", processData->processQueue[i]->Pid);
                }
                fprintf(file, "Total Exection Time: %d ms\n", (int)(time));
                if(syncTime > 0)
                {
                    fprintf(file, "Sync. Time: %d ms\n", (syncTime - excessTime));
                }
                else
                {
                    fprintf(file, "Timeframe was excided by: %d ms\n", (syncTime * -1));
                }
            #endif /* LOG */


            if(syncTime > 0)
            {
                printf("Synchronize: %d\n", syncTime);
                #ifdef WINDOWS
                    if(syncTime - excessTime > 0)
                    {
                        Sleep(syncTime - excessTime);
                    }
                #else
                    usleep(50 - time);
                #endif /* WINDOWS */
                excessTime = 0;
            }
            else
            {
                printf("Failed to keep time constraint!\n");
                excessTime = syncTime * -1; /* Making it non-negative */
                printf("Correcting next iteration with: %d\n", excessTime);
            }
        #endif /* PC */
        #ifdef ARDUINO
            /* TODO: Put arduino timing logic here */
        #endif
        printf("\n");
        #ifdef LOG
            fprintf(file, "==================\n");
        #endif
    }
    #ifdef LOG
        fclose(file);
    #endif
}

int main(void){
    init();
    run();
    clean_process_data();
    getch();
    return 0;
}