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
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "sched_batman_scheduler.h"

#ifdef PC
/* stubs represent other modules */
#include "sched_stubs.h"
#endif

Process* create_process(int8_t pid)
{
	Process *process = (Process*)malloc(sizeof(Process));
	memset(process, 0, sizeof(Process));
    process->Pid = pid;
	return process;
}

/* Terminates a process completely */
void end_process(Process *process)
{
	remove_process_tasks(process->firstTask);
    if(process != NULL)
    {
	    free(process);
    }
}

Task* create_task(const char *name, 
                    Fun_t functionPointer, int16_t executionTime)
{
    int16_t strLen = strlen(name) + 1;
	Task *task = (Task*)malloc(sizeof(Task));
	memset(task, 0, sizeof(Task));
    task->name = name;
	task->functionPointer = functionPointer;
    task->executionTime = executionTime;
	return task;
}

/* Removes all enqueued tasks for a process */
void remove_process_tasks(Task *task)
{
	if(task->nextTask != NULL)
	{
		remove_process_tasks(task->nextTask);
		free(task);
	}
    else
	{
		free(task);
	}
}

/* Enqueues a task to a structer at the last position of queue */
void enqueue_task(Process *process, Task *task)
{
	Task *pTmpTask = process->lastTask;
	if(pTmpTask != NULL)
	{
        pTmpTask->nextTask = task;
        process->lastTask = task;
	}
	else
	{
		process->firstTask = task;
		process->lastTask = task;
		process->idleTask = task;
	}
	process->no_tasks++;
}

/* Runs the idle task for the process */
void run_idle_task(Process *process)
{
	if(process->firstTask != NULL)
	{
		Task *pTmpTask = process->idleTask;
		Fun_t fp = pTmpTask->functionPointer;

		if(pTmpTask->nextTask != NULL)
			process->idleTask = pTmpTask->nextTask;
		else
			process->idleTask = process->firstTask;

		fp();
	}
}

/* Sets up the processes and initialize the init functions for processes */
int16_t init_process_data(void)
{
    /* function pointers to modules init functions */
    Fun_t funArrInit[] = {  &motoInit,
                            &caInit,
                            &moveInit,
                            &stabInit,
                            &connInit };

    /* function pointers to modules run functions */
    Fun_t funnArrRun[] = {  &motoRun,
                                &caRun,
                                &moveRun,
                                &stabRun,
                                &connRun };

    ProcessData *pProcessData;
    Process *process;
    Task *task;

    #ifdef PC
        printf("Initializing system...\n");
    #endif
    if (system_init(funArrInit) != EXIT_SUCCESS) {
        /* something went wrong during system initialization */
        #ifdef PC
            printf("Error in system initialization sequence!\n");
            exit(1);
        #endif /* PC */
        #ifdef ARDUINO
            /*  
             *  Do we have a way to give fatal error message on arduino,
             *  and exit? 
             */
            exit(1);
            
        #endif /* ARDUINO */
    }
    else /* If system_init returned success, set up processes*/
    {
        #ifdef PC
            printf("System Initialization completed!\n");
            printf("Setting up processes.................");
        #endif
        
        pProcessData = get_process_data();

        process = create_process(MOTOR_PID);
        task = create_task(MOTOR_TASK_1, funnArrRun[0], 10);
        enqueue_task(process, task);
        pProcessData->processList[0] = process;

        process = create_process(CA_PID);
        task = create_task(COLLISION_TASK_1, funnArrRun[1], 10);
        enqueue_task(process, task);
        pProcessData->processList[1] = process;

        process = create_process(MOVE_PID);
        task = create_task(MOVE_TASK_1, funnArrRun[2], 10);
        enqueue_task(process, task);
        pProcessData->processList[2] = process;

        process = create_process(STAB_PID);
        task = create_task(STAB_TASK_1, funnArrRun[3], 10);
        enqueue_task(process, task);
        pProcessData->processList[3] = process;

        process = create_process(CONN_PID);
        task = create_task(CONN_TASK_1, funnArrRun[4], 10);
        enqueue_task(process, task);
        pProcessData->processList[4] = process;

        pProcessData->idleProcessToSchedule = 1;
        pProcessData->totalExecutionTime = 0;
        #ifdef PC
            printf("DONE\n\n");
        #endif
    }
    return EXIT_SUCCESS;
}

