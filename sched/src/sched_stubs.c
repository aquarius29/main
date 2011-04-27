
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
    #ifdef DEBUG
	    printf("inside caRun\n");
	#endif /* DEBUG */
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
    #endif
	
	return 0;
}

int16_t stabRun(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside stabRun\n");
	#endif /* DEBUG */
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
    #endif
	
	return 0;
}

int16_t moveRun(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside moveRun\n");
	#endif /* DEBUG */
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
    #endif
	
	return 0;
}

int16_t motoRun(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside motoRun\n");
	#endif /* DEBUG */
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
    #endif
	
	return 0;
}

int16_t protoRun(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside protoRun\n");
	#endif /* DEBUG */
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
    #endif
	
	return 0;
}

int16_t connRun(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside connRun\n");
	#endif /* DEBUG */
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
    #endif
	
	return 0;
}

int16_t caInit(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside caInit\n");
	#endif /* DEBUG */
    #endif
	
	return 0;
}

int16_t stabInit(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside stabInit\n");
	#endif /* DEBUG */
    #endif
	
	return 0;
}

int16_t moveInit(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside moveInit\n");
	#endif /* DEBUG */
    #endif
	
	return 0;
}

int16_t motoInit(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside motoInit\n");
	#endif /* DEBUG */
	#endif

	return 0;
}

int16_t protoInit(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside protoInit\n");
	#endif /* DEBUG */
    #endif
	
	return 0;
}

int16_t connInit(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside connInit\n");
    #endif
	#endif /* DEBUG */
	
	return 0;
}