
/*!
 *  @file sched_naive_sched.h
 *
 *  @brief Header file for the naive scheduers main module
 *
 *  @author Joakim
 *  @date 2011-04-16
 *  @history    2011-04-10 - wrote original code
 *              2011-04-14 - added Doxygen comments
 */

#include <stdint.h>

#ifndef SCHED_NAIVE_SCHED_H
#define SCHED_NAIVE_SCHED_H

/* Fun_t is type "function that returns int and takes no arguments */
typedef int16_t(*Fun_t)(void);

void sched_naive_init(void);

#endif /* SCHED_NAIVE_SCHED_H */