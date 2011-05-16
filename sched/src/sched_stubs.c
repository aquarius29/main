
/*!
 *  @file sched_stubs.c
 *
 *  @brief Temporary solution to represent missing modules
 *
 *  @author Joakim
<<<<<<< HEAD
 *  @author Anders
 *  @date 2011-04-16
 *  @history    2011-04-10 - wrote original code
 *              2011-04-14 - added Doxygen comments
 *              2011-04-20 - Updated stubs to fake execution(Anders)
 */

=======
 *  @date 2011-04-16
 *  @history    2011-04-10 - wrote original code
 *              2011-04-14 - added Doxygen comments
 */

#include <stdio.h>
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
#include <stdint.h>

#include "sched_stubs.h"

<<<<<<< HEAD
#ifdef PC
#include <stdio.h>

#ifdef WINDOWS
#include <Windows.h> /* for windows timing functions */
#else
#include <unistd.h>
#endif /* WIN */
#endif /* PC */

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
=======
int16_t caRun(void) {
	#ifdef DEBUG
	    printf("inside caRun\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

int16_t stabRun(void) {
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside stabRun\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

int16_t moveRun(void) {
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside moveRun\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

int16_t motoRun(void) {
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside motoRun\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

int16_t protoRun(void) {
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside protoRun\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

<<<<<<< HEAD
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
=======
int16_t filterRun(void) {
	#ifdef DEBUG
	    printf("inside filterRun\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

int16_t caInit(void) {
<<<<<<< HEAD
	#ifdef PC
    #ifdef DEBUG
	    printf("inside caInit\n");
	#endif /* DEBUG */
    #endif
=======
	#ifdef DEBUG
	    printf("inside caInit\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

int16_t stabInit(void) {
<<<<<<< HEAD
	#ifdef PC
    #ifdef DEBUG
	    printf("inside stabInit\n");
	#endif /* DEBUG */
    #endif
=======
	#ifdef DEBUG
	    printf("inside stabInit\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

int16_t moveInit(void) {
<<<<<<< HEAD
	#ifdef PC
    #ifdef DEBUG
	    printf("inside moveInit\n");
	#endif /* DEBUG */
    #endif
=======
	#ifdef DEBUG
	    printf("inside moveInit\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

int16_t motoInit(void) {
<<<<<<< HEAD
	#ifdef PC
    #ifdef DEBUG
	    printf("inside motoInit\n");
	#endif /* DEBUG */
	#endif

=======
	#ifdef DEBUG
	    printf("inside motoInit\n");
	#endif /* DEBUG */
	
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	return 0;
}

int16_t protoInit(void) {
<<<<<<< HEAD
	#ifdef PC
    #ifdef DEBUG
	    printf("inside protoInit\n");
	#endif /* DEBUG */
    #endif
=======
	#ifdef DEBUG
	    printf("inside protoInit\n");
	#endif /* DEBUG */
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	
	return 0;
}

<<<<<<< HEAD
int16_t connInit(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside connInit\n");
    #endif
=======
int16_t filterInit(void) {
	#ifdef DEBUG
	    printf("inside filterInit\n");
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
	#endif /* DEBUG */
	
	return 0;
}