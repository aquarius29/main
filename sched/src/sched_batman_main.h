/***************************************************************************
 * Copyright (C) 2011  Anders Treptow
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
 *  @author Anders
 *  @date 2011-04-26
 *  @history    2011-04-26 - wrote header for sched_batman_main.c
 *              2011-05-19 - added license
 */

#ifndef _SCHED_BATMAN_MAIN_H_
#define _SCHED_BATMAN_MAIN_H_

#include <stdint.h>

int16_t sched_batman_init(void);
void sched_batman_profile(void);
void sched_batman_run(void);

#endif