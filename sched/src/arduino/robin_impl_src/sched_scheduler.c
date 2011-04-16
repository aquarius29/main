#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "sched_scheduler.h"
/* stubs represent other modules */
#include "sched_stubs.h"

const char MOTOR_PROCESS[] = "Motor Process";
const char MOTOR_TASK_1[] = "runMotor";

const char COLLISION_PROCESS[] = "CA Process";
const char COLLISION_TASK_1[] = "runCA";

const char MOVE_PROCESS[] = "Move Process";
const char MOVE_TASK_1[]  = "runMove";

const char STAB_PROCESS[] = "Stabilization Process";
const char STAB_TASK_1[] = "runStab";

const char PROTO_PROCESS[] = "Connectivity Process";
const char PROTO_TASK_1[] = "runConn";

/* TODO: Fix const construction of processes */
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
	free(process);
}

/* TODO: Fix const construction of tasks */
Task* createTask(const char *name, 
                    Fun_t functionPointer, 
                            int16_t executionTime)
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
	Task *tmpTask = process->lastTask;
	if(tmpTask != NULL)
	{
		while(tmpTask != NULL)
		{
			tmpTask = tmpTask->nextTask;
		}
		tmpTask = task;
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
		Task *tmpTask = process->idleTask;
		Fun_t fp = tmpTask->functionPointer;

		if(tmpTask->nextTask != NULL)
			process->idleTask = tmpTask->nextTask;
		else
			process->idleTask = process->firstTask;

		fp();
	}
}

/* Sets up the processes */
void initProcessData(void)
{
    Process *process = createProcess(MOTOR_PROCESS, MOTOR_PID);
    Task *task = createTask(MOTOR_TASK_1, &motoRun, 10);
    enqueueTask(process, task);
    sched_processData.ProcessList[0] = process;

    process = createProcess(COLLISION_PROCESS, CA_PID);
    task = createTask(COLLISION_TASK_1, &caRun, 10);
    enqueueTask(process, task);
    sched_processData.ProcessList[1] = process;

    process = createProcess(MOVE_PROCESS, MOVE_PID);
    task = createTask(MOVE_TASK_1, &moveRun, 10);
    enqueueTask(process, task);
    sched_processData.ProcessList[2] = process;

    process = createProcess(STAB_PROCESS, STAB_PID);
    task = createTask(STAB_TASK_1, &stabRun, 10);
    enqueueTask(process, task);
    sched_processData.ProcessList[3] = process;

    process = createProcess(PROTO_PROCESS, PROTO_PID);
    task = createTask(PROTO_TASK_1, &connRun, 10);
    enqueueTask(process, task);
    sched_processData.ProcessList[4] = process;

    sched_processData.IdleProcessToSchedule = 1;
    sched_processData.TotalExecutionTime = 0;
}

void cleanProcessData(void)
{
    int i;
    for(i = 0; i < TOTAL_NO_PROCESSES; i++)
    {
        endProcess(sched_processData.ProcessList[i]);
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
    for(i = 0; i < MAX_PROC_ITER; i++)
    {
        if(sched_processData.ProcessQueue[i] != NULL)
            sched_processData.ProcessQueue[i] = 0;
        else
            break;
    }
    sched_processData.CurrentQueueSize = 0;
    sched_processData.TotalExecutionTime = 0;
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
    int16_t taskTime = 0;
    ProcessData *pProcessData = getProcessData();
    Process **pProcessList = pProcessData->ProcessList;
    Process **pQueue = pProcessData->ProcessQueue;
    int8_t *pIdleToSchedule = &pProcessData->IdleProcessToSchedule;

    nullQueue();
    enqueueProcess(pProcessList[0]);
    timeLeft -= peekProcess(pProcessList[0], peekLayer)->executionTime;

    for(i = 1; i < MAX_PROC_ITER; i++)
    {
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
        peekLayer++;
    }

    #ifdef DEBUG
    printf("Current Process Queue: \n");
    for(i = 0; i < pProcessData->CurrentQueueSize; i++)
    {
        printf("%s\n", pQueue[i]->name);        
    }
    printf("\n");
    #endif
}

/*
// Algorithm for setting up a queue of processes
void createProcessQueue(void)
{
    int8_t i;
    int currentTimeLeft = 50; //TODO Fix TIME
    ProcessData *processData = getProcessData();
    int8_t idleScheduledProcess = processData->IdleProcess;
    int8_t lastScheduledProcess = processData->LastProcess;
    int8_t* queueSize = &processData->CurrentQueueSize;
    Process** processQueue = processData->ProcessQueue;
    Process** processList = processData->ProcessList;

    nullQueue();
    
    //MotorProcess starts first
    enqueueProcess(processList[0]);
    currentTimeLeft -= processList[0]->idleTask->executionTime;

    for(i = 1; i < MAX_PROC_ITER; i++)
    {
        //Every other process call is protocol
        if(currentTimeLeft - processList[4]->idleTask->executionTime > 0
                && lastScheduledProcess != 4)
        {
            currentTimeLeft -= processList[4]->idleTask->executionTime;
            enqueueProcess(processList[4]);
            lastScheduledProcess = 4;
        }
        else if(
            currentTimeLeft - processList[idleScheduledProcess]->idleTask->executionTime > 0)
        {
            currentTimeLeft -= processList[idleScheduledProcess]->idleTask->executionTime;
            enqueueProcess(processList[idleScheduledProcess]);
            lastScheduledProcess = idleScheduledProcess;
            if(idleScheduledProcess + 1 <= 3)
            {
                idleScheduledProcess += 1;
            }
            else
            {
                idleScheduledProcess = 1; //Restart process order in list
            }
        }
        else
        {
            break;
        }
    }
    for(i = 0; i < *queueSize; i++)
    {
        processData->TotalExecutionTime += 
            processData->ProcessQueue[i]->idleTask->executionTime;
    }

    #ifdef DEBUG
    printf("Current Process Queue: \n");
    for(i = 0; i < *queueSize; i++)
    {
        printf("%s\n", processQueue[i]->name);        
    }
    printf("\n");
    #endif
}
*/

void runProcess(int8_t processIndex)
{
    ProcessData *pProcessData = getProcessData();
    runIdleTask(pProcessData->ProcessQueue[processIndex]);

    /*
    ProcessData *processData = getProcessData();
    runIdleTask(processData->ProcessQueue[processData->IdleProcess]);
    if(processData->IdleProcess + 1 < processData->CurrentQueueSize)
    {
        processData->LastProcess = processData->IdleProcess;
        processData->IdleProcess += 1;
    }
    else
    {
        processData->LastProcess = processData->IdleProcess;
        processData->IdleProcess = 0;
    }
    */
}

/* Returns the task which is idle for the process for scheduling */
Task* peekProcess(Process *process, int16_t layer)
{
    int8_t i;
    Task *task = process->firstTask;
    for(i = 0; i < layer; i++)
    {
        if(task->nextTask != NULL)
        {
            task = task->nextTask;
        }
        else
        {
            task = process->firstTask;
        }
    }
    return task;
}
