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
#include "moto_printer_functions.h"


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
 * @version v0.01
 * @date 2011-04-10
 * @param none
 * @return int (0 if correctly carried out)
 */
int moto_run(void){
    moto_cyclesSinceLastMsg++;
    PRINT_STRING("Number of cycles without a message: ");
    PRINT_DEC(moto_cyclesSinceLastMsg);
    PRINT_NEW_LINE;


/*
 *
 *  maybe remove this if statement in the future 
 *
 */
    
    if (moto_cyclesSinceLastMsg > 10)
    {
        PRINT_STRING("No new message in protocol for too long!");
        PRINT_NEW_LINE;
        PRINT_STRING("Initiating no-op command!");
        PRINT_NEW_LINE;      
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
