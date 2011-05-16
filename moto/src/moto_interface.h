<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
#ifdef ARDUINO
   #include "WProgram.h"
<<<<<<< HEAD
   #include "../include/Servo.h"
=======
#ifdef ARDUINO
   #include "WProgram.h"
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
#elif defined PC
   #include <stdio.h>
#endif

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

int moto_init(void);
int moto_run(void);
