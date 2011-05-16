<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*! @author Kristofer Hansson Aspman, Björn Eriksson, Magnus Bergqvist
 * @file moto_interface.c
 * @version v0.02
 * @date 2011-04-10
 * @history 2011-04-26 - Major cleanup and restructuring of the code\n
                        (Magnus, Björn, Kristofer)
            2011-04-10 - Created first version
                        (Magnus, Björn, Kristofer)
 * @brief Contains the implementations of moto_init and moto_run.\n
          Global variables set are: binary, mp, inputFromProto
 */

#include <stdint.h>
#include "moto_recv.h"
#include "moto_interface.h"
#include "moto_driver_functions.h"
#include "moto_msg_handler.h"

#ifdef ARDUINO_DBG
    #define ARDUINO
#endif

#ifdef ARDUINO
    #include "../include/Servo.h"
    #include "WProgram.h"
#elif defined PC
    #include <stdio.h>
    #include "moto_stubs.h"
#endif

msg_pointer mp;
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
/*! @author Kristofer Hansson Aspman
 * @file moto_interface.c
 * @version v0.01
 * @date 2011-04-10
 * @brief Contains the implementations of moto_init and moto_run
 */

#ifdef ARDUINO_DBG
	#define ARDUINO
#endif

#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

//#include "

#include "proto_mov_motor.h"
#include "moto_interface.h"
#include "moto_msg_manipulation.h"
#include "moto_driver_functions.h"
#include "moto_msg_handler.h"

msg binary;
msg_pointer mp;
unsigned char inputFromProto; 
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

#ifdef ARDUINO
/* Pins for testing */
int ledPin = 13;
<<<<<<< HEAD
<<<<<<< HEAD
/* Servo "objects" definitions for the ESCs */
Servo escRight;
Servo escLeft;
Servo escFront;
Servo escRear;
#endif

/*! @author Kristofer Hansson Aspman, Björn Eriksson, Magnus Bergqvist
 * @brief The init function requested by the CFG. It is
          called when the drone boots up.
 * @version v0.02
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#endif

/*! @author Kristofer Hansson Aspman
 * @brief The init function requested by the CFG. It is
          called when the drone boots up.
 * @version v0.01
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
 * @date 2011-04-10
 * @param none
 * @return int (0 if correctly carried out)
 */
int moto_init(void){
<<<<<<< HEAD
<<<<<<< HEAD
#ifdef ARDUINO
    Serial.begin(9600); 
    escRight.attach(RIGHT_MOTOR);
    escLeft.attach(LEFT_MOTOR);
    escFront.attach(FRONT_MOTOR);
    escRear.attach(REAR_MOTOR);
    escRight.writeMicroseconds(STOP_PULSE);
    escLeft.writeMicroseconds(STOP_PULSE);
    escFront.writeMicroseconds(STOP_PULSE);
    escRear.writeMicroseconds(STOP_PULSE);
    pinMode(ledPin, OUTPUT);
#endif
  moto_cyclesSinceLastMsg = 0;
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
  moto_cyclesSinceLastMsg = 0;
  mp = &binary;
#ifdef ARDUINO
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
#elif defined PC
        //------------------------------------------------------missing
#endif
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
  return 0;
}

/*! @author Kristofer Hansson Aspman
 * @brief The run function requested by the CFG. It is run
          each scheduled cycle.
 * @version v0.01
 * @date 2011-04-10
 * @param none
 * @return int (0 if correctly carried out)
 */
