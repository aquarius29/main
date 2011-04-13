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

const char PROTO_PROCESS[] = "Protocol Process";
const char PROTO_TASK_1[] = "runProto";

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
Task* createTask(const char *name, Fun_t functionPointer, int16_t executionTime)
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
    task = createTask(PROTO_TASK_1, &protoRun, 10);
    enqueueTask(process, task);
    sched_processData.ProcessList[4] = process;

    sched_processData.IdleProcess = 1;
}

Process** getProcessListPtr(void)
{
    return sched_processData.ProcessList;
}

Process** getQueuePtr(void)
{
    if(sched_processData.ProcessQueue != NULL)
        return sched_processData.ProcessQueue;
    else
        return NULL;
}

int8_t* getIdleProcess(void)
{
    return &sched_processData.IdleProcess;
}

int8_t* getLastProcess(void)
{
    return &sched_processData.LastProcess;
}

Process* getProcessAtIndex(int8_t index)
{
    if(index > TOTAL_NO_PROCESSES)
        return NULL;
    else
        return sched_processData.ProcessList[index];
}

int8_t* getCurrentQueueSize(void)
{
    return &sched_processData.CurrentQueueSize;
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
}

void enqueueProcess(Process *process)
{
    int8_t *queueSize = getCurrentQueueSize();
    getQueuePtr()[*queueSize] = process;
    *queueSize += 1;
}

// Algorithm for setting up a queue of processes
void createProcessQueue(void)
{
    int8_t i;
    int8_t *queueSize = getCurrentQueueSize();
    int currentTimeLeft = 50; //TODO Fix TIME
    Process** processQueue = getQueuePtr();
    Process** processList = getProcessListPtr();
    int8_t* idleProcess = getIdleProcess();
    int8_t* lastProcess = getLastProcess();
    nullQueue();
    
    //MotorProcess starts first
    enqueueProcess(processList[0]);
    currentTimeLeft -= processList[0]->idleTask->executionTime;

    for(i = 1; i < MAX_PROC_ITER; i++)
    {
        //Every other process call is protocol
        if(currentTimeLeft - processList[4]->idleTask->executionTime > 0
                && *getLastProcess() != 4)
        {
            currentTimeLeft -= processList[4]->idleTask->executionTime;
            enqueueProcess(processList[4]);
            *getLastProcess() = 4;
        }
        else if(currentTimeLeft - peekIdleProcess() > 0)
        {
            currentTimeLeft -= peekIdleProcess();
            enqueueProcess(processList[*idleProcess]);
            *lastProcess = *idleProcess;
            if(*getIdleProcess() + 1 <= 3)
            {
                *idleProcess += 1;
            }
            else
            {
                *idleProcess = 1; //Restart process order in list
            }
        }
        else
        {
            break;
        }
    }

    printf("Current Process Queue: \n");
    for(i = 0; i < *getCurrentQueueSize(); i++)
    {
        printf("%s\n", processQueue[i]->name);        
    }
    printf("\n");
}

/* Returns the index of the process which is idle */
int16_t peekIdleProcess(void)
{
    Process **processList = getProcessListPtr();
    int16_t taskTime = processList[*getIdleProcess()]->idleTask->executionTime;
    return taskTime;
}
