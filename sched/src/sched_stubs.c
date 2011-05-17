
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
#ifdef DEBUG
    DEBUG_MSG("inside caRun\n");
#endif /* DEBUG */
    SLEEP(10);
	
	return 0;
}

int16_t stabRun(void) {
#ifdef DEBUG
	DEBUG_MSG("inside stabRun\n");
#endif /* DEBUG */
    SLEEP(10);

	
	return 0;
}

int16_t moveRun(void) {
#ifdef DEBUG
	DEBUG_MSG("inside moveRun\n");
#endif /* DEBUG */
    SLEEP(10);
	
	return 0;
}

int16_t motoRun(void) {
/*
#ifdef DEBUG
    DEBUG_MSG("inside motoRun");
#endif /* DEBUG */
	
	return 0;
}

int16_t protoRun(void) {
#ifdef DEBUG
	DEBUG_MSG("inside protoRun\n");
#endif /* DEBUG */
    SLEEP(10);
	
	return 0;
}

int16_t connRun(void) {
#ifdef DEBUG
	DEBUG_MSG("inside connRun\n");
#endif /* DEBUG */
    SLEEP(10);
	
	return 0;
}

int16_t caInit(void) {
#ifdef DEBUG
	DEBUG_MSG("inside caInit\n");
#endif /* DEBUG */
	
	return 0;
}

int16_t stabInit(void) {
#ifdef DEBUG
	DEBUG_MSG("inside stabInit\n");
#endif /* DEBUG */
	
	return 0;
}

int16_t moveInit(void) {
#ifdef DEBUG
	DEBUG_MSG("inside moveInit\n");
#endif /* DEBUG */
	
	return 0;
}

int16_t motoInit(void) {
#ifdef DEBUG
	DEBUG_MSG("inside motoInit");
#endif /* DEBUG */

	return 0;
}

int16_t protoInit(void) {
#ifdef DEBUG
	DEBUG_MSG("inside protoInit\n");
#endif /* DEBUG */
	
	return 0;
}

int16_t connInit(void) {
#ifdef DEBUG
	DEBUG_MSG("inside connInit\n");
#endif /* DEBUG */
	
	return 0;
}