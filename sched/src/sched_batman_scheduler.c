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
*   @file sched_scheduler.c
*   
*   @brief Functions for the batman implementation scheduler.
*
*   @author Anders Treptow
*   @date 2011-04-19
*
*   @history    2011-03-29 - wrote prototype
*               2011-04-04 - created process structure
*               2011-04-10 - created processData structure
*               2011-04-11 - all enqueueing written
*               2011-04-16 - time-constraints implemented
*               2011-04-19 - added Doxygen comments
*               2011-04-20 - changed init_process_data() based on\n
*                            naive implementation
*               2011-04-21 - Made execution time measurement
*               2011-05-10 - made time measurement for core components
*               2011-05-19 - added license
*               2011-05-19 - fixed some doxygen comments
*/
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#ifdef PC
#include <stdio.h>

#define PRINT_STRING(string) printf(string)

/* stubs represent other modules */
/* #include "sched_stubs.h" */
#elif defined ARDUINO
#include "WProgram.h"

#define PRINT_STRING(string) Serial.println(string)
#endif /* PC ARDUINO*/

#include "moto_interface.h"
#include "proto_lib.h"
#include "stab_interface.h"
#include "mov_interface.h"
#include "serial_interface.h"

#include "sched_batman_scheduler.h"

/*!
*   @brief  Used to create memory space for a process and returns a pointer \n
*   to that space.
*   
*   @param  The Process ID that shall be designated to the process.
*/
Process* create_process(int8_t pid){
	Process *process = (Process*)malloc(sizeof(Process));
	memset(process, 0, sizeof(Process));
    process->Pid = pid;
	return process;
}

/*!
*   @brief  Terminates all data related to a process.
*   
*   @param  process A process pointer to the process to be terminated.
*/
void end_process(Process *process){
	remove_process_tasks(process->firstTask);
    if(process != NULL){
	    free(process);
    }
}

/*!
*   @brief  Used to create memory space for a task and returns a pointer \n
*   to that space.
*   
*   @param   functionPointer A sched_Fun_t function pointer to the \n
*   function of which the task is to execute.
*   @param  exectionTime The measured time it will take for the \n
*   to execute and return.
*   @return A pointer to the task which was allocated.
*/
Task* create_task(sched_Fun_t functionPointer, int16_t executionTime){
	Task *task = (Task*)malloc(sizeof(Task));
	memset(task, 0, sizeof(Task));
	task->functionPointer = functionPointer;
    task->executionTime = executionTime;
	return task;
}

/*!
*   @brief  Removes all enqueued tasks in a process. It runs recursively \n
*   and removes all tasks linked with the first task.
*   
*   @param   task Pointer to the first task in the linked list of \n
*   which the deallocation will run.
*/
void remove_process_tasks(Task *task){
	if(task->nextTask != NULL){
		remove_process_tasks(task->nextTask);
		free(task);
	}
    else{
		free(task);
	}
}

/*!
*   @brief  Enqueues a task to a process at the last position of \n
*   the linked list of tasks.
*
*   @param  process Pointer to the process of which the task shall be \n
*   enqueued with-
*   @param  task Pointer to the task which shall be enqueued.
*/
void enqueue_task(Process *process, Task *task){
	Task *pTmpTask = process->lastTask;
	if(pTmpTask != NULL){
        pTmpTask->nextTask = task;
        process->lastTask = task;
	}
	else{
		process->firstTask = task;
		process->lastTask = task;
		process->idleTask = task;
	}
	process->no_tasks++;
}

/*!
*   @brief  Runs the idle task for a specific process.
*   
*   @param process Pointer to the process of which to run \n
*   it's idle task.
*/
void run_idle_task(Process *process){
	if(process->firstTask != NULL){
		Task *pTmpTask = process->idleTask;
		sched_Fun_t fp = pTmpTask->functionPointer;

		if(pTmpTask->nextTask != NULL)
			process->idleTask = pTmpTask->nextTask;
		else
			process->idleTask = process->firstTask;

		fp();
	}
}

