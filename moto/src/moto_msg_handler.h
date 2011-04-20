/**
 * Module:       parser.h
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description:  The typedef of the bitfield struct and
 *               all the prototypes for the functions used
 *               by tools.c, motor_control.c and parser.c.
 *
 */
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC_DBG
   #include <stdio.h>
#endif

//Parser functions
int examineID(msg_pointer mp);
void controlMotors(msg_pointer mp);
void specialMotorCommand(msg_pointer mp);
msg scanHexMsgSTDIN(void);
#ifdef ARDUINO_DBG
unsigned char serReadUnsignedChar(void);
#endif
