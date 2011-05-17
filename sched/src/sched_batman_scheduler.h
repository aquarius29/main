/*!
*   @file sched_scheduler.h
*
*   @brief Header file for the batman scheduler's main functions.
*
*   @author Anders Treptow
*   @date 2011-03-29
*
*   @history    2011-03-29 wrote prototype
*               2011-04-04 created process structure
*               2011-04-10 created processData structure
*               2011-04-11 all enqueueing written
*               2011-04-16 time-constraints implemented
*               2011-04-19 added Doxygen comments
*               2011-04-26 changed name of typedef global function pointer
*/

#ifndef __SCHED_BATMAN_SCHEDULER_H_
#define __SCHED_BATMAN_SCHEDULER_H_

#include <stdint.h>
#define TOTAL_NO_PROCESSES 3 /* Total number of processes */
#define MAX_PROC_ITER 100 /* maximum number of processes per iteration*/
#define TIMEFRAME_MS 100 /* The timeframe amount in milliseconds */

/* Defines all Process ID's */
#define MOTOR_PID 1
#define CA_PID 2
#define MOVE_PID 3
#define STAB_PID 4
#define CONN_PID 5

/* type Fun_t is type "function that 
* returns int16_t and takes no arguments */
typedef int16_t(*sched_Fun_t)(void);

/* struct Task points to function which perfoms given task 
* Is tasks are linked in a linked list structure */
typedef struct tagTask {
    /* The time it takes to execute the function pointed to */
	int16_t executionTime;
    /* Pointer to function */
	sched_Fun_t functionPointer;
    /* Pointer to the next Task in linked list */
	struct tagTask *nextTask;
}Task;

/* struct Process consists of 1...n number of Tasks put into an array */
typedef struct tagProcess {
    int8_t Pid; /* Process ID */
	int8_t priority; /* Priority of process in range of 0-100 */
	int8_t no_tasks; /* Numbers of tasks which the process contains */
    int8_t peekLayer; /* At what layer of tasks the last peeking was at */
	Task *firstTask; /* Pointer to first task in linked list */
	Task *lastTask; /* Pointer to last task in linked list */
	Task *idleTask; /* Pointer the idle task in linked list */
}Process;

/*Struct which contains all data that handles processes for the system */
typedef struct tagProcessData {
    /* ProcessList contains all processes of the system */
    Process *processList[TOTAL_NO_PROCESSES];
    /* ProcessQueue is the actual queue of processes to be ran */
    Process *processQueue[MAX_PROC_ITER];
    /* LastProcess is an offset to the last process ran in the ProcessList */
    int8_t idleProcessToSchedule;
    /* The size of the current processQueue */
    int8_t currentQueueSize;
    /* The total execution time for the processQueue */
    int16_t totalExecutionTime;
}ProcessData;

/* Functions that handle a process */
int16_t process_setup(ProcessData *pProcessData, 
    sched_Fun_t funArrRun[TOTAL_NO_PROCESSES]);
Process* create_process(int8_t pid);
void end_process(Process *process);
void enqueue_task(Process *process, Task *task);
void runIdle_task(Process *process);
Task* peek_process(Process *process, int16_t layer);

/* Functions that handle a task */
Task* create_task(sched_Fun_t functionPointer, int16_t executionTime);
void remove_process_tasks(Task *task);

/* Functions that handle the ProcessData struct */
int16_t init_process_data(void);
int16_t system_init(sched_Fun_t funArrInit[TOTAL_NO_PROCESSES]);
void clean_process_data(void);
ProcessData* get_process_data(void);
void null_queue(void);
void enqueue_process(Process *process);
void run_process(int8_t processIndex);

/* RunTime functions for ProcessData struct */
void create_process_queue(int16_t excessTime);

/* Main Process Data for the system,
* should only be access via getProcessData() */
static ProcessData sched_processData;

#endif