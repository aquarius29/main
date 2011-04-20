#ifndef __sched_stubs_h
#define __sched_stubs_h

#include <stdio.h>
#include <stdint.h>

/* dummy interface for collision avoidance code */
int16_t caRun(void);

int16_t caRun2(void);

/* dummy interface for stabilization code */
int16_t stabRun(void);

/* dummy interface for movement code */
int16_t moveRun(void);

/* dummy interface for motor code */
int16_t motoRun(void);

/* dummy interface for protocol code */
int16_t connRun(void);
#endif
