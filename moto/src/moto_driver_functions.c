<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
/** 
 * Module:       motor_controls.c
 * Author(s):    Kristofer Hansson Aspman,
 *               Björn Eriksson
 *
 * Description:  Contains the functions that
 *               sets the pulse width of the
 *               different motors.
 *
 */
 
 #ifdef ARDUINO_DBG
	#define ARDUNO
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#endif

#ifdef ARDUINO
    #include "WProgram.h"
<<<<<<< HEAD
<<<<<<< HEAD
    #include "../include/Servo.h"
#elif defined PC
    #include <stdio.h>
    #include"moto_stubs.h"
#endif

=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#elif defined PC
    #include <stdio.h>
#endif

#include "moto_driver_functions.h"
#include <stdint.h>

<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
/* These are the variables keeping track of the  */
/* current state (pulse width) of each motor. */
uint16_t rightPulse;
uint16_t leftPulse;
uint16_t frontPulse;
uint16_t rearPulse;

<<<<<<< HEAD
<<<<<<< HEAD

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



=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
/**
 * Function:    void moto_startMotors()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
<<<<<<< HEAD
<<<<<<< HEAD
 *              Magnus Bergqvist
=======
/**
 * Module:       motor_controls.c
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description:  Contains the functions that
 *               sets the pulse width of the
 *               different motors.
 *
 */

#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

#include "moto_driver_functions.h"

/* These are the variables keeping track of the  */
/* current state (pulse width) of each motor. */
unsigned char rightMotor;
unsigned char leftMotor;
unsigned char frontMotor;
unsigned char rearMotor;

/**
 * Function:    void _moto_startMotors()
 * Author(s):    Kristofer Hansson Aspman
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *
 * Description: Sets the pulse width to a state where
 *              all motors starts spinning but the
 *              drone does not lift off.
 *
 */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
void moto_startMotors(void){
    leftPulse = 40;
    rightPulse = 40;
    frontPulse = 40;
    rearPulse = 40;
#ifdef ARDUINO_DBG
    Serial.print("Starting all motors\n");
#elif defined PC
    printf("Starting all motors\n");
#endif 

#ifdef ARDUINO
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#endif
<<<<<<< HEAD
<<<<<<< HEAD
    PRINT_STRING("Starting all motors");
    PRINT_NEW_LINE;
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}

/**
 * Function:    void moto_stopMotors()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
<<<<<<< HEAD
<<<<<<< HEAD
 *              Magnus Bergqvist
=======
void _moto_startMotors(void){
#ifdef ARDUINO
  Serial.print("Starting all motors\n");
#elif defined PC
  printf("Starting all motors\n");
#endif
  rightMotor += NORMAL_INCREMENT;
  leftMotor += NORMAL_INCREMENT;
  frontMotor += NORMAL_INCREMENT;
  rearMotor += NORMAL_INCREMENT;    
}

/**
 * Function:    void _moto_stopMotors()
 * Author(s):    Kristofer Hansson Aspman
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *
 * Description: Stops all motors, i.e. sets the
 *              pulse width to zero.
 *
 */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
void moto_stopMotors(void){
    rightPulse = 0;
    leftPulse = 0;
    frontPulse = 0;
    rearPulse = 0;
#ifdef ARDUINO_BDG
    Serial.print("Stopping all motors\n");
#elif defined PC
    printf("Stopping all motors\n");
#endif

#ifdef ARDUINO
analogWrite(RIGHT_MOTOR, rightPulse);
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#endif
<<<<<<< HEAD
<<<<<<< HEAD
    PRINT_STRING("Stopping all motors");
    PRINT_NEW_LINE;
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}
/**
 * Function:    void moto_hover()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
<<<<<<< HEAD
<<<<<<< HEAD
 *              Magnus Bergqvist
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *
 * Description: Sets all motors to the same pulse width
 *              where to drone shall stay in hover state
 *
 */
