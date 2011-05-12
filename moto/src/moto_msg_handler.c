/*! @author Kristofer Hansson Aspman, Reza Moussavi
 * @file moto_msg_handler.c
 * @version v0.01
 * @date 2011-04-14
 * @brief Contains the functions that
 *        sets the pulse width of the
 *        different motors.
 */

#ifdef ARDUINO_DBG
	#define ARDUINO
#endif

#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

#include "moto_interface.h"
#include "moto_msg_manipulation.h"
#include "moto_msg_handler.h"
#include "moto_driver_functions.h"
#include "moto_state_definitions.h"

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

int examineID(msg_pointer mp){
#ifdef ARDUINO_DBG
  Serial.print("ID is ");
  Serial.println(mp->ID, DEC);
  if (BITFIELD_TO_CHAR(mp) == BAD_MESSAGE){
    Serial.println("Bad message!");
    return 1;
  }
#elif defined PC
  printf("ID is %d\n", mp->ID);
  if (BITFIELD_TO_CHAR(mp) == BAD_MESSAGE){
    printf("Bad message!\n");
    return 1;
  }
#endif
  if (BITFIELD_TO_CHAR(mp) == BAD_MESSAGE){
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
#ifdef ARDUINO_DBG
  Serial.print("Standard Motor Control Message!\n");
#elif defined PC 
  printf("Standard Motor Control Message!\n");
#endif

  //Normal increase of the motors
  //i.e. panic mode not set.
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

  //Panic increase of the motors
  //i.e. panic mode set.
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
  
  //Normal decrease of the motors
  //i.e. panic mode not set.
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
  
  //Panic decrease of the motors
  //i.e. panic mode set.
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

#ifdef ARDUINO_DBG
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
#ifdef ARDUINO_DBG
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
