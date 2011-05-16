<<<<<<< HEAD
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
#ifdef ARDUINO
   #include "WProgram.h"
   #include "../include/Servo.h"
=======
#ifdef ARDUINO
   #include "WProgram.h"
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
#elif defined PC
   #include <stdio.h>
#endif

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

int moto_init(void);
int moto_run(void);
