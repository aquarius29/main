#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC_DBG
   #include <stdio.h>
#endif


int moto_init(void);
int moto_run(void);