/*!
*   @brief  Sets up the processes and initialize the init functions \n
*   for the processes as well as running the init functions for \n
*   each component in the system.
*
*   @return If initialization was success it returns 0, otherwise 1.
*/
int16_t init_process_data(void){
    /*
    * funArrInit is an array of function calls to the init 
    * functions for the system and funArrRun is an array of function 
    * calls to the various system run functions. These are declared localy
    * in this scope in order to save memory since these arrays are never 
    * needed after system initialization.
    **/
    sched_Fun_t funArrInit[] = { &moto_init, 
                                &mov_init, 
                                &stab_init, 
                                &serial_init };
    sched_Fun_t funArrRun[] = { &moto_run, 
                                &mov_run, 
                                &stab_run, 
                                &serial_run };

    ProcessData *pProcessData;

    PRINT_STRING("Initializing system...\n");
    /* Author: Joakim
    *******************************************************************/
    if (system_init(funArrInit) != 0) {
        /* something went wrong during system initialization */
            PRINT_STRING("Error in system initialization sequence!\n");
#ifdef PC
            exit(1);
#elif defined ARDUINO
            return 1;
#endif /* PC ARDUINO */
    }
    /******************************************************************/
    else{ /* If system_init returned success, set up processes*/
    
        PRINT_STRING("System Initialization completed!\n");
        PRINT_STRING("Setting up processes.................");

        pProcessData = get_process_data();

        if(process_setup(pProcessData, funArrRun) != 0){
            PRINT_STRING("FAILED\n\n");
#ifdef PC
            exit(1);
#elif defined ARDUINO
            return 1;
#endif /* PC ARDUINO */
        }

        pProcessData->idleProcessToSchedule = 0;
        pProcessData->totalExecutionTime = 0;

        PRINT_STRING("DONE\n\n");
    }
    return 0; /*EXIT_SUCCESS*/
}

/*!
*   @brief  Sets up all processes in the system as well as their tasks.
*
*   @param pProcessData Pointer to the process data struct where data \n
*   shall be added about the processes.
*   @param funArrRun Array of the functionpointers to the tasks of which \n
*   the setup process will create the processes from.
*/
int16_t process_setup(ProcessData *pProcessData, 
    sched_Fun_t funArrRun[TOTAL_NO_PROCESSES])
{
    Process *process;
    Task *task;

    /* MOTOR PROCESS */
    process = create_process(MOTOR_PID);
    task = create_task(funArrRun[0], 1); /* 2011-05-12 | 
                                         time measured to ~240 microseconds */
    enqueue_task(process, task);
    pProcessData->processList[0] = process;

    /* MOVE PROCESS */
    process = create_process(MOVE_PID);
    task = create_task(funArrRun[1], 54); /* 2011-05-16 | 
                                          time measured to ~ */
    enqueue_task(process, task);
    pProcessData->processList[1] = process;

    /* STAB PROCESS */
    process = create_process(STAB_PID);
    task = create_task(funArrRun[2], 38); /* 2011-05-15 | 
                                          stab_run measured to ~38100 */
    enqueue_task(process, task);
    pProcessData->processList[2] = process;

    /* SERIAL PROCESS */
    process = create_process(SERIAL_PID);
    task = create_task(funArrRun[3], 5); /* not measured */
    enqueue_task(process, task);
    pProcessData->processList[3] = process;

    return 0;
}

/* Author: Joakim
********************************************************/
/*!
*   @brief  Initializes the system by running their init functions.
*   
*   @author Joakim
*   @param funArrInit Array of init function pointers to run.
*/
int16_t system_init(sched_Fun_t funArrInit[TOTAL_NO_PROCESSES]){
    int16_t i;
    int16_t res;
    
    proto_init(); /* <- init proto | 
                  * hardcoded due to late inclusion from protocol */
    for (i = 0; i < TOTAL_NO_PROCESSES; i++){
        res = (funArrInit[i])();

        DEBUG_MSG("function call result: %d\n", res);
    }
    
    return 0;
}
/********************************************************/

/*!
*   @brief  Deallocates all process data current running. \n
*   Mostly used for PC builds in order to avoid memory leaks.
*/
void clean_process_data(void){
    int i;
    ProcessData *pProcessData = get_process_data();
    for(i = 0; i < TOTAL_NO_PROCESSES; i++){
        end_process(pProcessData->processList[i]);
    }
}

