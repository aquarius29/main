/***************************************************************************
 * Copyright (C) 2011  Joakim Gross
 * 
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

/*!
 *  @file sched_stub.c
 *
 *  @brief  Module for simulating a scheduler calling protocol and \n
 *          group stub code \n
 *
 *  @author Joakim
 *
 *  @history    2011-05-10 - Started this module - Joakim \n
 *              2011-05-19 - Added license text and additional comments \n
 *                           - Joakim \n
 */

#include "WProgram.h"

#include "sched_stub.h"
#include "serial_interface.h"
#include "group_stub.h"

#define TRUE 1
#define FALSE 0

void myDelay(uint32_t n);
void andersWait(uint32_t time);

void setupMega(void){
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
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

/* millis() messes with interrupts globally */
void andersWait(uint32_t time){
    uint32_t start;
    
    start = millis();
    while (start+time > millis()) {
        ;
    }
}

void doSomeScheduling(void){
    setupMega();

    serial_init();
    
    while (1) {
        serial_run();
        group_run();
        // put some home made delay here
        myDelayMs(5000000);
        // andersWait(20);
    }
}