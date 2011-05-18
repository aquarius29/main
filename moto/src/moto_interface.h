/*!
 * @author Kristofer Hansson Aspman, Björn Eriksson, Magnus Bergqvist
 * @file moto_interface.c
 * @version v0.05
 * @date 2011-05-11
 * @history 2011-05-17 - Update after code review \n
                        (Magnus) \n
            2011-05-11 - Worked with ifdefs \n
                        (Magnus, Björn) \n
            2011-04-26 - Major cleanup and restructuring of the code\n
                        (Magnus, Björn, Kristofer) \n
            2011-04-10 - Created first version \n
                        (Magnus, Björn, Kristofer) \n

 * @brief Contains the implementations of moto_init and moto_run.\n
          Global variables set are: mp (a pointer to the hexadecimal \n
          message read from the protocol).
 */


#ifndef MOTO_INTERFACE_H
    #define MOTO_INTERFACE_H
#include <stdint.h>
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif

#ifdef ARDUINO
    #include "WProgram.h"
    #include "../include/Servo.h"
#endif

#ifdef ARDUINO
extern Servo escRight;
extern Servo escLeft;
extern Servo escFront;
extern Servo escRear;
#endif

/* 
 * Stores the number of cycles since the last message was written to the
 * protocol by the movement group.
 */
static int moto_cyclesSinceLastMsg;

uint16_t moto_init(void);
uint16_t moto_run(void);
#endif
