<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
/*! @author Kristofer Hansson Aspman, Reza Moussavi
 * @file moto_msg_handler.c
 * @version v0.01
 * @date 2011-04-14
 * @brief Contains the functions that
 *        sets the pulse width of the
 *        different motors.
 */

<<<<<<< HEAD
#include <stdint.h>
=======
/**
 * Module:       moto_msg_handler.c
 * Author(s):    Kristofer Hansson Aspman
 *               Reza Moussavi
 *
 * Description:  Contains the functions that
 *               sets the pulse width of the
 *               different motors.
 *
 */
=======
#ifdef ARDUINO_DBG
	#define ARDUINO
#endif
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16

#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

<<<<<<< HEAD
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
#include "moto_interface.h"
#include "moto_msg_manipulation.h"
#include "moto_msg_handler.h"
#include "moto_driver_functions.h"
#include "moto_state_definitions.h"

<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
/* //These definitions will go into a separate file later on. */
/* #define STOP 0x00 */
/* #define STOP_ID 0x00 */
/* #define START 0x40 */
/* #define START_ID 0x01 */
/* #define CONTROL_ID 0x02 */
/* #define SPECIAL_COMMAND_ID 0x03 */
/* #define BAD_MESSAGE 0xf // when bits are not within the 0-255 range */
/* #define GO_FORWARD 0xe3 // 1110 0011 */
/* #define GO_BACKWARD 0xc3 // 1100 0011 */

<<<<<<< HEAD
void examineID(msg_pointer mp){
#ifdef ARDUINO
=======
int examineID(msg_pointer mp){
#ifdef ARDUINO_DBG
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  Serial.print("ID is ");
  Serial.println(mp->ID, DEC);
  if (BITFIELD_TO_CHAR(mp) == BAD_MESSAGE){
    Serial.println("Bad message!");
<<<<<<< HEAD
    return;
=======
    return 1;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  }
#elif defined PC
  printf("ID is %d\n", mp->ID);
  if (BITFIELD_TO_CHAR(mp) == BAD_MESSAGE){
    printf("Bad message!\n");
<<<<<<< HEAD
    return;
  }
#endif
=======
    return 1;
  }
#endif
  if (BITFIELD_TO_CHAR(mp) == BAD_MESSAGE){
    return 1;
  }
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16

  switch(mp->ID){

  case START_ID:
<<<<<<< HEAD
    _moto_startMotors();
    break;
  case STOP_ID:
    _moto_stopMotors();
=======
    moto_startMotors();
    break;
  case STOP_ID:
    moto_stopMotors();
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
    break;
  case CONTROL_ID:
    controlMotors(mp);
    break;
  case SPECIAL_COMMAND_ID:
    specialMotorCommand(mp);
    break;
  }

<<<<<<< HEAD
  return;
}

void controlMotors(msg_pointer mp){
#ifdef ARDUINO
  Serial.print("Standard Motor Control Message!\n");
#elif defined PC  
=======
  return 0;
}

void controlMotors(msg_pointer mp){
#ifdef ARDUINO_DBG
  Serial.print("Standard Motor Control Message!\n");
#elif defined PC 
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  printf("Standard Motor Control Message!\n");
#endif

  //Normal increase of the motors
  //i.e. panic mode not set.
  if (mp->increase == 1 && mp->panic == 0){
    if(mp->left == 1)
<<<<<<< HEAD
      _moto_increaseLeftNormal();
    if(mp->right == 1)
      _moto_increaseRightNormal();
    if(mp->front == 1)
      _moto_increaseFrontNormal();
    if(mp->rear == 1)
      _moto_increaseRearNormal();
=======
      moto_increaseLeftNormal();
    if(mp->right == 1)
      moto_increaseRightNormal();
    if(mp->front == 1)
      moto_increaseFrontNormal();
    if(mp->rear == 1)
      moto_increaseRearNormal();
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  }

  //Panic increase of the motors
  //i.e. panic mode set.
  if (mp->increase == 1 && mp->panic == 1){
    if(mp->left == 1)
<<<<<<< HEAD
      _moto_increaseLeftPanic();
    if(mp->right == 1)
      _moto_increaseRightPanic();
    if(mp->front == 1)
      _moto_increaseFrontPanic();
    if(mp->rear == 1)
      _moto_increaseRearPanic();
=======
      moto_increaseLeftPanic();
    if(mp->right == 1)
      moto_increaseRightPanic();
    if(mp->front == 1)
      moto_increaseFrontPanic();
    if(mp->rear == 1)
      moto_increaseRearPanic();
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  }
  
  //Normal decrease of the motors
  //i.e. panic mode not set.
  if (mp->increase == 0 && mp->panic == 0){
    if(mp->left == 1)
<<<<<<< HEAD
      _moto_decreaseLeftNormal();
    if(mp->right == 1)
      _moto_decreaseRightNormal();
    if(mp->front == 1)
      _moto_decreaseFrontNormal();
    if(mp->rear == 1)
      _moto_decreaseRearNormal();
=======
      moto_decreaseLeftNormal();
    if(mp->right == 1)
      moto_decreaseRightNormal();
    if(mp->front == 1)
      moto_decreaseFrontNormal();
    if(mp->rear == 1)
      moto_decreaseRearNormal();
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  }
  
  //Panic decrease of the motors
  //i.e. panic mode set.
  if (mp->increase == 0 && mp->panic == 1){
    if(mp->left == 1)
<<<<<<< HEAD
      _moto_decreaseLeftPanic();
    if(mp->right == 1)
      _moto_decreaseRightPanic();
    if(mp->front == 1)
      _moto_decreaseFrontPanic();
    if(mp->rear == 1)
      _moto_decreaseRearPanic();
=======
      moto_decreaseLeftPanic();
    if(mp->right == 1)
      moto_decreaseRightPanic();
    if(mp->front == 1)
      moto_decreaseFrontPanic();
    if(mp->rear == 1)
      moto_decreaseRearPanic();
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  }
  return;
}

