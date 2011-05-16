 /*!@author Kristofer Hansson Aspman,
 *          Björn Eriksson,
 *          Magnus Bergqvist
 *         
 * @file moto_driver_functions.c
 * @version v0.03
 * @date 2011-05-09
 *
 * @brief Contains the functions that sets the pulse width of the \n
 *        different motors.
 *
 * @history 2011-04-03: Created the file. (Kristofer)
 *          2011-05-09: Added map function and moved printout macros \n
 *                      to moto_printer_functions, changed the printouts \n
 *                      to fully comply with the new macro style (Magnus)
 */
 
#include "moto_driver_functions.h"
#include <stdint.h>
#include <math.h>
#include "moto_interface.h"
#include "moto_printer_functions.h"

#ifdef ARDUINO_DBG
	#define ARDUINO
#endif

#ifdef ARDUINO
    #include "WProgram.h"
    #include "../include/Servo.h"
#elif defined PC
    #include <stdio.h>
    #include"moto_stubs.h"
#endif

/* These are the variables keeping track of the  */
/* current state (pulse width) of each motor. */
uint16_t rightPulse;
uint16_t leftPulse;
uint16_t frontPulse;
uint16_t rearPulse;


/*
*	Function:		moto_left_mototr(unsigned char increase,unsigned char panic)
*	Author(s):		Reza Moussavi, Rahwa Bahta
*	Description:	To incease/decrease panic/normal the left motor
*/
void moto_left_motor(unsigned char increase,unsigned char panic){
	leftPulse = increase?leftMotorLimitIncrease(leftPulse, panic?PANIC_STEP:NORMAL_STEP):leftMotorLimitDecrease(leftPulse, panic?PANIC_STEP:NORMAL_STEP);
	#ifdef ARDUINO
		escLeft.writeMicroseconds(leftPulse);
	#elif defined PC
		analogWrite(LEFT_MOTOR, leftPulse);
	#endif
		PRINT_STRING("Increasing left motor pulse");
		PRINT_NEW_LINE;
}

/*
*	Function:		moto_right_mototr(unsigned char increase,unsigned char panic)
*	Author(s):		Reza Moussavi, Rahwa Bahta
*	Description:	To incease/decrease panic/normal the right motor
*/
void moto_right_motor(unsigned char increase,unsigned char panic){
	rightPulse = increase?rightMotorLimitIncrease(rightPulse, panic?PANIC_STEP:NORMAL_STEP):rightMotorLimitDecrease(rightPulse, panic?PANIC_STEP:NORMAL_STEP);
	#ifdef ARDUINO
		escRight.writeMicroseconds(rightPulse);
	#elif defined PC
		analogWrite(RIGHT_MOTOR, rightPulse);
	#endif
		PRINT_STRING("Increasing right motor pulse");
		PRINT_NEW_LINE;
}

/*
*	Function:		moto_front_mototr(unsigned char increase,unsigned char panic)
*	Author(s):		Reza Moussavi, Rahwa Bahta
*	Description:	To incease/decrease panic/normal the front motor
*/
void moto_front_motor(unsigned char increase,unsigned char panic){
	frontPulse = increase?frontMotorLimitIncrease(frontPulse, panic?PANIC_STEP:NORMAL_STEP):frontMotorLimitDecrease(frontPulse, panic?PANIC_STEP:NORMAL_STEP);
	#ifdef ARDUINO
		escFront.writeMicroseconds(frontPulse);
	#elif defined PC
		analogWrite(FRONT_MOTOR, frontPulse);
	#endif
		PRINT_STRING("Increasing front motor pulse");
		PRINT_NEW_LINE;
}

