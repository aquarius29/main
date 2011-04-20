/*!
*   @file sched_scheduler.c
*   
*   @brief Functions for the batman implementation scheduler.
*
*   @author Anders Treptow
*   @date 2011-04-19
*
*   @history    2011-03-29 wrote prototype
*               2011-04-04 created process structure
*               2011-04-10 created processData structure
*               2011-04-11 all enqueueing written
*               2011-04-16 time-constraints implemented
*               2011-04-19 added Doxygen comments
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "sched_scheduler.h"

#ifdef PC
/* stubs represent other modules */
#include "sched_stubs.h"
#endif

Process* createProcess(const char *name, int8_t pid)
{
	Process *process = (Process*)malloc(sizeof(Process));
	memset(process, 0, sizeof(Process));
	process->name = name;
    process->Pid = pid;
	return process;
}

/* Terminates a process completely */
void endProcess(Process *process)
{
	removeProcessTasks(process->firstTask);
    if(process != NULL)
    {
	    free(process);
    }
}

Task* createTask(const char *name, 
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
void removeProcessTasks(Task *task)
{
	if(task->nextTask != NULL)
	{
		removeProcessTasks(task->nextTask);
		free(task);
	}
    else
	{
		free(task);
	}
}

/* Enqueues a task to a structer at the last position of queue */
void enqueueTask(Process *process, Task *task)
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

// TODO (Will this function ever be used?)
void dequeueTask(Process *process, Task *task)
{ }

/* Runs the idle task for the process */
void runIdleTask(Process *process)
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

/* Sets up the processes */
void initProcessData(void)
{
    ProcessData *pProcessData = getProcessData();

    #ifdef PC
    Process *process = createProcess(MOTOR_PROCESS, MOTOR_PID);
    Task *task = createTask(MOTOR_TASK_1, &motoRun, 10);
    enqueueTask(process, task);
    pProcessData->ProcessList[0] = process;

    process = createProcess(COLLISION_PROCESS, CA_PID);
    task = createTask(COLLISION_TASK_1, &caRun, 10);
    enqueueTask(process, task);
    task = createTask(COLLISION_TASK_2, &caRun2, 5);
    enqueueTask(process, task);
    pProcessData->ProcessList[1] = process;

    process = createProcess(MOVE_PROCESS, MOVE_PID);
    task = createTask(MOVE_TASK_1, &moveRun, 10);
    enqueueTask(process, task);
    pProcessData->ProcessList[2] = process;

    process = createProcess(STAB_PROCESS, STAB_PID);
    task = createTask(STAB_TASK_1, &stabRun, 10);
    enqueueTask(process, task);
    pProcessData->ProcessList[3] = process;

    process = createProcess(PROTO_PROCESS, PROTO_PID);
    task = createTask(PROTO_TASK_1, &connRun, 10);
    enqueueTask(process, task);
    pProcessData->ProcessList[4] = process;
    #endif

    pProcessData->IdleProcessToSchedule = 1;
    pProcessData->TotalExecutionTime = 0;
}

void cleanProcessData(void)
{
    int i;
    ProcessData *pProcessData = getProcessData();
    for(i = 0; i < TOTAL_NO_PROCESSES; i++)
    {
        endProcess(pProcessData->ProcessList[i]);
    }
}

ProcessData* getProcessData(void)
{
    return &sched_processData;
}

/* Nulls out the processQueue */
void nullQueue(void)
{
    int8_t i;
    ProcessData *pProcessData = getProcessData();
    for(i = 0; i < pProcessData->CurrentQueueSize; i++)
    {
        pProcessData->ProcessQueue[i] = 0;
    }
    pProcessData->CurrentQueueSize = 0;
    pProcessData->TotalExecutionTime = 0;
}

void enqueueProcess(Process *process)
{
    ProcessData *processData = getProcessData();
    processData->ProcessQueue[processData->CurrentQueueSize] = process;
    processData->CurrentQueueSize += 1;
}

void createProcessQueue(void)
{
    int8_t i;
    int16_t timeLeft = TIMEFRAME_MS;
    int8_t peekLayer = 0;
    int16_t iterCount = 0;
    int16_t taskTime = 0;
    ProcessData *pProcessData = getProcessData();
    Process **pProcessList = pProcessData->ProcessList;
    Process **pQueue = pProcessData->ProcessQueue;
    int8_t *pIdleToSchedule = &pProcessData->IdleProcessToSchedule;

    nullQueue();
    enqueueProcess(pProcessList[0]);
    taskTime = peekProcess(pProcessList[0], peekLayer)->executionTime;
    timeLeft -= peekProcess(pProcessList[0], peekLayer)->executionTime;
    pProcessData->TotalExecutionTime += taskTime;

    for(i = 1; i < MAX_PROC_ITER; i++)
    {
        if(i % TOTAL_NO_PROCESSES == 0)
        {
            peekLayer++;
        }
        taskTime = peekProcess(pProcessList[*pIdleToSchedule], 
                                peekLayer)->executionTime;
        if(timeLeft - taskTime > 0)
        {
            enqueueProcess(pProcessList[*pIdleToSchedule]);
            pProcessData->TotalExecutionTime += taskTime;
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
    printf("Current Process Queue: \n");
    for(i = 0; i < pProcessData->CurrentQueueSize; i++)
    {
        printf("%s\t", pQueue[i]->name);    
        printf("%d\n", pQueue[i]->idleTask->executionTime);
    }
    printf("SLEEP-TIME: %d\n", timeLeft);
    printf("PD-TIME: %d\n", pProcessData->TotalExecutionTime);
    printf("\n");
    #endif
}

void runProcess(int8_t processIndex)
{
    if(processIndex <= MAX_PROC_ITER)
    {
        ProcessData *pProcessData = getProcessData();
        runIdleTask(pProcessData->ProcessQueue[processIndex]);
    }
}

/* Returns the task which is idle for the process for scheduling */
Task* peekProcess(Process *process, int16_t layer)
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
