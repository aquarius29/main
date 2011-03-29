#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "scheduler.h"

Process* createProcess(char *name)
{
	int strLen = strlen(name) + 1;
	Process *process = (Process*)malloc(sizeof(Process));
	memset(process, 0, sizeof(Process));
	process->name = (char*)malloc(strLen);
	memset(process->name, 0, sizeof(strLen));
	strncpy(process->name, name, strLen);
	return process;
}

Task* createTask(char *name, Fun_t functionPointer)
{
	int strLen = strlen(name) + 1;
	Task *task = (Task*)malloc(sizeof(Task));
	memset(task, 0, sizeof(Task));
	task->name = (char*)malloc(strLen);
	memset(task->name, 0, strLen);
	strncpy(task->name, name, strLen);
	task->functionPointer = functionPointer;
	return task;
}

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

// TODO
void dequeueTask(Process *process, Task *task)
{ }

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