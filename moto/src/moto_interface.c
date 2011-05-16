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
 * @version v0.02
 * @date 2011-04-10
 * @param none
 * @return int (0 if correctly carried out)
 */
int moto_init(void){
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
    mp = moto_recvMsg();

    if(BITFIELD_TO_CHAR(mp) == 0xf1)
    {
#ifdef ARDUINO_DBG
      Serial.println("No new message in protocol");
#elif defined PC
      printf("No new message in protocol\n");
#endif
      return 0;
    }

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
    examineID(mp);

#ifdef ARDUINO_DBG
  printMsg(mp);
  printMotorStatus();

#elif defined PC
    printMsg(mp);
    printMotorStatus();
    
#endif
    return 0;
}
