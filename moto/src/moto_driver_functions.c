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
 *
 * Description: Sets the pulse width to a state where
 *              all motors starts spinning but the
 *              drone does not lift off.
 *
 */
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
 *
 * Description: Stops all motors, i.e. sets the
 *              pulse width to zero.
 *
 */
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
 *
 * Description: Increases the pulse width of
 *              of the rear motor and decreases
 *              the pulse width of the front
 *              motor. This makes the drone go
 *              forward.
 *
 */
void _moto_goForward(void){
  _moto_increaseRearNormal();
  _moto_decreaseFrontNormal();
  return;

}

/**
 * Function:    void _moto_goBackward()
 * Author(s):   Kristofer Hansson Aspman
 *
 * Description: Decreases the pulse width of
 *              of the rear motor and increases
 *              the pulse width of the front
 *              motor. This makes the drone go
 *              backward.
 *
 */
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
 *
 * Description: Increases either right or
 *              left motor and decreases
 *              the other in order to make
 *              the drone fly sideways to
 *              either left or right.
 *              
 */
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
 *              Pulse width increases either
 *              by the predefined normal
 *              increment or by the predefined
 *              panic increment.
 *
 */
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
 *
 * Description: Decreases the pulse width of
 *              the corresponding motor.
 *              Pulse width decreases either
 *              by the predefined normal
 *              decrement or by the predefined
 *              panic decrement.
 *
 */

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
}


/**
 * Function:     printMotorStatus()
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description:  Prints out the status of the
 *               motors to either the terminal
 *               or the serial monitor depending
 *               on whether the ARDUINO or PC
 *               flags are set.
 *
 */

void printMotorStatus(void){
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
}
