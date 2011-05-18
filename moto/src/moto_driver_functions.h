/*!
 * Module:       motor_control.h
 * Author(s):    Kristofer Hansson Aspman
 *               Magnus Bergqvist
 *
 * Description:  The typedef of the bitfield struct and
 *               all the prototypes for the functions used
 *               by tools.c, motor_control.c and parser.c.
 */
#ifndef MOTO_DRIVER_FUNCTIONS_H
    #define MOTO_DRIVER_FUNCTIONS_H

#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
#ifdef ARDUINO
   #include "WProgram.h"
#endif
#include <stdint.h>

#define NORMAL_STEP 5
#define PANIC_STEP 50

/* defines which "pin" in the arduino, to be changed further on */
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 3
#define FRONT_MOTOR 5
#define REAR_MOTOR 6


/* defines maximum and minimum pulse width in µs for every motor 
   i.e. at which pulse the motor starts turning and at which pulse it
   reaches its max speed */
#define MIN_PULSE_FRONT 1044
#define MAX_PULSE_FRONT 1900
#define MIN_PULSE_REAR 1044
#define MAX_PULSE_REAR 1900
#define MIN_PULSE_LEFT 1044
#define MAX_PULSE_LEFT 1900
#define MIN_PULSE_RIGHT 1044
#define MAX_PULSE_RIGHT 1900

/* defines the min and max values (pulse width in µs that are allowed) */
#define MIN_ESC_PULSE 1000
#define MAX_ESC_PULSE 2000

#define IDLE_SPEED 1100
#define STOP_PULSE 1000

/* defines hover speed pulse width in µs for every motor */
#define HOVER_PULSE_RIGHT 1400
#define HOVER_PULSE_LEFT 1400
#define HOVER_PULSE_FRONT 1400
#define HOVER_PULSE_REAR 1400

extern uint16_t rightPulse;
extern uint16_t leftPulse;
extern uint16_t frontPulse;
extern uint16_t rearPulse;


/*Motor pulse modification*/
void moto_startMotors(void);
void moto_stopMotors(void);
void moto_hover(void);
void moto_goForward(void);
void moto_goBackward(void);
void moto_strafeRight(void);
void moto_strafeLeft(void);
void moto_rotateLeft(void);
void moto_rotateRight(void);

void moto_increaseAllNormal(void);
void moto_increaseAllPanic(void);

void moto_decreaseAllNormal(void);
void moto_decreaseAllPanic(void);

void moto_increaseLeftNormal(void);
void moto_increaseRightNormal(void);
void moto_increaseFrontNormal(void);
void moto_increaseRearNormal(void);
void moto_increaseLeftPanic(void);
void moto_increaseRightPanic(void);
void moto_increaseFrontPanic(void);
void moto_increaseRearPanic(void);

void moto_decreaseLeftNormal(void);
void moto_decreaseRightNormal(void);
void moto_decreaseFrontNormal(void);
void moto_decreaseRearNormal(void);
void moto_decreaseLeftPanic(void);
void moto_decreaseRightPanic(void);
void moto_decreaseFrontPanic(void);
void moto_decreaseRearPanic(void);

void printMotorStatus(void);

void moto_left_motor(unsigned char,unsigned char);
void moto_right_motor(unsigned char,unsigned char);
void moto_front_motor(unsigned char,unsigned char);
void moto_rear_motor(unsigned char,unsigned char);

uint16_t moto_LimitIncrease(uint16_t currentPulse, uint16_t increment);
uint16_t moto_LimitDecrease(uint16_t currentPulse, uint16_t decrement);

uint16_t moto_map(uint16_t actual, uint16_t out_boundary1,
                                    uint16_t out_boundary2);

#endif
