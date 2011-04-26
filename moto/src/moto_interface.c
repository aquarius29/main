/*! @author Kristofer Hansson Aspman
 * @file moto_interface.c
 * @version v0.01
 * @date 2011-04-10
 * @brief Contains the implementations of moto_init and moto_run
 */
#include <stdint.h>

#ifdef ARDUINO_DBG
	#define ARDUINO
#endif

#ifdef ARDUINO
    #include "../include/Servo.h"
    #include "WProgram.h"
#elif defined PC
    #include <stdio.h>
    #include "../test/cunit_stubs.h"
#endif

/* #include "proto_mov_motor.h" */
#include "moto_interface.h"
#include "moto_msg_manipulation.h"
#include "moto_driver_functions.h"
#include "moto_msg_handler.h"

msg binary;
msg_pointer mp;
uint8_t inputFromProto; 

#ifdef ARDUINO
/* Pins for testing */
int ledPin = 13;
/* Servo "objects" definitions for the ESCs */
Servo escRight;
Servo escLeft;
Servo escFront;
Servo escRear;
#endif

/*! @author Kristofer Hansson Aspman
 * @brief The init function requested by the CFG. It is
          called when the drone boots up.
 * @version v0.01
 * @date 2011-04-10
 * @param none
 * @return int (0 if correctly carried out)
 */
int moto_init(void){
#ifdef ARDUINO
    escRight.attach(9);
    escLeft.attach(9);
    escFront.attach(9);
    escRear.attach(9);
    escRight.writeMicroseconds(STOP_PULSE);
    escLeft.writeMicroseconds(STOP_PULSE);
    escFront.writeMicroseconds(STOP_PULSE);
    escRear.writeMicroseconds(STOP_PULSE);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600); 
#elif defined PC
        //------------------------------------------------------missing
#endif

  moto_cyclesSinceLastMsg = 0;
  mp = &binary;
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
    /* Uncomment to use together with protocol group */
    /* Also uncomment the include file at the top of the file */
    /* inputFromProto = read_motor(); */
    /* binary = INT_TO_BITFIELD(&inputFromProto); */
    binary = scanHexMsgSTDIN();

#if defined ARDUINO_DBG
    binary = scanHexMsgSTDIN();
#endif

    if(BITFIELD_TO_CHAR(mp) == 0xf1)
    {
#ifdef ARDUINO_DBG
      Serial.println("No new message in protocol");
#elif defined PC
      printf("No new message in protocol\n");
#endif
      return 0;
    }
    moto_cyclesSinceLastMsg = 0;

    examineID(mp);

#ifdef ARDUINO_DBG
  printMsg(mp);
  printMotorStatus();

  /* if(leftPulse > 0 && rightPulse > 0 && frontPulse > 0 && rearPulse > 0){ */
  /*   digitalWrite(13, HIGH);   */
  /* } */
  /* else */
  /*   digitalWrite(13, LOW); */

#elif defined PC
    printMsg(mp);
    printMotorStatus();
    
#endif
    return 0;
}
