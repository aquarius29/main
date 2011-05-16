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


static int moto_cyclesSinceLastMsg;

int moto_init(void);
int moto_run(void);
