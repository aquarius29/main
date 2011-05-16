<<<<<<< HEAD
/*!@author Kristofer Hansson Aspman & Magnus Bergqvist
 * @file moto_msg_manipulation.c
 * @version v0.03
 * @date 2011-05-09
 *
 * @brief Holds the implementations of the functions\n
 * described in the corresponding .h file. For\n
 * full description of the functions please refer\n
 * to that file.\n
 * Uses the types msg and msg_pointer defined in\n
 * moto_msg_manipulation.h.
 *
 * @history 2011-04-03: Created the file. (Kristofer)
 *          2011-04-07: Implemented ifdefs. (Kristofer)
 *          2011-05-08: Cleaned up a bit and added some comments. (Kristofer)
 *          2011-05-09: Created macros for printing. (Magnus & Kristofer)
 *          2011-05-09: Moved macros for printing, included .h file for it \n
 *                      to be used by other files as well (Magnus)          
 */
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif

#ifdef ARDUINO
    #include "WProgram.h"
#elif defined PC
    #include <stdio.h>
#endif

#include "moto_msg_manipulation.h"
#include "moto_printer_functions.h"

void printMsg(msg_pointer mp){
    PRINT_STRING("***********************************");
    PRINT_NEW_LINE;
    PRINT_NEW_LINE;
    PRINT_STRING("         Message Information");
    PRINT_NEW_LINE;
    PRINT_NEW_LINE;
    PRINT_STRING("Bits are:");
    PRINT_NEW_LINE;
    PRINT_STRING("ID: ");
    PRINT_DEC(mp->ID);
    PRINT_NEW_LINE;
    PRINT_STRING("Increase: ");
    PRINT_DEC(mp->increase);
    PRINT_NEW_LINE;
    PRINT_STRING("Panic: ");
    PRINT_DEC(mp->panic);
    PRINT_NEW_LINE;
    
    PRINT_STRING("Right: ");
    PRINT_DEC(mp->right);
    PRINT_NEW_LINE;
    PRINT_STRING("Left: ");
    PRINT_DEC(mp->left);
    PRINT_NEW_LINE;
    PRINT_STRING("Front: ");
    PRINT_DEC(mp->front);
    PRINT_NEW_LINE;
    PRINT_STRING("Rear: ");
    PRINT_DEC(mp->rear);
    
    PRINT_NEW_LINE;
    PRINT_STRING("Size of bitfield: ");
    PRINT_DEC(sizeof(*mp));
    PRINT_NEW_LINE;
    PRINT_STRING("Hexadecimal representation: ");
    PRINT_HEX(BITFIELD_TO_CHAR(mp));
    PRINT_NEW_LINE;
    PRINT_STRING("Decimal representation: ");
    PRINT_DEC(BITFIELD_TO_CHAR(mp));
    PRINT_NEW_LINE;
    
    PRINT_STRING("***********************************");
    PRINT_NEW_LINE;

=======
/**
 * Module:       message.c
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description:  Contains necessary tools
 *               for handling the messages.
 *
 */

#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

#include "moto_msg_manipulation.h"

void printMsg(msg_pointer mp){
#ifdef ARDUINO
  Serial.println("***********************************\n");
  Serial.println("         Message Information\n");
  Serial.println("\nBits are:\n");
  Serial.print("ID: ");
  Serial.println(mp->ID, DEC);
  Serial.print("Increase: ");
  Serial.println(mp->increase, DEC);
  Serial.print("Panic: ");
  Serial.println(mp->panic, DEC);
  
  Serial.print("Right: ");
  Serial.println(mp->right, DEC);
  Serial.print("Left: ");
  Serial.println(mp->left, DEC);
  Serial.print("Front: ");
  Serial.println(mp->front, DEC);
  Serial.print("Rear: ");
  Serial.println(mp->rear, DEC);

  Serial.print("\nSize of bitfield: ");
  Serial.println(sizeof(*mp), DEC);
  Serial.print("Hexadecimal representation: ");
  Serial.println(BITFIELD_TO_CHAR(mp), HEX);
  Serial.print("Decimal representation: ");
  Serial.println(BITFIELD_TO_CHAR(mp), DEC);

  Serial.println("***********************************");

#elif defined PC //PC Code
  printf("***********************************\n");
  printf("         Message Information\n");
  printf("\nBits are:\n-ID: %d\n-Incr: %d\n-Panic: %d\n",
	 mp->ID, mp->increase,
	 mp->panic);
  printf("-Left: %d\n-Right: %d\n-Front: %d\n-Rear: %d\n",
	 mp->left, mp->right, 
	 mp->front, mp->rear);

  printf("\nSize of bitfield: %ld\n", sizeof(*mp));
  printf("Hexadecimal representation: %x\n",
	 BITFIELD_TO_CHAR(mp));
  printf("Decimal representation: %d\n",
	 BITFIELD_TO_CHAR(mp));
  printf("***********************************\n");

#endif
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
}
