#include <stdio.h>

#include "scheduler.h"

/* stubs represent other modules */
#include "stubs.h"

// Hardcoded
#define NO_PROCESSES 5

/* This module prototypes the scheduler */

Process *g_processArr[NO_PROCESSES];

/* Sets up all the processes and tasks */
/* HARDCODED */
void setup(void)
{
	Process *process = createProcess("Motor Process");
	Task *task = createTask("runMotor", &motoRun);
	enqueueTask(process, task);
	g_processArr[0] = process;

	process = createProcess("CA Process");
	task = createTask("runCA", &caRun);
	enqueueTask(process, task);
	g_processArr[1] = process;

	process = createProcess("Move Process");
	task = createTask("runMove", &moveRun);
	enqueueTask(process, task);
	g_processArr[2] = process;

	process = createProcess("Stability Process");
	task = createTask("runStab", &stabRun);
	enqueueTask(process, task);
	g_processArr[3] = process;

	process = createProcess("Protocol Process");
	task = createTask("runProto", &protoRun);
	enqueueTask(process, task);
	g_processArr[4] = process;
}

/* In current implementation Loop will only run once 
* i.e. Run one task for each process */
void loop(void)
{
	int i;
	for(i = 0; i < NO_PROCESSES; i++)
	{
		Process *process = g_processArr[i];
		runIdleTask(process);
	}
}

void endProcesses(void)
{
	int i;
	for(i = 0; i < NO_PROCESSES; i++)
	{
		endProcess(g_processArr[i]);
	}
}

int main(void)
{
	setup();
	loop();
	endProcesses();
}