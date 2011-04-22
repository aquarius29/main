
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
 */

#include <stdio.h>
#include <stdint.h>

#include "sched_stubs.h"

#ifdef WINDOWS
#include <Windows.h> /* for windows timing functions */
#else
#include <unistd.h>
#endif

int16_t caRun(void) {
	#ifdef PC
	    printf("inside caRun\n");
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
	#endif /* DEBUG */
	
	return 0;
}

int16_t stabRun(void) {
	#ifdef PC
	    printf("inside stabRun\n");
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
	#endif /* DEBUG */
	
	return 0;
}

int16_t moveRun(void) {
	#ifdef PC
	    printf("inside moveRun\n");
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
	#endif /* DEBUG */
	
	return 0;
}

int16_t motoRun(void) {
	#ifdef PC
	    printf("inside motoRun\n");
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
	#endif /* DEBUG */
	
	return 0;
}

int16_t protoRun(void) {
	#ifdef PC
	    printf("inside protoRun\n");
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
	#endif /* DEBUG */
	
	return 0;
}

int16_t connRun(void) {
	#ifdef PC
	    printf("inside connRun\n");
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
	#endif /* DEBUG */
	
	return 0;
}

int16_t caInit(void) {
	#ifdef PC
	    printf("inside caInit\n");
	#endif /* DEBUG */
	
	return 0;
}

int16_t stabInit(void) {
	#ifdef PC
	    printf("inside stabInit\n");
	#endif /* DEBUG */
	
	return 0;
}

int16_t moveInit(void) {
	#ifdef PC
	    printf("inside moveInit\n");
	#endif /* DEBUG */
	
	return 0;
}

int16_t motoInit(void) {
	#ifdef PC
	    printf("inside motoInit\n");
	#endif /* DEBUG */
	
	return 0;
}

int16_t protoInit(void) {
	#ifdef PC
	    printf("inside protoInit\n");
	#endif /* DEBUG */
	
	return 0;
}

int16_t connInit(void) {
	#ifdef PC
	    printf("inside connInit\n");
	#endif /* DEBUG */
	
	return 0;
}