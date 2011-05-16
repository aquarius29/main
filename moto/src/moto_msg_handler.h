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
#include <stdint.h>

#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
=======

>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

//Parser functions
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
