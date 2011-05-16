<<<<<<< HEAD
/**
 * Module:       parser.h
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description:  The typedef of the bitfield struct and
 *               all the prototypes for the functions used
 *               by tools.c, motor_control.c and parser.c.
 *
 */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include <stdint.h>

#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
=======

>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

//Parser functions
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
int examineID(msg_pointer mp);
void controlMotors(msg_pointer mp);
void specialMotorCommand(msg_pointer mp);
//msg scanHexMsgSTDIN(void);
//#ifdef ARDUINO_DBG
//uint8_t serReadUnsignedChar(void);
//#endif
=======
void examineID(msg_pointer mp);
void controlMotors(msg_pointer mp);
void specialMotorCommand(msg_pointer mp);
msg scanHexMsgSTDIN(void);
#ifdef ARDUINO
unsigned char serReadUnsignedChar(void);
#endif
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
int examineID(msg_pointer mp);
void controlMotors(msg_pointer mp);
void specialMotorCommand(msg_pointer mp);
msg scanHexMsgSTDIN(void);
#ifdef ARDUINO_DBG
unsigned char serReadUnsignedChar(void);
#endif
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
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

//Parser functions
int examineID(msg_pointer mp);
void controlMotors(msg_pointer mp);
void specialMotorCommand(msg_pointer mp);
//msg scanHexMsgSTDIN(void);
//#ifdef ARDUINO_DBG
//uint8_t serReadUnsignedChar(void);
//#endif
#endif
>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
