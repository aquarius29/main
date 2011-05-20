/***************************************************************************
 * Copyright (C) 2011  Anders Treptow
 * 
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

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
*               2011-05-19 - added license
*/
#include <stdint.h>

#ifdef PC
#include <time.h>
#include <stdio.h>

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

#define PRINT_STRING(string) printf(string)

#ifdef DEBUG
#define DEBUG_MSG(msg) PRINT_STRING(msg)
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

#define PRINT_STRING(string) Serial.println(string)

#ifdef DEBUG
#define DEBUG_MSG(msg) PRINT_STRING(msg)
#define DEBUG_MSG_VAR(var, type) Serial.println(var, type)
#else
#define DEBUG_MSG(msg)
#define DEBUG_MSG_VAR(var, type)
#endif

#define MSG_VAR(time, type) Serial.println(time, type)

#endif

/*!
*   @brief  Init function initializes all processes.
*   
*   @return Will return 0 if everything was initialized \n
*   properly, otherwise 1.
*/
int16_t sched_batman_init(void){
#ifdef ARDUINO
    init();
    Serial.begin(9600);
#endif
    if(init_process_data() == 0){ /*0 == EXIT_SUCCESS*/
        return 0; /*EXIT_SUCCESS*/
    }
    else{
        return 1; /*EXIT_FAILURE*/
    }
}

/*! 
*   @brief  Used for deallocating dynamic memory allocated for \n
*   the scheduler. Mostly used for PC 
*/
void shutdown_scheduler(void){
    PRINT_STRING("\n\nShutting down scheduler............");
    clean_process_data();
    PRINT_STRING("DONE\n");
}

/*!
*   @brief  Used for logging the scheduler for the PC.\n
*   Prints out number of processes ran, total execution time,\n
*   synchronization time and if the timeframe was exceeded and by how much
*
*   @param  file Pointer to a FILE to write to.
*   @param  syncTime The time that was need to synchronize.
*   @param  time    The total execution time for the iteration.
*/
#ifdef PC
#ifdef LOG
void print_iteration_status(FILE * file, int32_t syncTime, double time){
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

/*!
*   @brief  This function acts as a profiler. \n
*   The profiler is mainly used for measuring time on the arduino.
*/
void sched_batman_profile(void){
    TIME_TYPE start;
    TIME_TYPE stop;
    int32_t time;
    ProcessData * pProcessData = get_process_data();

    while(1){
        start = GET_CLOCK();
        pProcessData->processList[1]->idleTask->functionPointer();
        stop = GET_CLOCK();
        time = stop - start;

        /* 
        * Exception from the DEBUG_MSG since this message needs to be
        * printed outside the DEBUG flag */
#ifdef ARDUINO
        Serial.println(time, DEC);
#elif defined PC
        printf("%d\n", time);
#endif
        SLEEP(1000);
    }
}

/*!
*   @brief      This function acts as the main scheduling loop.
*   @details    This function is the actual process loop which run\n
*   all the processes. Each iteration consists of:\n
*   \n
*   A process queue is constructed with idle processes to be scheduled,\n
*   the queue's size and content of processes depend of the available\n
*   for the current timeframe and idle processes exection time.\n
*   \n
*   The process queue runs all processes.\n
*   \n
*   Total execution time is calculated.\n
*   \n
*   If the total execution time exceeds the value of the timeframe\n
*   then the next timeframe is deducted by the exceeding time.\n
*   \n
*   If the total execution time did not exceed the value of the\n
*   timeframe then the processes waits (timeframe - total execution time)\n
*   in order to synchronize.\n
**/
void sched_batman_run(void){
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

    PRINT_STRING("Starting scheduler: running processes\n");

    /* 
    * Delay of 20 seconds to plug in the 
    * motors before any commands can start the motors
    **/
#ifdef ARDUINO
    PRINT_STRING("System is ready, PLUG IN BATTERY!");
    SLEEP(20000);
    PRINT_STRING("3...");
    SLEEP(1000);
    PRINT_STRING("2...");
    SLEEP(1000);
    PRINT_STRING("1...");
    SLEEP(1000);
    PRINT_STRING("System booting up");
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
        DEBUG_MSG("Getting (start)clock");

        start = GET_CLOCK();
        
        DEBUG_MSG_VAR(start, DEC);
        DEBUG_MSG("Creating process queue");

        create_process_queue(timeFrame); /* Creates a process queue */

        DEBUG_MSG("Running processes");

        /* Runs all the processes in the queue */
        for(j = 0; j < processData->currentQueueSize; j++){
            run_process(j);
        }

        DEBUG_MSG("Ran all processes, calculating sync time");
        DEBUG_MSG("Getting (stop)clock");

        stop = GET_CLOCK();
        time = (int32_t)(stop-start);

        DEBUG_MSG_VAR(start, DEC);
        DEBUG_MSG_VAR(stop, DEC);
        DEBUG_MSG("****************************");
        DEBUG_MSG_VAR(time, DEC);
        DEBUG_MSG_VAR(processData->currentQueueSize, DEC);

        /* Calculates the time needed to synch */
        syncTime = (int)(timeFrame - time); 
        DEBUG_MSG("Sync time is...");
        DEBUG_MSG_VAR(syncTime, DEC);

#ifdef PC
#ifdef LOG
        print_iteration_status(file, syncTime, time);
#endif /* LOG */
#endif /* PC */

        DEBUG_MSG("Checking if timeframe was exceeded");
        if(syncTime >= 0){
            SLEEP(syncTime);
            timeFrame = TIMEFRAME_MS;
        }
        else if((syncTime * -1) > 1000){
            /* 
            * DEADLINE has been exceeded
            * System faulure: THIS IS DANGEROUS
            * PANIC MODE? 
            * */
#ifdef ARDUINO
            /* If something went wrong the light stops flashing */
            analogWrite(13, 0); 
#endif
        }
        else{
            /* If the timeframe was exceeded with more time 
            * than what fits in the TIMEFRAME then the timeframe should be
            * set to the time of the last timeframe since the other
            * timeframes will equal to 0 there is no point in running them */

            syncTime *= -1;

            /* Setting the (last) timeframe  */
            if(syncTime > TIMEFRAME_MS){
                syncTime = TIMEFRAME_MS % syncTime;
            }
#ifndef DEBUG
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
