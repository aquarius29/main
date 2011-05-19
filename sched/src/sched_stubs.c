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

int16_t caRun(void) {
    DEBUG_MSG("inside caRun\n");
    SLEEP(10);
	
	return 0;
}

int16_t stabRun(void) {
	DEBUG_MSG("inside stabRun\n");
    SLEEP(10);

	
	return 0;
}

int16_t moveRun(void) {
	DEBUG_MSG("inside moveRun\n");
    SLEEP(10);
	
	return 0;
}

int16_t motoRun(void) {
    DEBUG_MSG("inside motoRun");
	
    return 0;
}

int16_t protoRun(void) {
	DEBUG_MSG("inside protoRun\n");
    SLEEP(10);
	
	return 0;
}

int16_t connRun(void) {
	DEBUG_MSG("inside connRun\n");
    SLEEP(10);
	
	return 0;
}

int16_t caInit(void) {
	DEBUG_MSG("inside caInit\n");
	
	return 0;
}

int16_t stabInit(void) {
	DEBUG_MSG("inside stabInit\n");
	
	return 0;
}

int16_t moveInit(void) {
	DEBUG_MSG("inside moveInit\n");
	
	return 0;
}

int16_t motoInit(void) {
	DEBUG_MSG("inside motoInit");

	return 0;
}

int16_t protoInit(void) {
	DEBUG_MSG("inside protoInit\n");
	
	return 0;
}

int16_t connInit(void) {
	DEBUG_MSG("inside connInit\n");
	
	return 0;
}