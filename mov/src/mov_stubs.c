
/*!
 *  @file mov_stubs.c
 *
 *  @brief Stub code for movements run and init functions
 *
 *  @author Joakim
 *  @date 2011-04-20
 *  @history    2011-04-20 - added this file
 */


#include <stdint.h>

#include "mov_interface.h"
#include "proto_mov_motor.h"

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
    
    return 0;
}

int16_t mov_run(void){
    #ifdef ARDUINO
        runMega();
    #endif /* ARDUINO */
    
    #ifdef PC
        runPC();
    #endif /* PC */
    
    return 0;
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
    unsigned char message = 0;
    
    message = 0x10;
    /* send message to motor here */
    write_motor(message);
}
