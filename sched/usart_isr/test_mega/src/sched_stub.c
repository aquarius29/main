
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
#include "group_stub.h"

void setupMega(void){
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
}

void doSomeScheduling(void){
    setupMega();

    proto_init();
    
    while (1) {
        proto_run();
        group_run();
//        delay(50);
    }
}