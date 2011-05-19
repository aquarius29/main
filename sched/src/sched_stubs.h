/***************************************************************************
 * Copyright (C) 2011  <name of author>
 * 
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

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

#ifndef _SCHED_STUBS_H
#define _SCHED_STUBS_H

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