/*
*	Function:		moto_rear_mototr(unsigned char increase,unsigned char panic)
*	Author(s):		Reza Moussavi, Rahwa Bahta
*	Description:	To incease/decrease panic/normal the rear motor
*/
void moto_rear_motor(unsigned char increase,unsigned char panic){
	rearPulse = increase?rearMotorLimitIncrease(rearPulse, panic?PANIC_STEP:NORMAL_STEP):rearMotorLimitDecrease(rearPulse, panic?PANIC_STEP:NORMAL_STEP);
	#ifdef ARDUINO
		escRear.writeMicroseconds(rearPulse);
	#elif defined PC
		analogWrite(REAR_MOTOR, rearPulse);
	#endif
		PRINT_STRING("Increasing rear motor pulse");
		PRINT_NEW_LINE;
}



/**
 * Function:    void moto_startMotors()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Sets the pulse width to a state where
 *              all motors starts spinning but the
 *              drone does not lift off.
 *
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

/**
 * Function:    void moto_stopMotors()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Stops all motors, i.e. sets the
 *              pulse width to zero.
 *
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
/**
 * Function:    void moto_hover()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *              Magnus Bergqvist
 *
 * Description: Sets all motors to the same pulse width
 *              where to drone shall stay in hover state
 *
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




/**
 * Function:    void moto_goForward()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Increases the pulse width of
 *              of the rear motor and decreases
 *              the pulse width of the front
 *              motor. This makes the drone go
 *              forward.
 *
 */
void moto_goForward(void){
    moto_increaseRearNormal();
    moto_decreaseFrontNormal();
    return;

}

/**
 * Function:    void moto_goBackward()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Decreases the pulse width of
 *              of the rear motor and increases
 *              the pulse width of the front
 *              motor. This makes the drone go
 *              backward.
 *
 */
void moto_goBackward(void){
    moto_decreaseRearNormal();
    moto_increaseFrontNormal();
    return;
}

/**
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
 *              
 */
void moto_strafeRight(void){
    moto_decreaseRightNormal();
    moto_increaseLeftNormal();
    return;
}

void moto_strafeLeft(void){
    moto_decreaseLeftNormal();
    moto_increaseRightNormal();
    return;
}

/**
 * Functions:   moto_rotateLeft()
 *              moto_rotateRight()
 *
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Increases either right and
 *              left or front and rear
*               motor and decreases
 *              the other in order to make
 *              the drone turn either righ or left.
 *              
 */

void moto_rotateLeft(void){
    moto_increaseLeftNormal();
    moto_increaseRightNormal();
    moto_decreaseFrontNormal();
    moto_decreaseRearNormal();
    return;
}

void moto_rotateRight(void){
    moto_decreaseLeftNormal();
    moto_decreaseRightNormal();
    moto_increaseFrontNormal();
    moto_increaseRearNormal();
    return;
}
/**
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
 *
 */

void moto_increaseAllNormal(void){
    rightPulse = rightMotorLimitIncrease(rightPulse, NORMAL_STEP);
    leftPulse = leftMotorLimitIncrease(leftPulse, NORMAL_STEP);
    frontPulse = frontMotorLimitIncrease(frontPulse, NORMAL_STEP);
    rearPulse = rearMotorLimitIncrease(rearPulse, NORMAL_STEP);
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
    PRINT_STRING("increases all motors");
    PRINT_NEW_LINE;
}

void moto_increaseAllPanic(void){
    rightPulse = rightMotorLimitIncrease(rightPulse, PANIC_STEP);
    leftPulse = leftMotorLimitIncrease(leftPulse, PANIC_STEP);
    frontPulse = frontMotorLimitIncrease(frontPulse, PANIC_STEP);
    rearPulse = rearMotorLimitIncrease(rearPulse, PANIC_STEP);
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
    PRINT_STRING("increases all motors");
    PRINT_NEW_LINE;
}
/**
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
 *
 */

void moto_decreaseAllNormal(void){
    rightPulse = rightMotorLimitDecrease(rightPulse, NORMAL_STEP);
    leftPulse = leftMotorLimitDecrease(leftPulse, NORMAL_STEP);
    frontPulse = frontMotorLimitDecrease(frontPulse, NORMAL_STEP);
    rearPulse = rearMotorLimitDecrease(rearPulse, NORMAL_STEP);
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
    PRINT_STRING("decreases all motors\n");
    PRINT_NEW_LINE;
}

