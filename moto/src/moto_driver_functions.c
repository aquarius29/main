/*!
 * @author Kristofer Hansson Aspman,
 *         Björn Eriksson,
 *         Magnus Bergqvist
 *         
 * @file moto_driver_functions.c
 * @version v0.03
 * @date 2011-05-09
 *
 * @brief Contains the functions that sets the pulse width of the \n
 *        different motors.
 *
 * @history 2011-05-17: Implemented moto_map() function \n
                        (Magnus) \n
            2011-05-09: Added map function and moved printout macros \n
                        to moto_printer_functions, changed the printouts \n
                        to fully comply with the new macro style \n
                        (Magnus) \n
            2011-04-03: Created the file. \n 
                        (Kristofer)
 */
 
#include "moto_driver_functions.h"
#include <stdint.h>
#include <math.h>
#include "moto_interface.h"
#include "moto_printer_functions.h"

#ifdef ARDUINO
    #include "WProgram.h"
    #include "../include/Servo.h"
#elif defined PC
    #include"moto_stubs.h"
#endif

/* 
 * These are the variables keeping track of the 
 * current state (pulse width) of each motor. 
 */
uint16_t rightPulse;
uint16_t leftPulse;
uint16_t frontPulse;
uint16_t rearPulse;


/*
 * Function:    void moto_startMotors()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Sets the pulse width to a state where
 *              all motors starts spinning but the
 *              drone does not lift off.
 */

void moto_startMotors(void){
    leftPulse = IDLE_SPEED;
    rightPulse = IDLE_SPEED;
    frontPulse = IDLE_SPEED;
    rearPulse = IDLE_SPEED;
#ifdef ARDUINO 
    escRight.writeMicroseconds(rightPulse);
    escLeft.writeMicroseconds(leftPulse);
    escFront.writeMicroseconds(frontPulse);
    escRear.writeMicroseconds(rearPulse);
#elif defined PC
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#endif
    PRINT_STRING("Starting all motors");
    PRINT_NEW_LINE;
}

/*
 * Function:    void moto_stopMotors()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Stops all motors, i.e. sets the
 *              pulse width to zero.
 */
void moto_stopMotors(void){
    rightPulse = STOP_PULSE;
    leftPulse = STOP_PULSE;
    frontPulse = STOP_PULSE;
    rearPulse = STOP_PULSE;
#ifdef ARDUINO 
    escRight.writeMicroseconds(rightPulse);
    escLeft.writeMicroseconds(leftPulse);
    escFront.writeMicroseconds(frontPulse);
    escRear.writeMicroseconds(rearPulse);
#elif defined PC
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#endif
    PRINT_STRING("Stopping all motors");
    PRINT_NEW_LINE;
}
/*
 * Function:    void moto_hover()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Sets all motors to the same pulse width
 *              where to drone shall stay in hover state
 */
void moto_hover(void){
    rightPulse = HOVER_PULSE_RIGHT;
    leftPulse = HOVER_PULSE_LEFT;
    frontPulse = HOVER_PULSE_FRONT;
    rearPulse = HOVER_PULSE_REAR;
#ifdef ARDUINO 
    escRight.writeMicroseconds(rightPulse);
    escLeft.writeMicroseconds(leftPulse);
    escFront.writeMicroseconds(frontPulse);
    escRear.writeMicroseconds(rearPulse);
#elif defined PC
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#endif
    PRINT_STRING("Hovering");
    PRINT_NEW_LINE;    
}

/*
 * Function:    void moto_goForward()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Increases the pulse width of
 *              of the rear motor and decreases
 *              the pulse width of the front
 *              motor. This makes the drone go
 *              forward.
 */
void moto_goForward(void){
    moto_increaseRearNormal();
    moto_decreaseFrontNormal();
}
/*
 * Function:    void moto_goBackward()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Decreases the pulse width of
 *              of the rear motor and increases
 *              the pulse width of the front
 *              motor. This makes the drone go
 *              backward.
 */
void moto_goBackward(void){
    moto_decreaseRearNormal();
    moto_increaseFrontNormal();
}

