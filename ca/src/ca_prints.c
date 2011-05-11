/*!
 *  @file ca_prints.c
 *
 *  @brief 
 *
 *  @author Yanling Jin, Amber Olsson
 *  @date 2011-04-26
 *  @history  2011-04-26  Jin - move these methods from ca_filters.c
 *                              add arduino print outs -Yanling Jin
 *  @details  
 */


/*
  .     IR1(FRONT)

  IR3(LEFT)   IR4(RIGHT)

  .     IR2(BACK)

  {front, back, left, right,hover}

*/

#ifdef ARDUINO
#include "WProgram.h"
#endif
#include <stdlib.h>
#include <stdio.h>

#include "ca_interface.h"

/*
 * translate the 0 and 1
 * return 0 as not ok, 1 as ok
 */
char *translate(int i)
{
    char *result;
    if (i == 0)
		result = "not ok";
    else
		result = "ok";

    return result;
}


/*translate the output of IR*/
void outputIR(unsigned char *result)
{

#ifdef ARDUINO
	Serial.print("detects an object at ");
#elif defined PC
	printf("\n detects an object at ");
#endif 

    if (*result == 1) {
#ifdef ARDUINO
		Serial.print("\n Front");
#elif defined PC
		printf("\n Front ");
#endif 
	}

    if (*(result + 1) == 1) {
#ifdef ARDUINO
		Serial.print("\n Back  ");
#elif defined PC
		printf("\n Back ");
#endif
	}

    if (*(result + 2) == 1) {
#ifdef ARDUINO
		Serial.print("\n Left");
#elif defined PC
		printf("\n Left ");
#endif 
	}
	if (*(result + 3) == 1){

#ifdef ARDUINO
		Serial.print("\n Right ");
#elif defined PC
		printf("\n Right ");
#endif 
	}
}

/*
 * translate the current direction
 * {front, back, left, right, hover}
 */
void outputdirection(int direction)
{
    switch (direction) {

    case 0:
#ifdef ARDUINO
		Serial.print("Hover\n");
#elif defined PC
		printf("Hover\n");
#endif 
		break;

    case 1:
#ifdef ARDUINO
		Serial.print("Front\n");
#elif defined PC
		printf("Front\n ");
#endif 
		break;

    case 2:
#ifdef ARDUINO
		Serial.print("Back\n");
#elif defined PC
		printf("Back\n ");
#endif
		break;

    case 3:
#ifdef ARDUINO
		Serial.print("Left\n");
#elif defined PC
		printf("Left\n ");
#endif 
		break;

    case 4:
#ifdef ARDUINO
		Serial.print("Right\n ");
#elif defined PC
		printf("Right\n ");
#endif 
		break;

    default:
#ifdef ARDUINO
		Serial.print("NO PLACE TO GO\n");
#elif defined PC
		printf("NO PLACE TO GO\n");
#endif 
    }
}


/*translate the result of the directions options*/
void print_result(unsigned char *result)
{
    int i;
    char *answer;

    for (i = 0; i < 5; i++) {
		answer = translate(*(result + i));

		if (i == 0){
#ifdef ARDUINO
			Serial.print("Front is ");
			Serial.println(answer);
#elif defined PC
			printf("Front is %s\n", answer);
#endif 
		}

		if (i == 1){
#ifdef ARDUINO
			Serial.print("Back is ");
			Serial.println(answer);
#elif defined PC
			printf("Back is %s\n", answer);
#endif 
		}

		if (i == 2){
#ifdef ARDUINO
			Serial.print("Left is ");
			Serial.println(answer);
#elif defined PC
			printf("Left is %s\n", answer);
#endif 
		}

		if (i == 3){
#ifdef ARDUINO
			Serial.print("Right is ");
			Serial.println(answer);
#elif defined PC
			printf("Right is %s\n", answer);
#endif 
		}

		if (i == 4){
#ifdef ARDUINO
			Serial.print("Hover is ");
			Serial.println(answer);
#elif defined PC
			printf("Hover is %s\n", answer);
#endif 
		}
    }
}
