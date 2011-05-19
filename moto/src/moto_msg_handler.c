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
#include "moto_printer_functions.h"



#ifdef ARDUINO
    #include "WProgram.h"
#endif


int examineID(msg_pointer mp){

    PRINT_STRING("ID is ");
    PRINT_DEC(mp->ID);
    PRINT_NEW_LINE;
    
    if (BITFIELD_TO_CHAR(mp) == BAD_MESSAGE){
        PRINT_STRING("Bad message!");
        PRINT_NEW_LINE;
        return 1;
    }
    if (BITFIELD_TO_CHAR(mp) > 0xFF){
        PRINT_STRING("Message value too high, ignoring message!");
        PRINT_NEW_LINE;
        return 1;
    }


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

void controlMotors(msg_pointer mp){
    PRINT_STRING("Standard Motor Control Message!");
    
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
    PRINT_STRING("Special Motor Control Message!");
    PRINT_NEW_LINE;

    switch(BITFIELD_TO_CHAR(mp)){
    
    case FORWARD:
        moto_goForward();
        break;
    case BACKWARD:
        moto_goBackward();
        break;
    case TURN_LEFT:
        moto_rotateLeft();
        break;
    case TURN_RIGHT:
        moto_rotateRight();
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
