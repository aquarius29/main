#include <stdio.h>

#include "scheduler.h"
#include "sched_stubs.h"

/* NOTE: Most of this module is hardcoded, prototype implementation */

Process *g_processArr[NO_PROCESSES];

void setup(void)
{
	Process *process = createProcess("MotorProcess");
	Task *task = createTask("runMotor", &motoRun);
	enqueueTask(process, task);
	g_processArr[0] = process;
}

void loop(void)
{
	int i;
	for(i = 0; i < 1; i++)
	{
		Process *process = g_processArr[i];
		runIdleTask(process);
	}
}

int main(void)
{
	setup();
	loop();
}
