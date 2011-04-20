/*!
*   @file sched_scheduler.h
*
*   @brief Header file for the batman scheduler's main functions.
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

#ifndef __sched_scheduler_h_
#define __sched_scheduler_h_

#include <stdint.h>
#define TOTAL_NO_PROCESSES 5
#define MAX_PROC_ITER 30
#define TIMEFRAME_MS 50

/* Defines all Process ID's */
#define MOTOR_PID 1
#define CA_PID 2
#define MOVE_PID 3
#define STAB_PID 4
#define PROTO_PID 5

#ifdef PC
static const char MOTOR_PROCESS[] = "Motor Process";
static const char MOTOR_TASK_1[] = "runMotor";

static const char COLLISION_PROCESS[] = "CA Process";
static const char COLLISION_TASK_1[] = "runCA";
static const char COLLISION_TASK_2[] = "runCA2";

static const char MOVE_PROCESS[] = "Move Process";
static const char MOVE_TASK_1[]  = "runMove";

static const char STAB_PROCESS[] = "Stabilization Process";
static const char STAB_TASK_1[] = "runStab";

static const char PROTO_PROCESS[] = "Connectivity Process";
static const char PROTO_TASK_1[] = "runConn";
#endif

/* type Fun_t is type "function that 
* returns int16_t and takes no arguments */
typedef int16_t(*Fun_t)(void);

/* struct Task points to function which perfoms given task 
* Is tasks are linked in a linked list structure */
typedef struct tagTask {
    /* Readable name of the task */
	const char *name;
    /* The time it takes to execute the function pointed to */
	int16_t executionTime;
    /* Pointer to function */
	Fun_t functionPointer;
    /* Pointer to the next Task in linked list */
	struct tagTask *nextTask;
}Task;

/* struct Process consists of 1...n number of Tasks put into an array */
typedef struct tagProcess {
    /* Process ID */
    int8_t Pid;
    /* Readable name of process */
	const char *name; //TODO: Possible to remove
    /* Priority of process in range of 0-100 */
	int8_t priority;
    /* Numbers of tasks which the process contains */
	int8_t no_tasks;
    /* At what layer of tasks the last peeking was at */
    int8_t peekLayer;
    /* Pointer to first task in linked list */
	Task *firstTask;
    /* Pointer to last task in linked list */
	Task *lastTask;
    /* Pointer the idle task in linked list */
	Task *idleTask;
}Process;

/*Struct which contains all data that handles processes for the system */
typedef struct tagProcessData {
    /* ProcessList contains all processes of the system */
    Process *ProcessList[TOTAL_NO_PROCESSES];
    /* ProcessQueue is the actual queue of processes to be ran */
    Process *ProcessQueue[MAX_PROC_ITER];
    /* LastProcess is an offset to the last process ran in the ProcessList */
    int8_t IdleProcessToSchedule;
    /* The size of the current processQueue */
    int8_t CurrentQueueSize;
    /* The total execution time for the processQueue */
    int16_t TotalExecutionTime;
}ProcessData;

/* Functions that handle a process */
Process* createProcess(const char *name, int8_t pid);
void endProcess(Process *process);
void enqueueTask(Process *process, Task *task);
void dequeueTask(Process *process, Task *task);
void runIdleTask(Process *process);
Task* peekProcess(Process *process, int16_t layer);

/* Functions that handle a task */
Task* createTask(const char *name, 
                    Fun_t functionPointer, 
                        int16_t executionTime);
void removeProcessTasks(Task *task);

/* Functions that handle the ProcessData struct */
void initProcessData(void);
void cleanProcessData(void);
ProcessData* getProcessData(void);
void nullQueue(void);
void enqueueProcess(Process *process);
void runProcess(int8_t processIndex);

/* RunTime functions for ProcessData struct */
void createProcessQueue(void);

/* Main Process Data for the system */
static ProcessData sched_processData;

#endif