#include <stdio.h>
#include <stdint.h>

#ifdef PC
#ifdef WINDOWS
#include <Windows.h> /* for windows functions */
#else
#include <unistd.h>
#endif
#endif

#include "sched_stubs.h"

int16_t caRun(void)
{
	printf("running caRun\n");

    #ifdef WINDOWS
    Sleep(10);
    #else
    usleep(10);
    #endif
	return 0;
}

int16_t caRun2(void)
{
    printf("running caRun2\n");

    #ifdef WINDOWS
    Sleep(10);
    #else
    usleep(10);
    #endif
}

int16_t stabRun(void)
{
	printf("running stabRun\n");

    #ifdef WINDOWS
    Sleep(10);
    #else
    usleep(10);
    #endif
	return 0;
}

int16_t moveRun(void)
{
	printf("running moveRun\n");

    #ifdef WINDOWS
    Sleep(10);
    #else
    usleep(10);
    #endif
	return 0;
}

int16_t motoRun(void)
{
	printf("running motoRun\n");

    #ifdef WINDOWS
    Sleep(10);
    #else
    usleep(10);
    #endif
	return 0;
}

int16_t connRun(void)
{
	printf("running connRun\n");

    #ifdef WINDOWS
    Sleep(10);
    #else
    usleep(10);
    #endif
	return 0;
}