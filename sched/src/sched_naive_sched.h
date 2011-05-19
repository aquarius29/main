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
#ifdef NAIVE

#ifndef _SCHED_NAIVE_SCHED_H
#define _SCHED_NAIVE_SCHED_H

#include <stdint.h>

/* Fun_t is type "function that returns int and takes no arguments */
typedef int16_t(*sched_Fun_t)(void);

void sched_naive_init(void);

#endif /* SCHED_NAIVE_SCHED_H */

#endif