/*
 * Functions:   moto_strafeRight()
 *              moto_strafeLeft()
 *
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Increases either right or
 *              left motor and decreases
 *              the other in order to make
 *              the drone fly sideways to
 *              either left or right.
 */
void moto_strafeRight(void){
    moto_decreaseRightNormal();
    moto_increaseLeftNormal();
}

void moto_strafeLeft(void){
    moto_decreaseLeftNormal();
    moto_increaseRightNormal();
}

/*
 * Functions:   moto_rotateLeft()
 *              moto_rotateRight()
 *
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Increases either right and
 *              left or front and rear
 *              motor and decreases
 *              the other in order to make
 *              the drone turn either righ or left.             
 */



void moto_rotateLeft(void){
    moto_increaseLeftNormal();
    moto_increaseRightNormal();
    moto_decreaseFrontNormal();
    moto_decreaseRearNormal();
}

void moto_rotateRight(void){
    moto_decreaseLeftNormal();
    moto_decreaseRightNormal();
    moto_increaseFrontNormal();
    moto_increaseRearNormal();
}
/*
 * Functions:   moto_increaseAll()
 *              moto_increaseAllPanic()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Increases the pulse width of
 *              all the motors.
 *              Pulse width increases either
 *              by the predefined normal
 *              increment or by the predefined
 *              panic increment.
 */

void moto_increaseAllNormal(void){
    moto_increaseLeftNormal();
    moto_increaseRightNormal();
    moto_increaseFrontNormal();
    moto_increaseRearNormal();
    PRINT_STRING("increases all motors");
    PRINT_NEW_LINE;
}

void moto_increaseAllPanic(void){
    moto_increaseLeftPanic();
    moto_increaseRightPanic();
    moto_increaseFrontPanic();
    moto_increaseRearPanic();    
    PRINT_STRING("increases all motors");
    PRINT_NEW_LINE;
}
/*
 * Functions:   moto_decreaseAll()
 *              moto_decreaseAllPanic()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Decreases the pulse width of
 *              all the motors.
 *              Pulse width decreases either
 *              by the predefined normal
 *              decrement or by the predefined
 *              panic decrement.
 */

void moto_decreaseAllNormal(void){
    moto_decreaseLeftNormal();
    moto_decreaseRightNormal();
    moto_decreaseFrontNormal();
    moto_decreaseRearNormal();
    PRINT_STRING("decreases all motors\n");
    PRINT_NEW_LINE;
}

void moto_decreaseAllPanic(void){
    moto_decreaseLeftPanic();
    moto_decreaseRightPanic();
    moto_decreaseFrontPanic();
    moto_decreaseRearPanic();
    PRINT_STRING("decreases all motors");
    PRINT_NEW_LINE;
}
/*
 * Functions:   moto_increaseRightNormal()
 *              moto_increaseLeftNormal()
 *              moto_increaseFrontNormal()
 *              moto_increaseRearNormal()
 *              moto_increaseRightPanic()
 *              moto_increaseLeftPanic()
 *              moto_increaseFrontPanic()
 *              moto_increaseRearPanic()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Increases the pulse width of
 *              the corresponding motor.
 *              Pulse width increases either
 *              by the predefined normal
 *              increment or by the predefined
 *              panic increment. Every motor
 *              can have individual max & min
 *              levels due to HW tolerances              
 */
    
void moto_increaseLeftNormal(void){
    leftPulse = moto_LimitIncrease(leftPulse, NORMAL_STEP);
#ifdef ARDUINO
    escLeft.writeMicroseconds(moto_map(
                            leftPulse, MIN_PULSE_LEFT, MAX_PULSE_LEFT));
#elif defined PC
    analogWrite(LEFT_MOTOR, moto_map(
                            leftPulse, MIN_PULSE_LEFT, MAX_PULSE_LEFT));
#endif
    PRINT_STRING("Increasing left motor pulse");
    PRINT_NEW_LINE;
}

void moto_increaseRightNormal(void){
    rightPulse = moto_LimitIncrease(rightPulse, NORMAL_STEP);
#ifdef ARDUINO
    escRight.writeMicroseconds(moto_map(
                            rightPulse, MIN_PULSE_RIGHT, MAX_PULSE_RIGHT));
#elif defined PC
    analogWrite(RIGHT_MOTOR, moto_map(
                            rightPulse, MIN_PULSE_RIGHT, MAX_PULSE_RIGHT));
#endif
    PRINT_STRING("Increasing right motor pulse");
    PRINT_NEW_LINE;
}

