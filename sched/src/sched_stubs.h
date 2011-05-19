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

int16_t ca_init(void);
int16_t ca_run(void);

int16_t mov_init(void);
int16_t mov_run(void);

int16_t stab_init(void);
int16_t stab_run(void);

int16_t moto_init(void);
int16_t moto_run(void);

int16_t proto_init(void);
int16_t proto_run(void);

int16_t conn_init(void);
int16_t conn_run(void);

int16_t conn_init(void);
int16_t conn_run(void);

int16_t serial_init(void);
int16_t serial_run(void);

#endif /* SCHED_STUBS_H */