int moto_run(void){
    moto_cyclesSinceLastMsg++;
<<<<<<< HEAD
<<<<<<< HEAD
    mp = moto_recvMsg();
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    inputFromProto = read_motor();
    binary = INT_TO_BITFIELD(&inputFromProto);

#if defined ARDUINO_DBG
    binary = scanHexMsgSTDIN();
#endif
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

    if(BITFIELD_TO_CHAR(mp) == 0xf1)
    {
#ifdef ARDUINO_DBG
      Serial.println("No new message in protocol");
#elif defined PC
      printf("No new message in protocol\n");
#endif
      return 0;
    }
<<<<<<< HEAD
<<<<<<< HEAD

    if(BITFIELD_TO_CHAR(mp) == 0xf)
    {
#ifdef ARDUINO_DBG
      Serial.println("No new message in scanhexmsg");
#elif defined PC
      printf("No new message in scanhexmsg\n");
#endif
      return 0;
    }

    moto_cyclesSinceLastMsg = 0;
=======
    moto_cyclesSinceLastMsg = 0;

>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
    moto_cyclesSinceLastMsg = 0;

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    examineID(mp);

#ifdef ARDUINO_DBG
  printMsg(mp);
  printMotorStatus();

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
  /* if(leftPulse > 0 && rightPulse > 0 && frontPulse > 0 && rearPulse > 0){ */
  /*   digitalWrite(13, HIGH);   */
  /* } */
  /* else */
  /*   digitalWrite(13, LOW); */

<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#elif defined PC
    printMsg(mp);
    printMotorStatus();
    
#endif
    return 0;
<<<<<<< HEAD
<<<<<<< HEAD
=======
#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

#include "moto_interface.h"
#include "moto_msg_manipulation.h"
#include "moto_driver_functions.h"
#include "moto_msg_handler.h"

msg binary;
msg_pointer mp;

#ifdef ARDUINO
//Pins for testing
int ledPin = 13;

/* void setup(){ */
/* } */

/* void loop(){ */
/*   Serial.println("Inside loop, before"); */
/*   moto_run(); */
/*   Serial.println("Inside loop"); */
/* } */
#endif

int moto_init(void){
  mp = &binary;
#ifdef ARDUINO
  Serial.println("Exited Loop");
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
#elif defined PC
#endif

  return 0;
}

int moto_run(void){
#ifdef ARDUINO
  binary = scanHexMsgSTDIN();
  //  delay(200);
  examineID(mp);
  
  if(leftMotor > 0 && rightMotor > 0 && frontMotor > 0 && rearMotor > 0){
    digitalWrite(13, HIGH);  
  }
  else
    digitalWrite(13, LOW);
  
  printMsg(mp);
  printMotorStatus();
  //  delay(5000);
#elif defined PC
    binary = scanHexMsgSTDIN();
    examineID(mp);
    printMsg(mp);
    printMotorStatus();

#endif
  return 0;
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}
=======
/*!@author Kristofer Hansson Aspman, Björn Eriksson, Magnus Bergqvist
 * @file moto_interface.c
 * @version v0.05
 * @date 2011-05-16
 * @history 2011-05-16 - Implemented no-op instructions
                        (Kristofer)
            2011-05-11 - Worked with ifdefs
                        (Magnus, Björn)
            2011-05-10 - Added support for struct containing 8 messages
                        (Magnus, Björn, Kristofer)
            2011-04-26 - Major cleanup and restructuring of the code\n
                        (Magnus, Björn, Kristofer)
            2011-04-10 - Created first version
                        (Magnus, Björn, Kristofer)

 * @brief Contains the implementations of moto_init and moto_run.\n
          Global variables set are: mp (a pointer to the hexadecimal message
 *        read from the protocol).
 */

#include <stdint.h>
#include "moto_recv.h"
#include "moto_interface.h"
#include "moto_driver_functions.h"
#include "moto_msg_handler.h"
#include "moto_printer_functions.h"
#include "moto_state_definitions.h"

#ifdef ARDUINO
    #include "../include/Servo.h"
    #include "WProgram.h"
#elif defined PC
    #include <stdio.h>
    #include "moto_stubs.h"
#endif

/* Stores the address to the actual bitfield containing the hex msg */
msg_pointer mp;

#ifdef ARDUINO
/* Pins for testing */
int ledPin = 13;
/* Servo "objects" definitions for the ESCs */
Servo escRight;
Servo escLeft;
Servo escFront;
Servo escRear;
#endif

/*! @author Kristofer Hansson Aspman, Björn Eriksson, Magnus Bergqvist
 * @brief The init function requested by the CFG. It is
          called when the drone boots up.
 * @version v0.04
 * @date 2011-05-01
 * @param none
 * @return int (0 if correctly carried out)
 */
int moto_init(void){
    PRINT_STRING("Inside moto_init");
    PRINT_NEW_LINE;
#ifdef ARDUINO
    escRight.attach(RIGHT_MOTOR);
    escLeft.attach(LEFT_MOTOR);
    escFront.attach(FRONT_MOTOR);
    escRear.attach(REAR_MOTOR);
    escRight.writeMicroseconds(STOP_PULSE);
    escLeft.writeMicroseconds(STOP_PULSE);
    escFront.writeMicroseconds(STOP_PULSE);
    escRear.writeMicroseconds(STOP_PULSE);
    pinMode(ledPin, OUTPUT);
#endif
  moto_cyclesSinceLastMsg = 0;
  return 0;
}

/*! @author Kristofer Hansson Aspman
 * @brief The run function requested by the CFG. It is run
          each scheduled cycle.
 * @version v0.04
 * @date 2011-05-16
 * @param none
 * @return int (0 if correctly carried out)
 */
int moto_run(void){
    moto_cyclesSinceLastMsg++;
    PRINT_STRING("Number of cycles without a message: ");
    PRINT_DEC(moto_cyclesSinceLastMsg);
    PRINT_NEW_LINE;

/* Initiates no-op command if no message has been written to the protocol
 * in 5000 cycles. No-op command is currently set to HOVER but can be changed
 * whatever command preferred.
 */
    if (moto_cyclesSinceLastMsg > 5000)
    {
        PRINT_STRING("No new message in protocol for too long!");
        PRINT_NEW_LINE;
        PRINT_STRING("Initiating no-op command!");
        PRINT_NEW_LINE;

/* Set the uint8_t to HOVER and then casting it to a msg before sending
 * it to examineID() to be parsed.
 */
        uint8_t no_op_hex = HOVER;
        msg no_op_msg = INT_TO_BITFIELD(&no_op_hex);
        mp = &no_op_msg;
        examineID(mp);
        moto_cyclesSinceLastMsg = 0;
        return 0;
    }

/*
 *  when moto_recvMsg() is used
 *  ----------------------------------------------
 *   mp = moto_recvMsg(); 
 *  ----------------------------------------------
 */

/*
 * if moto_recvMsg2() is used
 * 
 * for loop and "uint8_t i" SHALL be removed
 */

/* ---------------this one------------------------ */
    msgStructPtr mpStruct;
    mpStruct = moto_recvMsg2();
    mp = (msg_pointer)&(mpStruct->msg1);
/* ----------------------------------------------- */



    /* will always receive 8 messages in the loop from struct */
    uint8_t i;
    for(i = 0; i < 8; i++){
        PRINT_STRING("msg is: ");
        PRINT_HEX(BITFIELD_TO_CHAR(mp));
        PRINT_NEW_LINE;

        if(BITFIELD_TO_CHAR(mp) == 0xf1){
            PRINT_STRING("No new message in protocol");
            PRINT_NEW_LINE;
            return 0;
        }

/*Resets the counter that counts how many cycles has run since last message*/
/*was written to protocol.*/
        moto_cyclesSinceLastMsg = 0;
        if(BITFIELD_TO_CHAR(mp) < 0x0 || BITFIELD_TO_CHAR(mp) > 0xff)
        {
            PRINT_STRING("Message out of bounds");
            PRINT_NEW_LINE;
            return 0;
        }

        if(BITFIELD_TO_CHAR(mp) == 0xf)
        {
            PRINT_STRING("No new message in scanhexmsg");
            PRINT_NEW_LINE;
            return 0;
        }

        if(BITFIELD_TO_CHAR(mp) == 0xB)
        {
            PRINT_STRING("Struct does not contain more messages!");
            PRINT_NEW_LINE;
            return 0;
        }

        examineID(mp);

        printMsg(mp);
        printMotorStatus();
/*
 *
 *  mp++ for moto_recvMsg2() 
 *  used when using the struct of messages
 * 
 */
        mp++;
        } /* ends the for loop */
    return 0;
}
>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
