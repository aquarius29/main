#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

static int moto_cyclesSinceLastMsg;

int moto_init(void);
int moto_run(void);
