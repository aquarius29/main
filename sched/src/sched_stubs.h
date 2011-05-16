
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

<<<<<<< HEAD
#ifndef _SCHED_STUBS_H
#define _SCHED_STUBS_H
=======
#ifndef SCHED_STUBS_H
#define SCHED_STUBS_H
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16

#include <stdint.h>


<<<<<<< HEAD
#ifdef CA
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t caInit(void);
/* dummy interface for stabilization code */
int16_t caRun(void);

#endif /* CA */
=======
// #ifdef CA
// /* stabilization groups header here */
// /* #include "../../ca/src/ca_sched.h" */
// 
// #else
// 
// /* dummy interface for stabilization code */
// int16_t caInit(void);
// /* dummy interface for stabilization code */
// int16_t caRun(void);
// 
// #endif /* CA */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16


#ifdef MOVE
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t moveInit(void);
/* dummy interface for stabilization code */
int16_t moveRun(void);

#endif /* MOVE */

<<<<<<< HEAD
#ifdef STAB
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t stabInit(void);
/* dummy interface for stabilization code */
int16_t stabRun(void);

#endif /* STAB */

=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16

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


<<<<<<< HEAD
#ifdef CONN
=======
#ifdef FILTER
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
<<<<<<< HEAD
int16_t connInit(void);
/* dummy interface for stabilization code */
int16_t connRun(void);

#endif /* CONN */
=======
int16_t filterInit(void);
/* dummy interface for stabilization code */
int16_t filterRun(void);

#endif /* FILTER */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16

#endif /* SCHED_STUBS_H */