void moto_decreaseAllPanic(void){
    rightPulse = rightMotorLimitDecrease(rightPulse, PANIC_STEP);
    leftPulse = leftMotorLimitDecrease(leftPulse, PANIC_STEP);
    frontPulse = frontMotorLimitDecrease(frontPulse, PANIC_STEP);
    rearPulse = rearMotorLimitDecrease(rearPulse, PANIC_STEP);
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
    PRINT_STRING("decreases all motors");
    PRINT_NEW_LINE;
}
/**
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
 *              
 */
    
void moto_increaseLeftNormal(void){
    leftPulse = leftMotorLimitIncrease(leftPulse, NORMAL_STEP);
#ifdef ARDUINO
    escLeft.writeMicroseconds(leftPulse);
#elif defined PC
    analogWrite(LEFT_MOTOR, leftPulse);
#endif
    PRINT_STRING("Increasing left motor pulse");
    PRINT_NEW_LINE;
}

void moto_increaseRightNormal(void){
    rightPulse = rightMotorLimitIncrease(rightPulse, NORMAL_STEP);
#ifdef ARDUINO
    escRight.writeMicroseconds(rightPulse);
#elif defined PC
    analogWrite(RIGHT_MOTOR, rightPulse);
#endif
    PRINT_STRING("Increasing right motor pulse");
    PRINT_NEW_LINE;
}

void moto_increaseFrontNormal(void){
    frontPulse = frontMotorLimitIncrease(frontPulse, NORMAL_STEP);
#ifdef ARDUINO
    escFront.writeMicroseconds(frontPulse);
#elif defined PC
    analogWrite(FRONT_MOTOR, frontPulse);
#endif
    PRINT_STRING("Increasing Front motor pulse");
    PRINT_NEW_LINE;
}

void moto_increaseRearNormal(void){
    rearPulse = rearMotorLimitIncrease(rearPulse, NORMAL_STEP);
#ifdef ARDUINO
    escRear.writeMicroseconds(rearPulse);
#elif defined PC
    analogWrite(REAR_MOTOR, rearPulse);
#endif
    PRINT_STRING("Increasing rear motor pulse");
    PRINT_NEW_LINE;
}

