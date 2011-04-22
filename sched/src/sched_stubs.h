
/*!
 *  @file sched_stubs.h
 *
 *  @brief Temporary solution to represent missing modules
 *
 *  @author Joakim
 *  @date 2011-04-16
 *  @history    2011-04-10 - wrote original code
 *              2011-04-14 - added Doxygen comments
 */

#ifndef SCHED_STUBS_H
#define SCHED_STUBS_H

#include <stdint.h>


#ifdef CA
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t caInit(void);
/* dummy interface for stabilization code */
int16_t caRun(void);

#endif /* CA */


#ifdef MOVE
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t moveInit(void);
/* dummy interface for stabilization code */
int16_t moveRun(void);

#endif /* MOVE */

#ifdef STAB
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t stabInit(void);
/* dummy interface for stabilization code */
int16_t stabRun(void);

#endif /* STAB */


#ifdef MOTO
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t motoInit(void);
/* dummy interface for stabilization code */
int16_t motoRun(void);

#endif /* MOTO */


#ifdef PROTO
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t protoInit(void);
/* dummy interface for stabilization code */
int16_t protoRun(void);

#endif /* PROTO */


#ifdef CONN
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t connInit(void);
/* dummy interface for stabilization code */
int16_t connRun(void);

#endif /* CONN */

#endif /* SCHED_STUBS_H */
