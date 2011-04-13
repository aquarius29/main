
#ifdef ARDUINO
#include "WProgram.h"
#endif /* ARDUINO */

#include "sched_interface.h"
#include "sched_naive_sched.h"


int sched_naive_main(void){
    #ifdef ARDUINO
        init();
    #endif /* ARDUINO */
    
    sched_naive_init();
    
    return 0;
}