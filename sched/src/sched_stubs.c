
/*!
 *  @file sched_stubs.c
 *
 *  @brief Temporary solution to represent missing modules
 *
 *  @author Joakim
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
 *  @author Anders
 *  @date 2011-04-16
 *  @history    2011-04-10 - wrote original code
 *              2011-04-14 - added Doxygen comments
 *              2011-04-20 - Updated stubs to fake execution(Anders)
 */

=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
 *  @author Anders
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
 *  @date 2011-04-16
 *  @history    2011-04-10 - wrote original code
 *              2011-04-14 - added Doxygen comments
 *              2011-04-20 - Updated stubs to fake execution(Anders)
 */

<<<<<<< HEAD
#include <stdio.h>
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
#include <stdint.h>

#include "sched_stubs.h"

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
#ifdef PC
#include <stdio.h>

#ifdef WINDOWS
#include <Windows.h> /* for windows timing functions */
#else
#include <unistd.h>
#endif /* WIN */
#endif /* PC */

<<<<<<< HEAD
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
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
int16_t caRun(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside caRun\n");
	#endif /* DEBUG */
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
    #endif
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

int16_t stabRun(void) {
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside stabRun\n");
	#endif /* DEBUG */
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
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
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

int16_t moveRun(void) {
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside moveRun\n");
	#endif /* DEBUG */
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
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
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

int16_t motoRun(void) {
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside motoRun\n");
	#endif /* DEBUG */
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
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
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

int16_t protoRun(void) {
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside protoRun\n");
	#endif /* DEBUG */
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
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
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
int16_t connRun(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside connRun\n");
<<<<<<< HEAD
	#endif /* DEBUG */
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
    #endif
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
int16_t filterRun(void) {
	#ifdef DEBUG
	    printf("inside filterRun\n");
	#endif /* DEBUG */
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
	#endif /* DEBUG */
        #ifdef WINDOWS
        Sleep(10);
        #else
        usleep(10);
        #endif /* WINDOWS */
    #endif
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

int16_t caInit(void) {
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside caInit\n");
	#endif /* DEBUG */
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
	#ifdef PC
    #ifdef DEBUG
	    printf("inside caInit\n");
	#endif /* DEBUG */
    #endif
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

int16_t stabInit(void) {
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside stabInit\n");
	#endif /* DEBUG */
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
	#ifdef PC
    #ifdef DEBUG
	    printf("inside stabInit\n");
	#endif /* DEBUG */
    #endif
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

int16_t moveInit(void) {
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside moveInit\n");
	#endif /* DEBUG */
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
	#ifdef PC
    #ifdef DEBUG
	    printf("inside moveInit\n");
	#endif /* DEBUG */
    #endif
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

int16_t motoInit(void) {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	#ifdef PC
    #ifdef DEBUG
	    printf("inside motoInit\n");
	#endif /* DEBUG */
	#endif

=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
	#ifdef DEBUG
	    printf("inside motoInit\n");
	#endif /* DEBUG */
	
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
	#ifdef PC
    #ifdef DEBUG
	    printf("inside motoInit\n");
	#endif /* DEBUG */
	#endif

>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	return 0;
}

int16_t protoInit(void) {
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	#ifdef DEBUG
	    printf("inside protoInit\n");
	#endif /* DEBUG */
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
	#ifdef PC
    #ifdef DEBUG
	    printf("inside protoInit\n");
	#endif /* DEBUG */
    #endif
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	
	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
int16_t connInit(void) {
	#ifdef PC
    #ifdef DEBUG
	    printf("inside connInit\n");
    #endif
<<<<<<< HEAD
=======
int16_t filterInit(void) {
	#ifdef DEBUG
	    printf("inside filterInit\n");
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
int16_t filterInit(void) {
	#ifdef DEBUG
	    printf("inside filterInit\n");
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
	#endif /* DEBUG */
	
	return 0;
}