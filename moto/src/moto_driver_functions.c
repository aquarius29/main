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
#endif

#ifdef ARDUINO
    #include "WProgram.h"
#elif defined PC
    #include <stdio.h>
#endif

#include "moto_driver_functions.h"
#include <stdint.h>

/* These are the variables keeping track of the  */
/* current state (pulse width) of each motor. */
uint16_t rightPulse;
uint16_t leftPulse;
uint16_t frontPulse;
uint16_t rearPulse;

/**
 * Function:    void moto_startMotors()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Sets the pulse width to a state where
 *              all motors starts spinning but the
 *              drone does not lift off.
 *
 */
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
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#endif
}

/**
 * Function:    void moto_stopMotors()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Stops all motors, i.e. sets the
 *              pulse width to zero.
 *
 */
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
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#endif
}
/**
 * Function:    void moto_hover()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
 *
 * Description: Sets all motors to the same pulse width
 *              where to drone shall stay in hover state
 *
 */
void moto_hover(void){
    rightPulse =90;
    leftPulse = 90;
    frontPulse = 90;
    rearPulse = 90;

#ifdef ARDUINO
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#elif defined PC
    printf("Hovering\n");
#endif    
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
    rightPulse += NORMAL_INCREMENT;
    leftPulse += NORMAL_INCREMENT;
    frontPulse += NORMAL_INCREMENT;
    rearPulse += NORMAL_INCREMENT;

#ifdef ARDUINO
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
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
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#elif defined PC
    printf("increases all motors\n");
#endif
}
/**
 * Functions:   moto_decreaseAll()
 *              moto_decreaseAllPanic()
 * Author(s):   Kristofer Hansson Aspman,
 *              Björn Eriksson
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
    rightPulse += NORMAL_DECREMENT;
    leftPulse += NORMAL_DECREMENT;
    frontPulse += NORMAL_DECREMENT;
    rearPulse += NORMAL_DECREMENT;

#ifdef ARDUINO
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
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
    analogWrite(RIGHT_MOTOR, rightPulse);
    analogWrite(LEFT_MOTOR, leftPulse);
    analogWrite(FRONT_MOTOR, frontPulse);
    analogWrite(REAR_MOTOR, rearPulse);
#elif defined PC
    printf("increases all motors\n");
#endif
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
 *
 * Description: Increases the pulse width of
 *              the corresponding motor.
 *              Pulse width increases either
 *              by the predefined normal
 *              increment or by the predefined
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
}

void sendMsg(void){
    struct pulses currentPulse = 
    {rightPulse, leftPulse, frontPulse, rearPulse};
    /* send(currentPulse);  not sure how the send funcrion till look like */
}