void moto_increaseFrontNormal(void){
    frontPulse = moto_LimitIncrease(frontPulse, NORMAL_STEP);
#ifdef ARDUINO
    escFront.writeMicroseconds(moto_map(
                            frontPulse, MIN_PULSE_FRONT, MAX_PULSE_FRONT));
#elif defined PC
    analogWrite(FRONT_MOTOR, moto_map(
                            frontPulse, MIN_PULSE_FRONT, MAX_PULSE_FRONT));
#endif
    PRINT_STRING("Increasing Front motor pulse");
    PRINT_NEW_LINE;
}

void moto_increaseRearNormal(void){
    rearPulse = moto_LimitIncrease(rearPulse, NORMAL_STEP);
#ifdef ARDUINO
    escRear.writeMicroseconds(moto_map(
                            rearPulse, MIN_PULSE_REAR, MAX_PULSE_REAR));
#elif defined PC
    analogWrite(REAR_MOTOR, moto_map(
                            rearPulse, MIN_PULSE_REAR, MAX_PULSE_REAR));
#endif
    PRINT_STRING("Increasing rear motor pulse");
    PRINT_NEW_LINE;
}

void moto_increaseLeftPanic(void){
    leftPulse = moto_LimitIncrease(leftPulse, PANIC_STEP);
#ifdef ARDUINO
    escLeft.writeMicroseconds(moto_map(
                          leftPulse, MIN_PULSE_LEFT, MAX_PULSE_LEFT));
#elif defined PC
    analogWrite(LEFT_MOTOR, moto_map(
                          leftPulse, MIN_PULSE_LEFT, MAX_PULSE_LEFT));
#endif
    PRINT_STRING("Increasing left motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_increaseRightPanic(void){
    rightPulse = moto_LimitIncrease(rightPulse, PANIC_STEP);
#ifdef ARDUINO
    escRight.writeMicroseconds(moto_map(
                            rightPulse, MIN_PULSE_RIGHT, MAX_PULSE_RIGHT));
#elif defined PC
    analogWrite(RIGHT_MOTOR, moto_map(
                            rightPulse, MIN_PULSE_RIGHT, MAX_PULSE_RIGHT));
#endif
    PRINT_STRING("Increasing right motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_increaseFrontPanic(void){
    frontPulse = moto_LimitIncrease(frontPulse, PANIC_STEP);
#ifdef ARDUINO
    escFront.writeMicroseconds(moto_map(
                            frontPulse, MIN_PULSE_FRONT, MAX_PULSE_FRONT));
#elif defined PC
    analogWrite(FRONT_MOTOR, moto_map(
                            frontPulse, MIN_PULSE_FRONT, MAX_PULSE_FRONT));
#endif
    PRINT_STRING("Increasing Front motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_increaseRearPanic(void){
    rearPulse = moto_LimitIncrease(rearPulse, PANIC_STEP);
#ifdef ARDUINO
    escRear.writeMicroseconds(moto_map(
                            rearPulse, MIN_PULSE_REAR, MAX_PULSE_REAR));
#elif defined PC
    analogWrite(REAR_MOTOR, moto_map(
                            rearPulse, MIN_PULSE_REAR, MAX_PULSE_REAR));
#endif
    PRINT_STRING("Increasing rear motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

/*
 * Functions:   moto_decreaseRightNormal()
 *              moto_decreaseLeftNormal()
 *              moto_decreaseFrontNormal()
 *              moto_decreaseRearNormal()
 *              moto_decreaseRightPanic()
 *              moto_decreaseLeftPanic()
 *              moto_decreaseFrontPanic()
 *              moto_decreaseRearPanic()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Decreases the pulse width of
 *              the corresponding motor.
 *
 *              Pulse width decreases either
 *              by the predefined normal
 *              decrement or by the predefined
 *              panic decrement.
 */

void moto_decreaseRightNormal(void){
    rightPulse = moto_LimitDecrease(rightPulse, NORMAL_STEP);
#ifdef ARDUINO
    escRight.writeMicroseconds(moto_map(
                            rightPulse, MIN_PULSE_RIGHT, MAX_PULSE_RIGHT));
#elif defined PC
    analogWrite(RIGHT_MOTOR, moto_map(
                            rightPulse, MIN_PULSE_RIGHT, MAX_PULSE_RIGHT));
#endif
    PRINT_STRING("Decreasing right motor pulse");
    PRINT_NEW_LINE;
}

void moto_decreaseLeftNormal(void){
    leftPulse = moto_LimitDecrease(leftPulse, NORMAL_STEP);
#ifdef ARDUINO
    escLeft.writeMicroseconds(moto_map(
                            leftPulse, MIN_PULSE_LEFT, MAX_PULSE_LEFT));
#elif defined PC
    analogWrite(LEFT_MOTOR, moto_map(
                            leftPulse, MIN_PULSE_LEFT, MAX_PULSE_LEFT));
#endif
    PRINT_STRING("Decreasing left motor pulse");
    PRINT_NEW_LINE;
}

void moto_decreaseFrontNormal(void){
    frontPulse = moto_LimitDecrease(frontPulse, NORMAL_STEP);
#ifdef ARDUINO
    escFront.writeMicroseconds(moto_map(
                            frontPulse, MIN_PULSE_FRONT, MAX_PULSE_FRONT));
#elif defined PC
    analogWrite(FRONT_MOTOR, moto_map(
                            frontPulse, MIN_PULSE_FRONT, MAX_PULSE_FRONT));
#endif
    PRINT_STRING("Decreasing Front motor pulse");
    PRINT_NEW_LINE;
}

void moto_decreaseRearNormal(void){
    rearPulse = moto_LimitDecrease(rearPulse, NORMAL_STEP);
#ifdef ARDUINO
    escRear.writeMicroseconds(moto_map(
                            rearPulse, MIN_PULSE_REAR, MAX_PULSE_REAR));
#elif defined PC
    analogWrite(REAR_MOTOR, moto_map(
                            rearPulse, MIN_PULSE_REAR, MAX_PULSE_REAR));
#endif
    PRINT_STRING("Decreasing rear motor pulse");
    PRINT_NEW_LINE;
}

void moto_decreaseLeftPanic(void){
    leftPulse = moto_LimitDecrease(leftPulse, PANIC_STEP);
#ifdef ARDUINO
    escLeft.writeMicroseconds(moto_map(
                            leftPulse, MIN_PULSE_LEFT, MAX_PULSE_LEFT));
#elif defined PC
    analogWrite(LEFT_MOTOR, moto_map(
                            leftPulse, MIN_PULSE_LEFT, MAX_PULSE_LEFT));
#endif
    PRINT_STRING("Decreasing left motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_decreaseRightPanic(void){
    rightPulse = moto_LimitDecrease(rightPulse, PANIC_STEP);
#ifdef ARDUINO
    escRight.writeMicroseconds(moto_map(
                            rightPulse, MIN_PULSE_RIGHT, MAX_PULSE_RIGHT));
#elif defined PC
    analogWrite(RIGHT_MOTOR, moto_map(
                            rightPulse, MIN_PULSE_RIGHT, MAX_PULSE_RIGHT));
#endif
    PRINT_STRING("Decreasing right motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_decreaseFrontPanic(void){
    frontPulse = moto_LimitDecrease(frontPulse, PANIC_STEP);
#ifdef ARDUINO
    escFront.writeMicroseconds(moto_map(
                            frontPulse, MIN_PULSE_FRONT, MAX_PULSE_FRONT));
#elif defined PC
    analogWrite(FRONT_MOTOR, moto_map(
                            frontPulse, MIN_PULSE_FRONT, MAX_PULSE_FRONT));
#endif
    PRINT_STRING("Decreasing Front motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_decreaseRearPanic(void){
    rearPulse = moto_LimitDecrease(rearPulse, PANIC_STEP);
#ifdef ARDUINO
    escRear.writeMicroseconds(moto_map(
                            rearPulse, MIN_PULSE_REAR, MAX_PULSE_REAR));
#elif defined PC
    analogWrite(REAR_MOTOR, moto_map(
                            rearPulse, MIN_PULSE_REAR, MAX_PULSE_REAR));
#endif
    PRINT_STRING("Decreasing rear motor pulse in PANIC!");
    PRINT_NEW_LINE;
}


/*
 * Function:     printMotorStatus()
 * Author(s):    Kristofer Hansson Aspman,
 *               Magnus Bergqvist
 *
 * Description:  Prints out the status of the
 *               motors to either the terminalmoto_map(
                              leftPulse,MIN_PULSE_LEFT,MAX_PULSE_LEFT))
 *               or the serial monitor depending
 *               on whether the ARDUINO or PC
 *               flags are set.
 */

void printMotorStatus(void){
    PRINT_STRING("****************************");
    PRINT_NEW_LINE;
    PRINT_STRING("Current status of the motors");
    PRINT_NEW_LINE;
    PRINT_STRING("Right:  ");
    PRINT_DEC(rightPulse);
    PRINT_NEW_LINE;
    PRINT_STRING("Left:  ");
    PRINT_DEC(leftPulse);
    PRINT_NEW_LINE;
    PRINT_STRING("Front:  ");
    PRINT_DEC(frontPulse);
    PRINT_NEW_LINE;
    PRINT_STRING("Rear:  ");
    PRINT_DEC(rearPulse);
    PRINT_NEW_LINE;
    PRINT_STRING("****************************");
    PRINT_NEW_LINE;
}

/*
 * Functions:    moto_LimitIncrease()
 *               moto_LimitDecrease()
 * Author(s):    Magnus Bergqvist
 *
 * Description:  Functions contains the logic
 *               that determines and returns
 *               a valid input value to the motors.
 */
 
uint16_t moto_LimitIncrease(uint16_t currentPulse,
                                        uint16_t increment){
    if((currentPulse + increment) < MAX_ESC_PULSE){
        return (currentPulse + increment);
    }
    else{
        return MAX_ESC_PULSE;
    }
}

uint16_t moto_LimitDecrease(uint16_t currentPulse,
                                        uint16_t decrement){
    if((currentPulse - decrement) > MIN_ESC_PULSE){
        return (currentPulse - decrement);
    }
    else{
        return MIN_ESC_PULSE;
    }
}


/*
 * Function:     moto_map()
 * Author(s):    Magnus Bergqvist
 *
 * Description:  The map function takes an input value (actual), and upper
 *               and lower boundary value the wanted output as arguments.
 *               According to these values combined with boundaries for the
 *               systems actual output signals it returns a suitable
 *               value for the calling function to use.
 */
uint16_t moto_map(uint16_t actual, uint16_t out_boundary1, 
                                    uint16_t out_boundary2){    
    /* 
     * step size depending on inner value spectra 
     * compared to ESC output spectra
     */
    double steps = (double)(out_boundary2 - out_boundary1) / 
                    (double)(MAX_ESC_PULSE - MIN_ESC_PULSE);
    
    /*
     * calculating the result and make sure all values start from 
     * out_boundary1
     */
    double result = out_boundary1 + ((actual-MIN_ESC_PULSE)*steps);
    
    /*
     * modfCrap is a var. to take care of int val. after a modf on result,
     * which we don't care about. We just want the decimal part to get
     * the rounding of the numbers more accurate
     */
    
    double modfCrap;
    
    /*
     * modfRest will store the decimals from var. result to be used below
     * to determine if the returned value should be rounded up or down
     */
    double modfRest = modf(result, &modfCrap);
    
    /* 
     * final created to get a return variable that conforms with the
     * coding standard and allows final adjustment to the result before
     * it's returned
     */
    uint16_t final;
    
    /* If fractional part of result < 0.5 do nothing */
    if(modfRest < 0.5){
        final = (uint16_t)result;
    }
    /* else add 1 to get a rounding upwards */
    else{
        final = (uint16_t)result + 1;
    }
    
    if (final >= out_boundary1 && final <= out_boundary2){
        return final;
    }
    else if(final < out_boundary1){
        return out_boundary1;
    }
    else{
        return out_boundary2;
    }
}
