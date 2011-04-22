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
    #ifdef PC
        clock_t start;
        clock_t stop;
        double time = 0.0;
    #endif

    ProcessData *processData = get_process_data();
    Process** processQueue = processData->processQueue;

    for(k = 0; k < 500; k++) //TODO: 15?
    {
        int i;
        #ifdef PC
            assert((start = clock()) != -1);
        #endif /* PC */
        create_process_queue();
        printf("Running processes\n==================\n");
        for(i = 0; i < processData->currentQueueSize; i++)
        {
            run_process(i);
        }
        #ifdef PC
            stop = clock();
            time = (double)(stop-start);

            printf("ExecutionTime: %f\n", time);

        #ifdef WINDOWS
            if(50 - time > 0)
            {
                printf("Synchronize: %f\n", (50 - time));
                Sleep(50 - time);
            }
            else
            {
                printf("Failed to keep time constraint!\n");
                printf("Shutting down scheduler...");
                break;
            }
        #else 
            usleep(time - 50);
        #endif /* WINDOWS */
        #endif /* PC */
        printf("\n");
    }
}

int main(void){
    init();
    run();
    clean_process_data();
    getch();
    return 0;
}