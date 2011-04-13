#ifndef __sched_scheduler_h_
#define __sched_scheduler_h_

#include <stdint.h>
#define TOTAL_NO_PROCESSES 5
#define MAX_PROC_ITER 30

/* Defines all Process ID's */
#define MOTOR_PID 1
#define CA_PID 2
#define MOVE_PID 3
#define STAB_PID 4
#define PROTO_PID 5

//Defintion of motor process
extern const char MOTOR_PROCESS[];
extern const char MOTOR_TASK_1[];

//Defintion of Collision Avoidance process
extern const char COLLISION_PROCESS[];
extern const char COLLISION_TASK_1[];

//Defintion of Move process
extern const char MOVE_PROCESS[];
extern const char MOVE_TASK_1[];

//Defintion of Stabilization process
extern const char STAB_PROCESS[];
extern const char STAB_TASK_1[];

//Defintion of Protocol process (non-existant)
extern const char PROTO_PROCESS[];
extern const char PROTO_TASK_1[];

/* type Fun_t is type "function that returns int16_t and takes no arguments */
typedef int16_t(*Fun_t)(void);

/* struct Task points to function which perfoms given task 
* Is tasks are linked in a linked list structure */
typedef struct tagTask
{
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
typedef struct tagProcess
{
    /* Process ID */
    int8_t Pid;
    /* Readable name of process */
	const char *name; //TODO: Possible to remove
    /* Priority of process in range of 0-100 */
	int8_t priority;
    /* Numbers of tasks which the process contains */
	int8_t no_tasks;
    /* Pointer to first task in linked list */
	Task *firstTask;
    /* Pointer to last task in linked list */
	Task *lastTask;
    /* Pointer the idle task in linked list */
	Task *idleTask;
}Process;

/*Struct which contains all data that handles processes for the system */
typedef struct tagProcessData
{
    /* ProcessList contains all processes of the system */
    Process *ProcessList[TOTAL_NO_PROCESSES];
    /* ProcessQueue is the actual queue of processes to be ran */
    Process *ProcessQueue[MAX_PROC_ITER];
    /* IdleProcess is the process which is next in queue to run */
    int8_t IdleProcess; //TODO: init to 1
    /* LastProcess is an offset to the last process ran in the ProcessList */
    int8_t LastProcess;
    /* The size of the current processQueue */
    int8_t CurrentQueueSize;
}ProcessData;

/* Functions that handle a process */
Process* createProcess(const char *name, int8_t pid);
void endProcess(Process *process);
void enqueueTask(Process *process, Task *task);
void dequeueTask(Process *process, Task *task);
void runIdleTask(Process *process);

/* Functions that handle a task */
Task* createTask(const char *name, Fun_t functionPointer, int16_t executionTime); 
void removeProcessTasks(Task *task);

/* Functions that handle the ProcessData struct */
void initProcessData(void);
Process** getProcessListPtr(void);
Process** getQueuePtr(void);
int8_t* getIdleProcess(void);
int8_t* getLastProcess(void);
void nullQueue(void);
Process* getProcessAtIndex(int8_t index);
int8_t* getCurrentQueueSize(void);
void enqueueProcess(Process *process);
void runIdleProcess(void);

/* RunTime functions for ProcessData struct */
void createProcessQueue(void);
int16_t peekIdleProcess();

/* Main Process Data for the system */
static ProcessData sched_processData;

#endif