
/*!
 *  @file sched_naive_main.c
 *
 *  @brief At the moment this is the naive schedulers entry point \n
 *  it's made available as the naive schedulers interface, this is temporary
 *  
 *  @author Joakim
 *  @date 2011-04-14
 *
 *  @history    2011-04-10 - wrote original code
 *              2011-04-14 - added Doxygen comments
 */

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