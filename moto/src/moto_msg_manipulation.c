/**
 * Module:       message.c
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description:  Contains necessary tools
 *               for handling the messages.
 *
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

void printMsg(msg_pointer mp){
#ifdef ARDUINO_DBG
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

#elif defined PC//PC Code
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
}
