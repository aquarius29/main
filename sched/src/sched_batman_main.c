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
*               2011-05-10 - Made arduino debugging and code cleaning
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

#elif defined ARDUINO
#include "WProgram.h"
#include "stab_interface.h"
#include "moto_interface.h"
#include "mov_interface.h"
#endif /* PC ARDUINO */

#include "sched_batman_scheduler.h"

#ifdef PC

#ifdef WINDOWS
#define SLEEP(a) Sleep(a)
#else
#define SLEEP(a) usleep(a)
#endif

#define GET_CLOCK() clock()
#define TIME_TYPE clock_t

#ifdef LOG
#define ITER_END() printf("."); fprintf(file, "==================\n")
#else
#define ITER_END() printf(".")
#endif

#ifdef DEBUG
#define DEBUG_MSG(msg)
#define DEBUG_MSG_VAR(var, type)
#else
#define DEBUG_MSG(msg)
#define DEBUG_MSG_VAR(var, type)
#endif

#define MSG_VAR(time, type) printf("%d\n", time)

#elif defined ARDUINO
#define SLEEP(a) delay(a)
#define GET_CLOCK() millis()
#define TIME_TYPE uint32_t
#define ITER_END()

#ifdef DEBUG
#define DEBUG_MSG(msg) Serial.println(msg)
#define DEBUG_MSG_VAR(var, type) Serial.println(var, type)
#else
#define DEBUG_MSG(msg)
#define DEBUG_MSG_VAR(var, type)
#endif

#define MSG_VAR(time, type) Serial.println(time, type)

#endif

/* 
* Init function initializes all processes 
**/
void sched_batman_init(void) 
{
#ifdef ARDUINO
    init();
    Serial.begin(9600);
#endif
    init_process_data();
}

/* 
* Used for deallocating dynamic memory allocated for
* the scheduler. Mostly used for PC 
**/
void shutdown_scheduler(void)
{
#ifdef PC
    printf("\n\nShutting down scheduler............");
#endif
    clean_process_data();
#ifdef PC
    printf("DONE\n");
#endif
}

/*
* Used for logging the scheduler for the PC. 
* Prints out number of processes ran, total execution time,
* synchronization time and if the timeframe was exceeded and by how much
*/
#ifdef PC
#ifdef LOG
void print_iteration_status(FILE * file, int32_t syncTime, double time)
{
    int i;
    ProcessData * pProcessData = get_process_data();


    fprintf(file, "Ran: %d processes\n", pProcessData->currentQueueSize);
    for(i = 0; i < pProcessData->currentQueueSize; i++)
    {
        fprintf(file, "PID: %d\n", pProcessData->processQueue[i]->Pid);
    }
    fprintf(file, "Total Execution Time: %d ms\n", (int)(time));
    if(syncTime > 0)
    {
        fprintf(file, "Sync. Time: %d ms\n", (syncTime));
    }
    else
    {
        fprintf(file, 
            "Timeframe was exceded by: %d ms\n", (syncTime * -1));
    }
}
#endif
#endif

/* 
 * This function acts as a profiler. 
 * The profiler mainly used for measuring time on the arduino 
 **/
