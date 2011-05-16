/*! @author Kristofer Hansson Aspman, Reza Moussavi
 * @file moto_msg_handler.c
 * @version v0.01
 * @date 2011-04-14
 * @brief Contains the functions that
 *        sets the pulse width of the
 *        different motors.
 */

#include <stdint.h>
#include "moto_interface.h"
#include "moto_msg_manipulation.h"
#include "moto_msg_handler.h"
#include "moto_driver_functions.h"
#include "moto_state_definitions.h"

#ifdef ARDUINO_DBG
    #define ARDUINO
#endif

#ifdef ARDUINO
    #include "WProgram.h"
#elif defined PC
    #include <stdio.h>
#endif


int examineID(msg_pointer mp){
#ifdef ARDUINO_DBG
    Serial.print("ID is ");
    Serial.println(mp->ID, DEC);
    if (BITFIELD_TO_CHAR(mp) == BAD_MESSAGE){
        Serial.println("Bad message!");
        return 1;
    }
    if (BITFIELD_TO_CHAR(mp) > 0xFF){
        Serial.println("Message value too high, ignoring message!");
        return 1;
    }
#elif defined PC
    printf("ID is %d\n", mp->ID);
    if (BITFIELD_TO_CHAR(mp) == BAD_MESSAGE){
        printf("Bad message!\n");
        return 1;
    }
    if (BITFIELD_TO_CHAR(mp) > 0xFF){
        printf("Message value too high, ignoring message!\n");
        return 1;
    }

#endif

    switch(mp->ID){

    case START_ID:
        moto_startMotors();
        break;
    case STOP_ID:
        moto_stopMotors();
        break;
    case CONTROL_ID:
        controlMotors(mp);
        break;
    case SPECIAL_COMMAND_ID:
        specialMotorCommand(mp);
        break;
    }

    return 0;
}

/*
*	Function:		controlMotors(msg_pointer)
*	Author(s):		Reza Moussavi, Rahwa Bahta
*	Description:	Optimized last one
*/

/* changed this one to old since it's not followig the architecture 
 * and the other one is easier to modify and work with
 */

void OLD_controlMotors(msg_pointer mp){
	#ifdef ARDUINO_DBG
		Serial.print("Standard Motor Control Message!\n");
	#elif defined PC 
		printf("Standard Motor Control Message!\n");
	#endif

	if(mp->left)    moto_left_motor(mp->increase,mp->panic);
	if(mp->right)	moto_right_motor(mp->increase,mp->panic);
	if(mp->front)	moto_front_motor(mp->increase,mp->panic);
	if(mp->rear)	moto_rear_motor(mp->increase,mp->panic);
}

  /* This has been renamed to OLDxxxx to prevent duplication */
  /*  The new one Implemented up here */

void controlMotors(msg_pointer mp){
#ifdef ARDUINO_DBG
    Serial.print("Standard Motor Control Message!\n");
#elif defined PC 
    printf("Standard Motor Control Message!\n");
#endif

    /*Normal increase of the motors*/
    /*i.e. panic mode not set.*/
    if (mp->increase == 1 && mp->panic == 0){
        if(mp->left == 1)
            moto_increaseLeftNormal();
        if(mp->right == 1)
            moto_increaseRightNormal();
        if(mp->front == 1)
            moto_increaseFrontNormal();
        if(mp->rear == 1)
            moto_increaseRearNormal();
    }

    /*Panic increase of the motors*/
    /*i.e. panic mode set.*/
    if (mp->increase == 1 && mp->panic == 1){
        if(mp->left == 1)
            moto_increaseLeftPanic();
        if(mp->right == 1)
            moto_increaseRightPanic();
        if(mp->front == 1)
            moto_increaseFrontPanic();
        if(mp->rear == 1)
            moto_increaseRearPanic();
    }
  
    /*Normal decrease of the motors*/
    /*i.e. panic mode not set.*/
    if (mp->increase == 0 && mp->panic == 0){
        if(mp->left == 1)
            moto_decreaseLeftNormal();
        if(mp->right == 1)
            moto_decreaseRightNormal();
        if(mp->front == 1)
            moto_decreaseFrontNormal();
        if(mp->rear == 1)
            moto_decreaseRearNormal();
    }
  
    /*Panic decrease of the motors*/
    /*i.e. panic mode set.*/
    if (mp->increase == 0 && mp->panic == 1){
        if(mp->left == 1)
            moto_decreaseLeftPanic();
        if(mp->right == 1)
            moto_decreaseRightPanic();
        if(mp->front == 1)
            moto_decreaseFrontPanic();
        if(mp->rear == 1)
            moto_decreaseRearPanic();
    }
    return;
}

void specialMotorCommand(msg_pointer mp){
#ifdef ARDUINO_DBG
    Serial.print("Special Motor Control Message!\n");
#elif defined PC
    printf("Special Motor Control Message!\n");
#endif

    switch(BITFIELD_TO_CHAR(mp)){
    
    case FORWARD:
        moto_goForward();
        break;
    case BACKWARD:
        moto_goBackward();
        break;
    case TURN_LEFT:
        break;
    case TURN_RIGHT:
        break;
    case STRAFE_LEFT:
        moto_strafeLeft();
        break;
    case STRAFE_RIGHT:
        moto_strafeRight();
        break;
    case INCREASE_ALL_NORMAL:
        moto_increaseAllNormal();
        break;
    case DECREASE_ALL_NORMAL:
        moto_decreaseAllNormal();
        break;
    case INCREASE_ALL_PANIC:
        moto_increaseAllPanic();
        break;
    case DECREASE_ALL_PANIC:
        moto_decreaseAllPanic();
        break;
    case HOVER:
        moto_hover();
        break;
    }

  return;

}
