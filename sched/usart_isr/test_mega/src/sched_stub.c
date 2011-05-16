
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

void myDelay(uint32_t n);
void andersWait(uint32_t time);

void setupMega(void){
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
}

void myDelayMs(uint32_t n){
    uint32_t x;
    
    while (n--) {
        x = 300000;
        
        while (x--) {
            ;
        }
    }
}

void andersWait(uint32_t time){
    uint32_t start;
    
    start = millis();
    while (start+time > millis()) {
        ;
    }
}

void doSomeScheduling(void){
    setupMega();

    proto_init();
    
    while (1) {
        proto_run();
        group_run();
        // put some home made delay here
        myDelayMs(5000000);
        // andersWait(20);
    }
}