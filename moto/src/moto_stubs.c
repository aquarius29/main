/*!
 * @file cunit_stubs.c
 * @brief Stub functions for use during testing.
 * @date 2011-04-18
 * @author Magnus Bergqvist
 * @version 1
 * @history 2011-04-18 - created
 * @details The functions in cunit_stubs.c is used during testing to \n
            replace any arduino library function that is called within \n
            the software.
 */
#include <stdio.h>
#include <stdint.h>
#include "moto_stubs.h"
#include "moto_driver_functions.h"


#ifdef MASTER_TEST_SUITE
    #define PRINTOUT_1(a)
    #define PRINTOUT_2(a, b)
#endif
#ifndef MASTER_TEST_SUITE
    /* PRINTOUT macro inspired by Henrik Sandklef */
    #define PRINTOUT_1(a) fprintf(stdout, a)
    #define PRINTOUT_2(a, b) fprintf(stdout, a, b)
#endif

/* writeMicroseconds from servo library from arduino standard libraries */
void writeMicroseconds(unsigned char value){
    PRINTOUT_2("writeMicroseconds received %d\n", value);
}

/* readMicroseconds from servo library from arduino standard libraries */
unsigned int readMicroseconds(void){
    PRINTOUT_1("readMicroseconds was called\n");
}

/* attach from servo library from arduino standard libraries */
unsigned char attach(unsigned char pin){
    PRINTOUT_2("attach was called for pin %d\n", pin);
}

/* analogWrite from arduino standard libraries, used for ordinary pwm out */
void analogWrite(int motor, uint16_t pulse){
    
    if(motor == LEFT_MOTOR){
        PRINTOUT_2("\nLEFT_MOTOR received %d\n", pulse);
    }
    if(motor == RIGHT_MOTOR){
        PRINTOUT_2("\nRIGHT_MOTOR received %d\n", pulse);
    }
    if(motor == FRONT_MOTOR){
        PRINTOUT_2("\nFRONT_MOTOR received %d\n", pulse);
    }
    if(motor == REAR_MOTOR){
        PRINTOUT_2("\nREAR_MOTOR received %d\n", pulse);
    }
}