void moto_increaseLeftPanic(void){
    leftPulse = leftMotorLimitIncrease(leftPulse, PANIC_STEP);
#ifdef ARDUINO
    escLeft.writeMicroseconds(leftPulse);
#elif defined PC
    analogWrite(LEFT_MOTOR, leftPulse);
#endif
    PRINT_STRING("Increasing left motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_increaseRightPanic(void){
    rightPulse = rightMotorLimitIncrease(rightPulse, PANIC_STEP);
#ifdef ARDUINO
    escRight.writeMicroseconds(rightPulse);
#elif defined PC
    analogWrite(RIGHT_MOTOR, rightPulse);
#endif
    PRINT_STRING("Increasing right motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_increaseFrontPanic(void){
    frontPulse = frontMotorLimitIncrease(frontPulse, PANIC_STEP);
#ifdef ARDUINO
    escFront.writeMicroseconds(frontPulse);
#elif defined PC
    analogWrite(FRONT_MOTOR, frontPulse);
#endif
    PRINT_STRING("Increasing Front motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_increaseRearPanic(void){
    rearPulse = rearMotorLimitIncrease(rearPulse, PANIC_STEP);
#ifdef ARDUINO
    escRear.writeMicroseconds(rearPulse);
#elif defined PC
    analogWrite(REAR_MOTOR, rearPulse);
#endif
    PRINT_STRING("Increasing rear motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

/**
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
 *              Pulse width decreases either
 *              by the predefined normal
 *              decrement or by the predefined
 *              panic decrement.
 *
 */

void moto_decreaseRightNormal(void){
    rightPulse = rightMotorLimitDecrease(rightPulse, NORMAL_STEP);
#ifdef ARDUINO
    escRight.writeMicroseconds(rightPulse);
#elif defined PC
    analogWrite(RIGHT_MOTOR, rightPulse);
#endif
    PRINT_STRING("Decreasing right motor pulse");
    PRINT_NEW_LINE;
}

void moto_decreaseLeftNormal(void){
    leftPulse = leftMotorLimitDecrease(leftPulse, NORMAL_STEP);
#ifdef ARDUINO
    escLeft.writeMicroseconds(leftPulse);
#elif defined PC
    analogWrite(LEFT_MOTOR, leftPulse);
#endif
    PRINT_STRING("Decreasing left motor pulse");
    PRINT_NEW_LINE;
}

void moto_decreaseFrontNormal(void){
    frontPulse = frontMotorLimitDecrease(frontPulse, NORMAL_STEP);
#ifdef ARDUINO
    escFront.writeMicroseconds(frontPulse);
#elif defined PC
    analogWrite(FRONT_MOTOR, frontPulse);
#endif
    PRINT_STRING("Decreasing Front motor pulse");
    PRINT_NEW_LINE;
}

void moto_decreaseRearNormal(void){
    rearPulse = rearMotorLimitDecrease(rearPulse, NORMAL_STEP);
#ifdef ARDUINO
    escRear.writeMicroseconds(rearPulse);
#elif defined PC
    analogWrite(REAR_MOTOR, rearPulse);
#endif
    PRINT_STRING("Decreasing rear motor pulse");
    PRINT_NEW_LINE;
}

void moto_decreaseLeftPanic(void){
    leftPulse = leftMotorLimitDecrease(leftPulse, PANIC_STEP);
#ifdef ARDUINO
    escLeft.writeMicroseconds(leftPulse);
#elif defined PC
    analogWrite(LEFT_MOTOR, leftPulse);
#endif
    PRINT_STRING("Decreasing left motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_decreaseRightPanic(void){
    rightPulse = rightMotorLimitDecrease(rightPulse, PANIC_STEP);
#ifdef ARDUINO
    escRight.writeMicroseconds(rightPulse);
#elif defined PC
    analogWrite(RIGHT_MOTOR, rightPulse);
#endif
    PRINT_STRING("Decreasing right motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_decreaseFrontPanic(void){
    frontPulse = frontMotorLimitDecrease(frontPulse, PANIC_STEP);
#ifdef ARDUINO
    escFront.writeMicroseconds(frontPulse);
#elif defined PC
    analogWrite(FRONT_MOTOR, frontPulse);
#endif
    PRINT_STRING("Decreasing Front motor pulse in PANIC!");
    PRINT_NEW_LINE;
}

void moto_decreaseRearPanic(void){
    rearPulse = rearMotorLimitDecrease(rearPulse, PANIC_STEP);
#ifdef ARDUINO
    escRear.writeMicroseconds(rearPulse);
#elif defined PC
    analogWrite(REAR_MOTOR, rearPulse);
#endif
    PRINT_STRING("Decreasing rear motor pulse in PANIC!");
    PRINT_NEW_LINE;
}


/**
 * Function:     printMotorStatus()
 * Author(s):    Kristofer Hansson Aspman,
 *               Magnus Bergqvist
 *
 * Description:  Prints out the status of the
 *               motors to either the terminal
 *               or the serial monitor depending
 *               on whether the ARDUINO or PC
 *               flags are set.
 *
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

void sendMsg(void){
    struct pulses currentPulse = 
    {rightPulse, leftPulse, frontPulse, rearPulse};
    /* send(currentPulse);  not sure how the send funcrion till look like */
}

/**
 * Functions:    rightMotorLimitIncrease()
 *               rightMotorLimitDecrease()
 *               leftMotorLimitIncrease()
 *               leftMotorLimitDecrease()
 *               frontMotorLimitIncrease()
 *               frontMotorLimitDecrease()
 *               rearMotorLimitIncrease()
 *               rearMotorLimitDecrease()
 * Author(s):    Magnus Bergqvist
 *
 * Description:  Functions contains the logic
 *               that determines and returns
 *               a valid input value to the motors.
 *               Returned values are mapped for
 *               the functions corresponding motor.
 */
 
uint16_t rightMotorLimitIncrease(uint16_t currentPulse,
                                        uint16_t increment){
    if((currentPulse + increment) < MAX_PULSE_RIGHT){
        return (currentPulse + increment);
    }
    else{
        return MAX_PULSE_RIGHT;
    }
}

uint16_t rightMotorLimitDecrease(uint16_t currentPulse,
                                        uint16_t decrement){
    if((currentPulse - decrement) > MIN_PULSE_RIGHT){
        return (currentPulse - decrement);
    }
    else{
        return MIN_PULSE_RIGHT;
    }
}

uint16_t leftMotorLimitIncrease(uint16_t currentPulse,
                                        uint16_t increment){
    if((currentPulse + increment) < MAX_PULSE_LEFT){
        return (currentPulse + increment);
    }
    else{
        return MAX_PULSE_LEFT;
    }
}

uint16_t leftMotorLimitDecrease(uint16_t currentPulse,
                                        uint16_t decrement){
    if((currentPulse - decrement) > MIN_PULSE_LEFT){
        return (currentPulse - decrement);
    }
    else{
        return MIN_PULSE_LEFT;
    }
}

uint16_t frontMotorLimitIncrease(uint16_t currentPulse,
                                        uint16_t increment){
    if((currentPulse + increment) < MAX_PULSE_FRONT){
        return (currentPulse + increment);
    }
    else{
        return MAX_PULSE_FRONT;
    }
}

uint16_t frontMotorLimitDecrease(uint16_t currentPulse,
                                        uint16_t decrement){
    if((currentPulse - decrement) > MIN_PULSE_FRONT){
        return (currentPulse - decrement);
    }
    else{
        return MIN_PULSE_FRONT;
    }
}

uint16_t rearMotorLimitIncrease(uint16_t currentPulse,
                                        uint16_t increment){
    if((currentPulse + increment) < MAX_PULSE_REAR){
        return (currentPulse + increment);
    }
    else{
        return MAX_PULSE_REAR;
    }
}

uint16_t rearMotorLimitDecrease(uint16_t currentPulse,
                                        uint16_t decrement){
    if((currentPulse - decrement) > MIN_PULSE_REAR){
        return (currentPulse - decrement);
    }
    else{
        return MIN_PULSE_REAR;
    }
}

/**
 * Function:     map()
 * Author(s):    Magnus Bergqvist
 *
 * Description:  The map function takes an input value (actual), and upper
 *               and lower boundary value the wanted output as arguments.
 *               According to these values combined with boundaries for the
 *               systems actual output signals it returns a suitable
 *               value for the calling function to use.
 */
uint16_t map(uint16_t actual, uint16_t out_boundary1, uint16_t out_boundary2){
    
    /*step size depending on inner value spectra 
    compared to ESC output spectra*/
    double steps = (double)(out_boundary2 - out_boundary1) / 
                    (double)(MAX_ESC_PULSE - MIN_ESC_PULSE);
    
    /* calculating the result and make sure all values start from 
        out_boundary1*/
    double result = out_boundary1 + ((actual-MIN_ESC_PULSE)*steps);
    
    /* modfCrap is a var. to take care of int val. after a modf on result,
       which we don't care about. We just want the decimal part to get
       the rounding of the numbers more accurate*/
    double modfCrap;
    
    /* modfRest will store the decimals from var. result to be used below
       to determine if the returned value should be rounded up or down*/
    double modfRest = modf(result, &modfCrap);
    
    /* final created to get a return variable that conforms with the
       coding standard and allows final adjustment to the result before
       it's returned*/
    uint16_t final;
    
    /* If fractional part of result < 0.5 do nothing*/
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
    else if(final > out_boundary2){
        return out_boundary2;
    }
}
