/*!
 * @file moto_stubs.c
 * @brief Stub functions for use during testing.
 * @date 2011-04-18
 * @author Magnus Bergqvist
 * @version 1
 * @history 2011-04-18 - created
 * @details The functions in cunit_stubs.c is used during testing to \n
            replace any arduino library function that is called within \n
            the software.
 */
#include <stdint.h>
#include "moto_stubs.h"
#include "moto_driver_functions.h"
#include "moto_printer_functions.h"

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