/*!
*   @brief  Retrieves a pointer to the main data struct for the processes. \n
*
*   @return A pointer to the main data struct.
*/
ProcessData* get_process_data(void){
    return &sched_processData;
}

/*!
*   @brief  Nulls the current process queue so that a new \n
*   one can be created. Must be used at the start of each iteration.
*/
void null_queue(void){
    int8_t i;
    ProcessData *pProcessData = get_process_data();
    for(i = 0; i < pProcessData->currentQueueSize; i++){
        pProcessData->processQueue[i] = 0;
    }
    pProcessData->currentQueueSize = 0;
    pProcessData->totalExecutionTime = 0;
}

/*!
*   @brief  Enqueues a process to the current process list of which will \n
*   be used during the creation of the execution queue.
*
*   @param  process Pointer to the process to be enqueued to the list.
*/
void enqueue_process(Process *process){
    ProcessData *processData = get_process_data();
    if(processData->currentQueueSize < MAX_PROC_ITER){
        processData->processQueue[processData->currentQueueSize] = process;
        processData->currentQueueSize += 1;
    }
}

/*!
*   @brief  The main function of which holds the algorithm to create the \n
*   current iteration's process list. Based on the input timeframe it \n
*   will fit as many idle processes as possible without exceeding the \n
*   timeframe execution time wise.
*
*   @param  timeFrame The time of how long the current timeframe is.
*/
void create_process_queue(int16_t timeFrame){
    int8_t i;
    int16_t timeLeft = timeFrame;
    int8_t peekLayer = 0;
    int16_t iterCount = 0;
    int16_t taskTime = 0;
    ProcessData *pProcessData = get_process_data();
    Process **pProcessList = pProcessData->processList;
    Process **pQueue = pProcessData->processQueue;
    int8_t *pIdleToSchedule = &pProcessData->idleProcessToSchedule;

    null_queue();

    if(timeLeft > 0){
        for(i = 1; i < MAX_PROC_ITER; i++){
            if(i % TOTAL_NO_PROCESSES == 0){
                peekLayer++;
            }
            taskTime = peek_process(pProcessList[*pIdleToSchedule], 
                                    peekLayer)->executionTime;
            if(timeLeft - taskTime > 0){
                enqueue_process(pProcessList[*pIdleToSchedule]);
                pProcessData->totalExecutionTime += taskTime;
                timeLeft -= taskTime;
            }
            else{
                break;
            }

            if(*pIdleToSchedule + 1 < TOTAL_NO_PROCESSES){
                *pIdleToSchedule += 1;
            }
            else{
                *pIdleToSchedule = 0;
            }
        }
    }

#ifdef PC
#ifdef DEBUG
    PRINT_STRING("Current Process Queue\n==================\n");
    for(i = 0; i < pProcessData->currentQueueSize; i++){
        PRINT_STRING("%d\n", pQueue[i]->idleTask->executionTime);
    }
    PRINT_STRING("SLEEP-TIME: %d\n", timeLeft);
    PRINT_STRING("PD-TIME: %d\n", pProcessData->totalExecutionTime);
    PRINT_STRING("\n");
#endif
#endif
}

/*!
*   @brief  Runs the process at the specific index of the \n
*   current process list in the main processData struct.
*
*   @param  processIndex Zero-based index of the process to be executed.
*/
void run_process(int8_t processIndex){
    if(processIndex <= MAX_PROC_ITER){
        ProcessData *pProcessData = get_process_data();
        run_idle_task(pProcessData->processQueue[processIndex]);
    }
}

/*!
*   @brief  Peeks at the currently idle task for a process \n
*   at a specific layer which is used when creating process list \n
*   per iteration.
*
*   @param  process Pointer to the process to peek at.
*   @param  layer The depth to peek at counting from the idle task.
*/
Task* peek_process(Process *process, int16_t layer){
    int8_t i;
    Task *pTask = process->idleTask;
    for(i = 0; i < layer; i++){
        if(pTask->nextTask != NULL){
            pTask = pTask->nextTask;
        }
        else{
            pTask = process->firstTask;
        }
    }
    return pTask;
}
