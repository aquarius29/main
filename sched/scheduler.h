#define NO_PROCESSES 5

/* type Fun_t is type "function that returns int and takes no arguments */
typedef int(*Fun_t)(void);

/* struct Task points to function which perfoms given task */
typedef struct tagTask
{
	char *name;
	int duration;
	Fun_t functionPointer;
	struct tagTask *nextTask;
}Task;

/* struct Process consists of 1...n number of Tasks put into an array */
typedef struct tagProcess
{
	char *name;
	int priority;
	int no_tasks;
	Task *firstTask;
	Task *lastTask;
	Task *idleTask;
}Process;

Process* createProcess(char *name);
Task* createTask(char *name, Fun_t functionPointer); // TODO: make possible to generalize functionpointer
void enqueueTask(Process *process, Task *task);
void dequeueTask(Process *process, Task *task);

void runIdleTask(Process *process);