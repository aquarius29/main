


#include <stdint.h>

#include "mov_interface.h"
/* include protocols interface here */

static void initMega(void);
static void runMega(void);
static void initPC(void);
static void runPC(void);

int16_t mov_init(void){
    #ifdef ARDUINO
        initMega();
    #endif /* ARDUINO */
    
    #ifdef PC
        initPC();
    #endif /* PC */
    
    return 1;
}

int16_t mov_run(void){
    #ifdef ARDUINO
        runMega();
    #endif /* ARDUINO */
    
    #ifdef PC
        runPC();
    #endif /* PC */
    
    return 1;
}

void initMega(void){
    /* mega-board specific initialization here */
}

void initPC(void){
    /* pc-board specific initialization here */    
}

void runMega(void){
    /* send message to motor here */
}

void runPC(void){
    /* send message to motor here */
}
