
#include <stdio.h>

#ifdef PC
/* header file for group code stubs here */
#endif /* PC */

#ifdef ARDUINO
/* header files for other groups interfaces here */
#endif /* ARDUINO */

#include "sched_naive_sched.h"

static int system_init(void);
static void naive_loop(Fun_t funArr[]);

void sched_naive_init(void){
    /* function pointers to modules init functions */
    Fun_t funArrInit[] = {  &protoInit,
                            &moveInit,
                            &caInit,
                            &stabInit,
                            &filterInit,
                            &motoInit };
    
    /* function pointers to modules run functions */
    Fun_t funArrRun[] = {   &protoRun,
                            &moveRun,
                            &protoRun,
                            &caRun,
                            &protoRun,
                            &stabRun,
                            &protoRun,
                            &filterRun,
                            &protoRun,
                            &motoRun };
    
    /* call all other groups inits */
    if (system_init() != 1) {
        #ifdef PC
            printf("Error in system initialization sequence!\n");
            exit(EXIT_FAILURE);
        #endif
        #ifdef ARDUINO
            /*  
             *  Do we have a way to give fatal error message on arduino,
             *  and exit? 
             */
            exit(EXIT_FAILURE);
            
        #endif
    }
    else {
        /* call loop, pass array as argument */
        naive_loop(funArrRun);
    }
}

int system_init(void){
    
}

void naive_loop(Fun_t funArr[]){
    
}