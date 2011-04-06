
#ifdef ARDUINO
#include <WProgram.h>
#endif /* ARDUINO */

#include "sched_naive_sched.h"


int main(void){
    #ifdef ARDUINO
        init();
    #endif /* ARDUINO */
    
    sched_naive_init();
    
    return 0;
}