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
 *  @file sched_stubs.c
 *
 *  @brief Temporary solution to represent missing modules
 *
 *  @author Joakim
 *  @author Anders
 *  @date 2011-04-16
 *  @history    2011-04-10 - wrote original code
 *              2011-04-14 - added Doxygen comments
 *              2011-04-20 - Updated stubs to fake execution(Anders)
 *              2011-05-10 - Updated with arduino related debugging(Anders)
 */

#include <stdint.h>

#include "sched_stubs.h"

#ifdef PC
#include <stdio.h>

#ifdef WINDOWS
#include <Windows.h> /* for windows timing functions */
#define SLEEP(a) Sleep(a)
#else
#include <unistd.h>
#define SLEEP(a) usleep(a)
#endif /* WIN */

#define DEBUG_MSG(msg) printf(msg)

#elif ARDUINO
#include "WProgram.h"

#define SLEEP(a) delay(a)
#define DEBUG_MSG(msg) Serial.println(msg)
#endif /* PC ARDUINO */

int16_t ca_run(void){
    DEBUG_MSG("inside ca_run\n");
    SLEEP(10);
	
	return 0;
}

int16_t stab_run(void){
	DEBUG_MSG("inside stab_run\n");
    SLEEP(10);

	
	return 0;
}

int16_t mov_run(void){
	DEBUG_MSG("inside mov_run\n");
    SLEEP(10);
	
	return 0;
}

int16_t moto_run(void){
    DEBUG_MSG("inside moto_run");
	
    return 0;
}

int16_t proto_run(void){
	DEBUG_MSG("inside proto_run\n");
    SLEEP(10);
	
	return 0;
}

int16_t conn_run(void){
	DEBUG_MSG("inside conn_run\n");
    SLEEP(10);
	
	return 0;
}

int16_t serial_run(void){
    DEBUG_MSG("inside serial_run\n");
    SLEEP(10);

    return 0;
}

int16_t ca_init(void){
	DEBUG_MSG("inside ca_init\n");
	
	return 0;
}

int16_t stab_init(void){
	DEBUG_MSG("inside stab_init\n");
	
	return 0;
}

int16_t mov_init(void){
	DEBUG_MSG("inside mov_init\n");
	
	return 0;
}

int16_t moto_init(void){
	DEBUG_MSG("inside moto_init");

	return 0;
}

int16_t proto_init(void){
	DEBUG_MSG("inside proto_init\n");
	
	return 0;
}

int16_t conn_init(void){
	DEBUG_MSG("inside conn_init\n");
	
	return 0;
}

int16_t serial_init(void){
    DEBUG_MSG("inside serial_init");

    return 0;
}