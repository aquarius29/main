#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sched_profiler.h"

#include "moto_interface.h"
#include "stab_interface.h"
#include "ca_interface.h"
#include "mov_interface.h"


int16_t profile_mov(void)
{
    clock_t start;
    clock_t stop;
    int time;

    start = clock();
    mov_run();
    stop = clock();
    time = (int)(stop - start);

    return time;
}

int16_t profile_stab(void)
{
    clock_t start;
    clock_t stop;
    int time;

    start = clock();
    stab_run();
    stop = clock();
    time = (int)(stop - start);

    return time;
}

int16_t profile_ca(void)
{
    clock_t start;
    clock_t stop;
    int time;

    start = clock();
    ca_run();
    stop = clock();
    time = (int)(stop - start);

    return time;
}

int16_t profile_moto(void)
{
    clock_t start;
    clock_t stop;
    int time;

    start = clock();
    moto_run();
    stop = clock();
    time = (int)(stop - start);

    return time;
}

int16_t profile_init(void)
{
    moto_init();
    ca_init();
    mov_init();
    stab_init();
    return EXIT_SUCCESS;
}

int16_t profile_main(void)
{
    profile_init();
    int i;
    int16_t vTime[NO_PROCESSES];
    sched_Fun_t vFun[NO_PROCESSES] = {&profile_mov,
        &profile_ca, &profile_stab, &profile_mov};

    profile_init();
    for(i = 0; i < NO_PROCESSES; i++)
    {
        vFun[i] = (*vFun[i])();
    }

    printf("Profiler results\n*************************\n");
    for(i = 0; i < NO_PROCESSES; i++)
    {
        printf("%d - %d ms\n", i, vFun[i]);
    }
    return EXIT_SUCCESS;
}
