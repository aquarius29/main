
/*!
 *  @file sched_stub.c
 *
 *  @brief Module for simulating a scheduler calling protocol code
 *
 *  @author Joakim
 *
 *  @history    2011-05-10 - Started this module - Joakim
 */


/* WProgram.h needed for delay function */
#include "WProgram.h"

#include "sched_stub.h"
#include "proto_stub.h"

void doSomeScheduling(void){
    proto_init();
    
    while (1) {
        proto_run();
        delay(2000);
    }
}