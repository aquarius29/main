/*!@author Kristofer Hansson Aspman
 * @file moto_msg_manipulation.h
 * @version v0.02
 * @date 2011-05-08
 *
 * @brief Intended to include the necessary tools to handle\n
 * the binary motor control msg.\n
 * Defines the types msg and msg_pointer, frequently used\n
 * within the code of the motor control component.\n
 * Various tools such as macros for casting and function\n
 * for printing are found here.
 *
 * @history 2011-04-03: First version.
 *          2011-04-07: Implemented ifdefs.
 *          2011-05-08: Cleaned up a bit and added some comments.
 */
#ifndef MOTO_MSG_MANIPULATION_H
    #define MOTO_MSG_MANIPULATION_H
#include <stdint.h>

#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
#ifdef ARDUINO
   #include "WProgram.h"
#endif

/* Casts a uint8_t into a pointer of type msg_pointer */
#define INT_TO_BITFIELD(a) *(msg_pointer)a

/* Casts a msg_pointer into a uint8_t */
#define BITFIELD_TO_CHAR(a) *(uint8_t*)a

/* Big endian control message
 * This is the actual bitfield used throughout
 * the motor control component.
 */
typedef struct control_message{
  uint8_t rear :1;
  uint8_t front :1;
  uint8_t left :1;
  uint8_t right :1;
  uint8_t panic :1;
  uint8_t increase :1;
  uint8_t ID :2;
} msg, *msg_pointer;

/*Little endian control message*/
/* struct control_message{ */
/*   uint8_t ID :2; */
/*   uint8_t increase :1; */
/*   uint8_t panic :1; */
/*   uint8_t right :1; */
/*   uint8_t left :1; */
/*   uint8_t front :1; */
/*   uint8_t rear :1; */

/* } msg, *msg_pointer; */

/*!@author Kristofer Hansson Aspman
 * @function printMsg
 * @param msg_pointer
 * @return void
 * @brief Simply prints out necessary debug information\n
 * such as the status of the motors and the bits of the message\n
 * sent in as a parameter to the functions.\n
 * Uses Serial.print or printf depending on what flag has been set\n
 * for the compilation (ARDUINO_DBG or PC respectively).
 */
void printMsg(msg_pointer mp);
#endif
