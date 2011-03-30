/* type Fun_t is type "function that returns int and takes no arguments */
// TODO: make it possible to generalize a functionpointer
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
void endProcess(Process *process);
Task* createTask(char *name, Fun_t functionPointer); 
void removeProcessTasks(Task *task);
void enqueueTask(Process *process, Task *task);
void dequeueTask(Process *process, Task *task);

void runIdleTask(Process *process);