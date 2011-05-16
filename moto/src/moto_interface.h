<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
#ifdef ARDUINO
   #include "WProgram.h"
<<<<<<< HEAD
<<<<<<< HEAD
   #include "../include/Servo.h"
=======
#ifdef ARDUINO
   #include "WProgram.h"
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#elif defined PC
   #include <stdio.h>
#endif

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#ifdef ARDUINO
    extern Servo escRight;
    extern Servo escLeft;
    extern Servo escFront;
    extern Servo escRear;
#endif


static int moto_cyclesSinceLastMsg;
=======
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
static int moto_cyclesSinceLastMsg;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
static int moto_cyclesSinceLastMsg;
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

int moto_init(void);
int moto_run(void);
=======
/*!@author Kristofer Hansson Aspman, Björn Eriksson, Magnus Bergqvist
 * @file moto_interface.c
 * @version v0.05
 * @date 2011-05-11
 * @history 2011-05-11 - Worked with ifdefs
                        (Magnus, Björn)
            2011-04-26 - Major cleanup and restructuring of the code\n
                        (Magnus, Björn, Kristofer)
            2011-04-10 - Created first version
                        (Magnus, Björn, Kristofer)

 * @brief Contains the implementations of moto_init and moto_run.\n
          Global variables set are: mp (a pointer to the hexadecimal message
 *        read from the protocol).
 */

#ifndef MOTO_INTERFACE_H
    #define MOTO_INTERFACE_H
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif

#ifdef ARDUINO
   #include "WProgram.h"
   #include "../include/Servo.h"
#elif defined PC
   #include <stdio.h>
#endif

#ifdef ARDUINO
extern Servo escRight;
extern Servo escLeft;
extern Servo escFront;
extern Servo escRear;
#endif

/* Stores the number of cycles since the last message was written to the
 * protocol by the movement group.
 */
static int moto_cyclesSinceLastMsg;

int moto_init(void);
int moto_run(void);
#endif
>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
