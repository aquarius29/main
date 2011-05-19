/*!
 * @file cunit_stubs.h
 * @brief header file for the test stub functions in cunit_stubs.c
 * @date 2011-04-18
 * @author Magnus Bergqvist
 * @version 1
 * @history 2011-04-18 - created
 * @details cunit_stubs.h contains prototypes of the functions in \n
            cunit_stubs.c which is used during testing to replace any \n
            arduino library function that is called within the software
 */
#ifndef MOTO_STUBS_H
    #define MOTO_STUBS_H
#include <stdint.h>

void analogWrite(int motor, uint16_t pulse);
#endif
