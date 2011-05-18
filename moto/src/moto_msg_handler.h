/**
 * Module:       parser.h
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description:  The typedef of the bitfield struct and
 *               all the prototypes for the functions used
 *               by tools.c, motor_control.c and parser.c.
 *
 */
#ifndef MOTO_MSG_HANDLER_H
    #define MOTO_MSGHANDLER_H
#include <stdint.h>

#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

/* Parser functions */
int examineID(msg_pointer mp);
void controlMotors(msg_pointer mp);
void specialMotorCommand(msg_pointer mp);

#endif
