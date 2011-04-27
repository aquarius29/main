
/*!
 *  @file sched_naive_sched.h
 *
 *  @brief Header file for the naive scheduers main module
 *
 *  @author Joakim
 *  @date 2011-04-14
 *  @history    2011-04-10 - wrote original code - Joakim
 *              2011-04-14 - added Doxygen comments - Joakim
 *              2011-04-21 - changed typedef to conform to coding
 *                           standard - Joakim
 */

#ifndef SCHED_NAIVE_SCHED_H
#define SCHED_NAIVE_SCHED_H

#include <stdint.h>

/* Fun_t is type "function that returns int and takes no arguments */
typedef int16_t(*sched_Fun_t)(void);

void sched_naive_init(void);

#endif /* SCHED_NAIVE_SCHED_H */