void specialMotorCommand(msg_pointer mp){
<<<<<<< HEAD
#ifdef ARDUINO
=======
#ifdef ARDUINO_DBG
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  Serial.print("Special Motor Control Message!\n");
#elif defined PC
  printf("Special Motor Control Message!\n");
#endif

  switch(BITFIELD_TO_CHAR(mp)){
  case FORWARD:
<<<<<<< HEAD
    _moto_goForward();
    break;
  case BACKWARD:
    _moto_goBackward();
=======
    moto_goForward();
    break;
  case BACKWARD:
    moto_goBackward();
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
    break;
  case TURN_LEFT:
    break;
  case TURN_RIGHT:
    break;
  case STRAFE_LEFT:
<<<<<<< HEAD
    _moto_strafeLeft();
    break;
  case STRAFE_RIGHT:
    _moto_strafeRight();
=======
    moto_strafeLeft();
    break;
  case STRAFE_RIGHT:
    moto_strafeRight();
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
    break;
  }

  return;

}


/**
 * Function:     msg scanHexMsgSTDIN()
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description: When compiling for the ARDUINO this 
 *              converts the char given by serReadUnsignedChar()
 *              into a msg and returns it.
 *              When compiling for PC scanf() is used to read
 *              the variable.
 *              
 *
 */

msg scanHexMsgSTDIN(void){

<<<<<<< HEAD
#ifdef ARDUINO
=======
#ifdef ARDUINO_DBG
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
    unsigned char input;
    Serial.println("Enter the message in hexadecimal!");
  
    input = serReadUnsignedChar();

    Serial.print("Number entered: ");
    Serial.println(input, HEX);
  
    if (input > -1 || input < 256)
      return INT_TO_BITFIELD(&input);
    else
      return INT_TO_BITFIELD(0xf); //returns BAD_MSG

#elif defined PC
    unsigned int input;
    printf("Enter the message in hexadecimal: ");
    scanf("%x", &input);
    return INT_TO_BITFIELD(&input);
#endif
}

/**
 * Function:     unsigned char serReadUnsignedChar()
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description: Reads and stores what's currently in
 *              Serial.available() in an array.
 *              If there is something in the serial in
 *              then this is converted to an unsigned char
 *              with the help of sscanf() and returned.
 *              Otherwise 0xf is returned which is
 *              considered a bad message.
 *              Only used when compiled to ARDUINO.
 *              
 * Inspired by reply number 3 in this thread:
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1191880368
 */
<<<<<<< HEAD

#ifdef ARDUINO
=======
#ifdef ARDUINO_DBG
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
unsigned char serReadUnsignedChar(void)
{
  int i, numberOfAvailableInputs;
  unsigned char returnValue;
  char inputBytes [7];                     // Array to hold input bytes
  char * inputBytesPtr = &inputBytes[0];
  
  if (Serial.available()>0)                // Check to see if there are any serial input
    {
      delay(5);                              // Delay for terminal to finish transmitted
                                             // 5mS work great for 9600 baud (increase this number for slower baud)
      numberOfAvailableInputs = Serial.available();
      for (i=0; i<numberOfAvailableInputs; i++)       // Load input bytes into array
	inputBytes[i] = Serial.read();
      inputBytes[i] =  '\0';             // Adding a NULL character at the end
      
      sscanf(inputBytes, "%x", &returnValue); //Scans the character string and stores it as a hexadecimal
      return returnValue;
    }
    
  else
    return 0xf;                         // Returns BAD_MSG 0xf (0000 1111) if there is no input
}
#endif
<<<<<<< HEAD
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
