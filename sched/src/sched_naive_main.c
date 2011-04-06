
#ifdef ARDUINO
#include <WProgram.h>
#endif

#include "sched_naive_sched.h"


int main(void){
    #ifdef ARDUINO
        init();
    #endif /* ARDUINO */
    
    while(1){
        sched_naive_init();
    }
    
    return 0;
}