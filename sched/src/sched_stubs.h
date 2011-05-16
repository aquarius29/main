
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
<<<<<<< HEAD
<<<<<<< HEAD
#ifndef _SCHED_STUBS_H
#define _SCHED_STUBS_H
=======
#ifndef SCHED_STUBS_H
#define SCHED_STUBS_H
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
#ifndef SCHED_STUBS_H
#define SCHED_STUBS_H
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
#ifndef _SCHED_STUBS_H
#define _SCHED_STUBS_H
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04

#include <stdint.h>


<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
#ifdef CA
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t caInit(void);
/* dummy interface for stabilization code */
int16_t caRun(void);

#endif /* CA */
<<<<<<< HEAD
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
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
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04


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
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
#ifdef STAB
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t stabInit(void);
/* dummy interface for stabilization code */
int16_t stabRun(void);

#endif /* STAB */

<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04

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
<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONN
=======
#ifdef FILTER
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
#ifdef FILTER
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
#ifdef CONN
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
int16_t connInit(void);
/* dummy interface for stabilization code */
int16_t connRun(void);

#endif /* CONN */
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
int16_t filterInit(void);
=======
int16_t connInit(void);
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
/* dummy interface for stabilization code */
int16_t connRun(void);

<<<<<<< HEAD
#endif /* FILTER */
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
#endif /* CONN */
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04

#endif /* SCHED_STUBS_H */