/* Author: Joakim */
int16_t system_init(Fun_t funArrInit[TOTAL_NO_PROCESSES]){
    int16_t i;
    int16_t res;
    
    for (i = 0; i < TOTAL_NO_PROCESSES; i++){
        res = (funArrInit[i])();

        #ifdef PC
        #ifdef DEBUG
            printf("function call result: %d\n", res);
        #endif /* DEBUG */
        #endif /* PC */
    }
    
    return EXIT_SUCCESS;
}

/* Deallocates all dynamic data */
void clean_process_data(void)
{
    int i;
    ProcessData *pProcessData = get_process_data();
    for(i = 0; i < TOTAL_NO_PROCESSES; i++)
    {
        end_process(pProcessData->processList[i]);
    }
}

ProcessData* get_process_data(void)
{
    return &sched_processData;
}

/* Nulls out the processQueue */
void null_queue(void)
{
    int8_t i;
    ProcessData *pProcessData = get_process_data();
    for(i = 0; i < pProcessData->currentQueueSize; i++)
    {
        pProcessData->processQueue[i] = 0;
    }
    pProcessData->currentQueueSize = 0;
    pProcessData->totalExecutionTime = 0;
}

/* If */
void enqueue_process(Process *process)
{
    ProcessData *processData = get_process_data();
    if(processData->currentQueueSize < MAX_PROC_ITER)
    {
        processData->processQueue[processData->currentQueueSize] = process;
        processData->currentQueueSize += 1;
    }
}

void create_process_queue(void)
{
    int8_t i;
    int16_t timeLeft = TIMEFRAME_MS;
    int8_t peekLayer = 0;
    int16_t iterCount = 0;
    int16_t taskTime = 0;
    ProcessData *pProcessData = get_process_data();
    Process **pProcessList = pProcessData->processList;
    Process **pQueue = pProcessData->processQueue;
    int8_t *pIdleToSchedule = &pProcessData->idleProcessToSchedule;

    null_queue();
    enqueue_process(pProcessList[0]);
    taskTime = peek_process(pProcessList[0], peekLayer)->executionTime;
    timeLeft -= peek_process(pProcessList[0], peekLayer)->executionTime;
    pProcessData->totalExecutionTime += taskTime;

    for(i = 1; i < MAX_PROC_ITER; i++)
    {
        if(i % TOTAL_NO_PROCESSES == 0)
        {
            peekLayer++;
        }
        taskTime = peek_process(pProcessList[*pIdleToSchedule], 
                                peekLayer)->executionTime;
        if(timeLeft - taskTime > 0)
        {
            enqueue_process(pProcessList[*pIdleToSchedule]);
            pProcessData->totalExecutionTime += taskTime;
            timeLeft -= taskTime;
        }
        else
        {
            break;
        }

        if(*pIdleToSchedule + 1 < TOTAL_NO_PROCESSES)
        {
            *pIdleToSchedule += 1;
        }
        else
        {
            *pIdleToSchedule = 1;
        }
    }

    #ifdef DEBUG
    printf("Current Process Queue\n==================\n");
    for(i = 0; i < pProcessData->currentQueueSize; i++)
    {
        printf("%s\t", pQueue[i]->name);    
        printf("%d\n", pQueue[i]->idleTask->executionTime);
    }
    printf("SLEEP-TIME: %d\n", timeLeft);
    printf("PD-TIME: %d\n", pProcessData->totalExecutionTime);
    printf("\n");
    #endif
}

void run_process(int8_t processIndex)
{
    if(processIndex <= MAX_PROC_ITER)
    {
        ProcessData *pProcessData = get_process_data();
        run_idle_task(pProcessData->processQueue[processIndex]);
    }
}

/* Returns the task which is idle for the process for scheduling */
Task* peek_process(Process *process, int16_t layer)
{
    int8_t i;
    Task *pTask = process->idleTask;
    for(i = 0; i < layer; i++)
    {
        if(pTask->nextTask != NULL)
        {
            pTask = pTask->nextTask;
        }
        else
        {
            pTask = process->firstTask;
        }
    }
    return pTask;
}