#ifdef ARDUINO
void sched_batman_profile(void)
{
  TIME_TYPE start;
  TIME_TYPE stop;
  int32_t time;
  ProcessData * pProcessData = get_process_data();
  
  while(1)
    {
      start = micros();
      pProcessData->processList[1]->idleTask->functionPointer();
      stop = micros();
      time = stop - start;
#ifdef ARDUINO
      Serial.println(time, DEC);
#elif defined PC
      printf("%d\n", time);
#endif
      SLEEP(1000);
    }
}
#endif
/*
* This function is the actual process loop which run all the processes.
* Each iteration consists of:
* 
* A process queue is constructed with idle processes to be scheduled,
* the queue's size and content of processes depend of the available
* for the current timeframe and idle processes exection time.
*
* The process queue runs all processes.
*
* Total execution time is calculated.
*
* If the total execution time exceeds the value of the timeframe 
* then the next timeframe is deducted by the exceeding time.
*
* If the total execution time did not exceed the value of the
* timeframe then the processes waits (timeframe - total execution time)
* in order to synchronous.
*
**/
void sched_batman_run(void)
{
    int16_t i;
    int32_t time;
    ProcessData * processData;
    Process ** processQueue;
    int16_t timeFrame;
    TIME_TYPE start;
    TIME_TYPE stop;

#ifdef PC
#ifdef LOG
    FILE * file;
    file = fopen("scheduler_log.txt", "a+");
    fprintf(file, "SCHEDULER LOG\n****************************\n");
#endif /* LOG */
#endif /* PC */

    time = 0.0;
    timeFrame = TIMEFRAME_MS;

    processData = get_process_data();
    processQueue = processData->processQueue;

#ifdef PC
    printf("Starting scheduler: running processes\n");
#endif

    /* 
    * Delay of 20 seconds to plug in the 
    * motors before any commands can start the motors
    **/
#ifdef ARDUINO
    Serial.println("System is ready, PLUG IN BATTERY!");
    SLEEP(30000); /* To be removed? */
#endif

    /* This loop is the main scheduling loop */
#ifdef PC
    for(i = 0; i < 500; i++)
#elif defined ARDUINO
    while(1)
#endif
    {
        int16_t j;
        int16_t syncTime;

        DEBUG_MSG("iter start");
        //DEBUG_MSG("Getting (start)clock");

        start = GET_CLOCK();
        
        //DEBUG_MSG_VAR(start, DEC);
        //DEBUG_MSG("Creating process queue");

        create_process_queue(timeFrame); /* Creates a process queue */

        //DEBUG_MSG("Running processes");

        /* Runs all the processes in the queue */
        for(j = 0; j < processData->currentQueueSize; j++)
        {
            run_process(j);
        }

        //DEBUG_MSG("Ran all processes, calculating sync time");
        //DEBUG_MSG("Getting (stop)clock");

        stop = GET_CLOCK();
        time = (int32_t)(stop-start);

        /*DEBUG_MSG_VAR(start, DEC);
        DEBUG_MSG_VAR(stop, DEC);
        DEBUG_MSG("****************************");
        DEBUG_MSG_VAR(time, DEC);
        DEBUG_MSG_VAR(processData->currentQueueSize, DEC);*/

        /* Calculates the time needed to synch */
        syncTime = (int)(timeFrame - time); 
        //DEBUG_MSG("Sync time is...");
        //  DEBUG_MSG_VAR(syncTime, DEC);

#ifdef PC
#ifdef LOG
        print_iteration_status(file, syncTime, time);
#endif /* LOG */
#endif /* PC */

        DEBUG_MSG("Checking if timeframe was exceeded");
        if(syncTime >= 0)
        {
            SLEEP(syncTime);
            timeFrame = TIMEFRAME_MS;
        }
        else if((syncTime * -1) > 1000)
        {
            /* 
            * DEADLINE has been exceeded
            * System faulure: THIS IS DANGEROUS
            * PANIC MODE? 
            * */
#ifdef ARDUINO
            analogWrite(13, 0);
#endif
        }
        else 
        {
            /* If the timeframe was exceeded with more time 
            * than what fits in the TIMEFRAME then the timeframe should be
            * set to the time of the last timeframe since the other
            * timeframes will equal to 0 there is no point in running them */

            syncTime *= -1;

            /* Setting the (last) timeframe  */
            if(syncTime > TIMEFRAME_MS)
            {
                syncTime = TIMEFRAME_MS % syncTime;
            }
#ifdef DEBUG

#else
            timeFrame = TIMEFRAME_MS - syncTime;
#endif
        }
#ifdef ARDUINO
        analogWrite(13, 255);
#endif
        ITER_END();
    }
#ifdef PC
#ifdef LOG
    fprintf(file, "******************************************\n");
    fclose(file);
#endif /* LOG */
#endif /* PC */

    shutdown_scheduler();
}
