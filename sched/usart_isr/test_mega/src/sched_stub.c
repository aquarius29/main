
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


#define TRUE 1
#define FALSE 0

static uint32_t LIGHT = TRUE;

void setupMega(void){
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
}

void doSomeScheduling(void){
    setupMega();

//    proto_init();
    
    while (1) {
//        digitalWrite(12, HIGH);
        // proto_run();
        // group_run();
        // put some home made delay here
        delay(500);
        if (LIGHT == TRUE) {
            digitalWrite(12, HIGH);
            LIGHT = FALSE;
        }
        else {
            digitalWrite(12, LOW);        
            LIGHT = TRUE;
        }
 //       delay(500);
    }
}