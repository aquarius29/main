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
#include "moto_printer_functions.h"

/* writeMicroseconds from servo library from arduino standard libraries */
void writeMicroseconds(unsigned char value){
    PRINT_STRING("writeMicroseconds received ");
    PRINT_DEC(value);
    PRINT_NEW_LINE;
}

/* readMicroseconds from servo library from arduino standard libraries */
unsigned int readMicroseconds(void){
    PRINT_STRING("readMicroseconds was called");
    PRINT_NEW_LINE;
}

/* attach from servo library from arduino standard libraries */
unsigned char attach(unsigned char pin){
    PRINT_STRING ("attach was called for pin ");
    PRINT_DEC(pin);
    PRINT_NEW_LINE;
}

/* analogWrite from arduino standard libraries, used for ordinary pwm out */
void analogWrite(int motor, uint16_t pulse){
    
    if(motor == LEFT_MOTOR){
        PRINT_NEW_LINE;
        PRINT_STRING ("LEFT_MOTOR received:  ");
        PRINT_DEC(pulse);
        PRINT_NEW_LINE;
    }
    if(motor == RIGHT_MOTOR){
        PRINT_NEW_LINE;
        PRINT_STRING ("RIGHT_MOTOR received  ");
        PRINT_DEC(pulse);
        PRINT_NEW_LINE;
    }
    if(motor == FRONT_MOTOR){
        PRINT_NEW_LINE;
        PRINT_STRING ("FRONT_MOTOR received  ");
        PRINT_DEC(pulse);
        PRINT_NEW_LINE;
    }
    if(motor == REAR_MOTOR){
        PRINT_NEW_LINE;
        PRINT_STRING ("REAR_MOTOR received  ");
        PRINT_DEC(pulse);
        PRINT_NEW_LINE;
    }
}