void moto_hover(void){
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    rightPulse =90;
    leftPulse = 90;
    frontPulse = 90;
    rearPulse = 90;

#ifdef ARDUINO
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
<<<<<<< HEAD
<<<<<<< HEAD
#endif
    PRINT_STRING("Hovering");
    PRINT_NEW_LINE;    
=======
#elif defined PC
    printf("Hovering\n");
#endif    
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
#elif defined PC
    printf("Hovering\n");
#endif    
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}




/**
 * Function:    void moto_goForward()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
<<<<<<< HEAD
<<<<<<< HEAD
=======
void _moto_stopMotors(void){
#ifdef ARDUINO
  Serial.print("Stopping all motors\n");
#elif defined PC
  printf("Stopping all motors\n");
#endif
  rightMotor = 0;
  leftMotor = 0;
  frontMotor = 0;
  rearMotor = 0;
    
}

/**
 * Function:    void _moto_goForward()
 * Author(s):    Kristofer Hansson Aspman
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *
 * Description: Increases the pulse width of
 *              of the rear motor and decreases
 *              the pulse width of the front
 *              motor. This makes the drone go
 *              forward.
 *
 */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
void moto_goForward(void){
    moto_increaseRearNormal();
    moto_decreaseFrontNormal();
    return;
<<<<<<< HEAD
<<<<<<< HEAD
=======
void _moto_goForward(void){
  _moto_increaseRearNormal();
  _moto_decreaseFrontNormal();
  return;
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

}

/**
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
 * Function:    void moto_goBackward()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
=======
 * Function:    void _moto_goBackward()
 * Author(s):   Kristofer Hansson Aspman
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
 * Function:    void moto_goBackward()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
 * Function:    void moto_goBackward()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *
 * Description: Decreases the pulse width of
 *              of the rear motor and increases
 *              the pulse width of the front
 *              motor. This makes the drone go
 *              backward.
 *
 */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
void _moto_goBackward(void){
  _moto_decreaseRearNormal();
  _moto_increaseFrontNormal();
  return;

}

/**
 * Functions:   _moto_strafeRight()
 *              _moto_strafeLeft()
 *
 * Author(s):   Kristofer Hansson Aspman
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *
 * Description: Increases either right or
 *              left motor and decreases
 *              the other in order to make
 *              the drone fly sideways to
 *              either left or right.
 *              
 */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
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
<<<<<<< HEAD
<<<<<<< HEAD
 *              Magnus Bergqvist
 *
 * Description: Increases the pulse width of
 *              all the motors.
=======
void _moto_strafeRight(void){
  _moto_decreaseRightNormal();
  _moto_increaseLeftNormal();
  return;

}
void _moto_strafeLeft(void){
  _moto_decreaseLeftNormal();
  _moto_increaseRightNormal();
  return;

}

/**
 * Functions:   _moto_increaseRightNormal()
 *              _moto_increaseLeftNormal()
 *              _moto_increaseFrontNormal()
 *              _moto_increaseRearNormal()
 *              _moto_increaseRightPanic()
 *              _moto_increaseLeftPanic()
 *              _moto_increaseFrontPanic()
 *              _moto_increaseRearPanic()
 * Author(s):   Kristofer Hansson Aspman
 *
 * Description: Increases the pulse width of
 *              the corresponding motor.
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
 *
 * Description: Increases the pulse width of
 *              all the motors.
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
 *
 * Description: Increases the pulse width of
 *              all the motors.
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *              Pulse width increases either
 *              by the predefined normal
 *              increment or by the predefined
 *              panic increment.
 *
 */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

void moto_increaseAllNormal(void){
    rightPulse += NORMAL_INCREMENT;
    leftPulse += NORMAL_INCREMENT;
    frontPulse += NORMAL_INCREMENT;
    rearPulse += NORMAL_INCREMENT;

#ifdef ARDUINO
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#elif defined PC
    printf("increases all motors\n");
#endif
}

void moto_increaseAllPanic(void){
    rightPulse += PANIC_INCREMENT;
    leftPulse += PANIC_INCREMENT;
    frontPulse += PANIC_INCREMENT;
    rearPulse += PANIC_INCREMENT;

#ifdef ARDUINO
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
<<<<<<< HEAD
<<<<<<< HEAD
#endif
    PRINT_STRING("increases all motors");
    PRINT_NEW_LINE;
=======
#elif defined PC
    printf("increases all motors\n");
#endif
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
#elif defined PC
    printf("increases all motors\n");
#endif
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}
/**
 * Functions:   moto_decreaseAll()
 *              moto_decreaseAllPanic()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
<<<<<<< HEAD
<<<<<<< HEAD
 *              Magnus Bergqvist
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
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
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    rightPulse += NORMAL_DECREMENT;
    leftPulse += NORMAL_DECREMENT;
    frontPulse += NORMAL_DECREMENT;
    rearPulse += NORMAL_DECREMENT;

#ifdef ARDUINO
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#elif defined PC
    printf("increases all motors\n");
#endif
}

void moto_decreaseAllPanic(void){
    rightPulse += PANIC_DECREMENT;
    leftPulse += PANIC_DECREMENT;
    frontPulse += PANIC_DECREMENT;
    rearPulse += PANIC_DECREMENT;

#ifdef ARDUINO
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
<<<<<<< HEAD
<<<<<<< HEAD
#endif
    PRINT_STRING("decreases all motors");
    PRINT_NEW_LINE;
=======
#elif defined PC
    printf("increases all motors\n");
#endif
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
#elif defined PC
    printf("increases all motors\n");
#endif
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
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
<<<<<<< HEAD
<<<<<<< HEAD
 *              Magnus Bergqvist
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *
 * Description: Increases the pulse width of
 *              the corresponding motor.
 *              Pulse width increases either
 *              by the predefined normal
 *              increment or by the predefined
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *              panic increment.
 *
 */
    
void moto_increaseLeftNormal(void){
    leftPulse += NORMAL_INCREMENT;

#ifdef ARDUINO 
    analogWrite(LEFT_MOTOR, leftPulse);
#elif defined PC
    printf("Increasing left motor pulse\n");
#endif

}

void moto_increaseRightNormal(void){
    rightPulse += NORMAL_INCREMENT;
#ifdef ARDUINO 
    analogWrite(RIGHT_MOTOR, rightPulse);
#elif defined PC
    printf("Increasing right motor pulse\n");
#endif
}

void moto_increaseFrontNormal(void){
    frontPulse += NORMAL_INCREMENT;
#ifdef ARDUINO
    analogWrite(FRONT_MOTOR, frontPulse); 
#elif defined PC
    printf("Increasing Front motor pulse\n");
#endif
}

void moto_increaseRearNormal(void){
    rearPulse += NORMAL_INCREMENT;
#ifdef ARDUINO 
    analogWrite(REAR_MOTOR, rearPulse);
#elif defined PC
    printf("Increasing rear motor pulse\n");
#endif
}

void moto_increaseLeftPanic(void){
    leftPulse += PANIC_INCREMENT;
#ifdef ARDUINO     
    analogWrite(LEFT_MOTOR, leftPulse);
#elif defined PC
    printf("Increasing left motor pulse in PANIC!\n");
#endif

}

void moto_increaseRightPanic(void){
    rightPulse += PANIC_INCREMENT;
#ifdef ARDUINO 
    analogWrite(RIGHT_MOTOR, rightPulse);
#elif defined PC
    printf("Increasing right motor pulse in PANIC!\n");
#endif
}

void moto_increaseFrontPanic(void){
    frontPulse += PANIC_INCREMENT;
#ifdef ARDUINO 
    analogWrite(FRONT_MOTOR, frontPulse);
#elif defined PC
    printf("Increasing Front motor pulse in PANIC!\n");
#endif
}

void moto_increaseRearPanic(void){
    rearPulse += PANIC_INCREMENT;
#ifdef ARDUINO 
    analogWrite(REAR_MOTOR, rearPulse);
#elif defined PC
    printf("Increasing rear motor pulse in PANIC!\n");
#endif
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
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
<<<<<<< HEAD
<<<<<<< HEAD
 *              Magnus Bergqvist
=======
void _moto_increaseLeftNormal(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Increasing left motor pulse\n");
  leftMotor += NORMAL_INCREMENT;
#endif

}

void _moto_increaseRightNormal(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Increasing right motor pulse\n");
  rightMotor += NORMAL_INCREMENT;
#endif
}

void _moto_increaseFrontNormal(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Increasing Front motor pulse\n");
  frontMotor += NORMAL_INCREMENT;
#endif
}

void _moto_increaseRearNormal(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Increasing rear motor pulse\n");
  rearMotor += NORMAL_INCREMENT;
#endif
}

void _moto_increaseLeftPanic(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Increasing left motor pulse in PANIC!\n");
  leftMotor += PANIC_INCREMENT;
#endif

}

void _moto_increaseRightPanic(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Increasing right motor pulse in PANIC!\n");
  rightMotor += PANIC_INCREMENT;
#endif
}

void _moto_increaseFrontPanic(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Increasing Front motor pulse in PANIC!\n");
  frontMotor += PANIC_INCREMENT;
#endif
}

void _moto_increaseRearPanic(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Increasing rear motor pulse in PANIC!\n");
  rearMotor += PANIC_INCREMENT;
#endif
}

/**
 * Functions:   _moto_decreaseRightNormal()
 *              _moto_decreaseLeftNormal()
 *              _moto_decreaseFrontNormal()
 *              _moto_decreaseRearNormal()
 *              _moto_decreaseRightPanic()
 *              _moto_decreaseLeftPanic()
 *              _moto_decreaseFrontPanic()
 *              _moto_decreaseRearPanic()
 * Author(s):   Kristofer Hansson Aspman
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *
 * Description: Decreases the pulse width of
 *              the corresponding motor.
 *              Pulse width decreases either
 *              by the predefined normal
 *              decrement or by the predefined
 *              panic decrement.
 *
 */

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
void _moto_decreaseRightNormal(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Decreasing right motor pulse\n");
  rightMotor += NORMAL_DECREMENT;
#endif
}

void _moto_decreaseLeftNormal(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Decreasing left motor pulse\n");
  leftMotor += NORMAL_DECREMENT;
#endif
}

void _moto_decreaseFrontNormal(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Decreasing Front motor pulse\n");
  frontMotor += NORMAL_DECREMENT;
#endif
}

void _moto_decreaseRearNormal(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Decreasing rear motor pulse\n");
  rearMotor += NORMAL_DECREMENT;
#endif
}

void _moto_decreaseLeftPanic(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Decreasing left motor pulse in PANIC!\n");
  leftMotor += PANIC_DECREMENT;
#endif
}

void _moto_decreaseRightPanic(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Decreasing right motor pulse in PANIC!\n");
  rightMotor += PANIC_DECREMENT;
#endif
}

void _moto_decreaseFrontPanic(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Decreasing Front motor pulse in PANIC!\n");
  frontMotor += PANIC_DECREMENT;
#endif
}

void _moto_decreaseRearPanic(void){
#ifdef ARDUINO 
#elif defined PC
  printf("Decreasing rear motor pulse in PANIC!\n");
  rearMotor += PANIC_DECREMENT;
#endif
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
void moto_decreaseRightNormal(void){
    rightPulse += NORMAL_DECREMENT;
#ifdef ARDUINO 
    analogWrite(RIGHT_MOTOR, rightPulse);
#elif defined PC
    printf("Decreasing right motor pulse\n");
#endif
}

void moto_decreaseLeftNormal(void){
    leftPulse += NORMAL_DECREMENT;
#ifdef ARDUINO     
    analogWrite(LEFT_MOTOR, leftPulse);
#elif defined PC
    printf("Decreasing left motor pulse\n");
#endif
}

void moto_decreaseFrontNormal(void){
    frontPulse += NORMAL_DECREMENT;
#ifdef ARDUINO 
    analogWrite(FRONT_MOTOR, frontPulse);
#elif defined PC
    printf("Decreasing Front motor pulse\n");
#endif
}

void moto_decreaseRearNormal(void){
    rearPulse += NORMAL_DECREMENT;
#ifdef ARDUINO 
    analogWrite(REAR_MOTOR, rearPulse);
#elif defined PC
    printf("Decreasing rear motor pulse\n");
#endif
}

void moto_decreaseLeftPanic(void){
    leftPulse += PANIC_DECREMENT;
#ifdef ARDUINO 
    analogWrite(LEFT_MOTOR, leftPulse);
#elif defined PC
    printf("Decreasing left motor pulse in PANIC!\n");
#endif
}

void moto_decreaseRightPanic(void){
    rightPulse += PANIC_DECREMENT;
#ifdef ARDUINO 
    analogWrite(RIGHT_MOTOR, rightPulse);
#elif defined PC
    printf("Decreasing right motor pulse in PANIC!\n");
#endif
}

void moto_decreaseFrontPanic(void){
    frontPulse += PANIC_DECREMENT;
#ifdef ARDUINO 
    analogWrite(FRONT_MOTOR, frontPulse);
#elif defined PC
    printf("Decreasing Front motor pulse in PANIC!\n");
#endif
}

void moto_decreaseRearPanic(void){
    rearPulse += PANIC_DECREMENT;
#ifdef ARDUINO 
    analogWrite(REAR_MOTOR, rearPulse);
#elif defined PC
    printf("Decreasing rear motor pulse in PANIC!\n");
#endif
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}


/**
 * Function:     printMotorStatus()
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
 * Author(s):    Kristofer Hansson Aspman,
 *               Magnus Bergqvist
=======
 * Author(s):    Kristofer Hansson Aspman
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
 * Author(s):    Kristofer Hansson Aspman
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
 * Author(s):    Kristofer Hansson Aspman
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 *
 * Description:  Prints out the status of the
 *               motors to either the terminal
 *               or the serial monitor depending
 *               on whether the ARDUINO or PC
 *               flags are set.
 *
 */

void printMotorStatus(void){
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#ifdef ARDUINO_DBG
    /* Arduino code begin*/
    Serial.println("****************************");
    Serial.println("Current status of the motors");
    Serial.print("Right:  ");
    Serial.println(rightPulse, DEC);
    Serial.print("Left:  ");
    Serial.println(leftPulse, DEC);
    Serial.print("Front:  ");
    Serial.println(frontPulse, DEC);
    Serial.print("Rear:  ");
    Serial.println(rearPulse, DEC);
    Serial.println("****************************");
    /* Arduino code end */
#elif defined PC
    /* PC code begin */
    printf("****************************\n");
    printf("Current status of the motors\n\n");
    printf("Left:  %d   Right: %d\n", leftPulse, rightPulse);
    printf("Front: %d   Rear:  %d\n", frontPulse, rearPulse);
    printf("****************************\n");
    /* PC code end */
#endif
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}

void sendMsg(void){
    struct pulses currentPulse = 
    {rightPulse, leftPulse, frontPulse, rearPulse};
    /* send(currentPulse);  not sure how the send funcrion till look like */
}

<<<<<<< HEAD
<<<<<<< HEAD
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
=======
#ifdef ARDUINO 
  //Arduino code begin
  Serial.println("****************************");
  Serial.println("Current status of the motors");
  Serial.print("Right:  ");
  Serial.println(rightMotor, DEC);
  Serial.print("Left:  ");
  Serial.println(leftMotor, DEC);
  Serial.print("Front:  ");
  Serial.println(frontMotor, DEC);
  Serial.print("Rear:  ");
  Serial.println(rearMotor, DEC);
  Serial.println("****************************");
  //Arduino code end
#elif defined PC
  //PC code begin
  printf("****************************\n");
  printf("Current status of the motors\n\n");
  printf("Left:  %d   Right: %d\n", leftMotor, rightMotor);
  printf("Front: %d   Rear:  %d\n", frontMotor, rearMotor);
  printf("****************************\n");
  //PC code end
#endif
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
}
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
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

/**
 * Function:    void sendMsg()
 * Author(s):   Björn Eriksson

 *
 * Description: sends a message as a struct to movement
 *              
 */

/*
 *
 *  function to sent the current pulses if we use the proto_read_motor()
 *
 *
void sendMsg(void){
    struct pulses currentPulsess = {rightPulse, leftPulse, 
                                    frontPulse, rearPulse};
    proto_write_move(currentPulses);
}

*/
>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
