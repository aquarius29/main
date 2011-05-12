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


#ifdef ARDUINO
void print_speed_dangerzone(int speed, int dangerzone){
	Serial.println("================================");
	Serial.print("Quadrocopter travels at speed ");
	Serial.print(speed);
	Serial.println();
	Serial.print("Dangerous zone is ");
	Serial.print(dangerzone);
	Serial.println();
}

void print_dangerzone_ir(unsigned char *irBooleans){
	Serial.println("================================");
	Serial.print("Result for which ir is triggered:");
	outputIR(irBooleans);
}

void print_result_after_dangerzone(unsigned char *result){
	Serial.println("================================");
	Serial.println("after filter the according to the ir BOOLEANS");
	print_result(result);
}

void print_result_after_flying_dir(int dir, unsigned char *result){
	Serial.println("================================");
	Serial.println("Quadrocopter heading towards ");
	outputdirection(dir);
	Serial.println("================================");
	Serial.println("after filter according to the heading directions");
	print_result(result);
}

void print_movingCloser_ir(unsigned char *moving_close){
	Serial.println("================================");
	Serial.println("Result for which direction is moving closer");
	outputIR(moving_close);
}

void print_result_after_movingCloser(unsigned char *result){
Serial.println("================================");
	Serial.println("after filter according to the moving object\n");
	print_result(result);
}

void print_final_result(unsigned char *result){
	Serial.println("========FINAL=============");
	print_result(result);
}

void print_final_direction(int finalDir){
	Serial.println("================================");
	Serial.println("IF I HAVE TO PICK A DIRECTION\nI CHOOSE ");
	outputdirection(finalDir);
}
/*translate the output of IR*/
void outputIR(unsigned char *result)
{
	Serial.print("detects an object at ");

    if (*result == 1) {
		Serial.print("\n Front");
	}

    if (*(result + 1) == 1) {
		Serial.print("\n Back  ");
	}

    if (*(result + 2) == 1) {
		Serial.print("\n Left");
	}

	if (*(result + 3) == 1){
		Serial.print("\n Right ");
	}
	Serial.println();
}

/*
 * translate the current direction
 * {front, back, left, right, hover}
 */
void outputdirection(int direction)
{
    switch (direction) {

    case 0:
		Serial.print("Hover\n");
		break;

    case 1:
		Serial.print("Front\n");
		break;

    case 2:
		Serial.print("Back\n");
		break;

    case 3:
		Serial.print("Left\n");
		break;

    case 4:
		Serial.print("Right\n ");
		break;

	case 5:
		Serial.print("SAME AS CURRENT DIR\n ");
		break;

    default:
		Serial.print("NO PLACE TO GO\n");
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
			Serial.print("Front is ");
			Serial.println(answer);
		}

		if (i == 1){
			Serial.print("Back is ");
			Serial.println(answer);
		}

		if (i == 2){
			Serial.print("Left is ");
			Serial.println(answer);
		}

		if (i == 3){
			Serial.print("Right is ");
			Serial.println(answer);
		}

		if (i == 4){
			Serial.print("Hover is ");
			Serial.println(answer);
		}
    }
}


#elif defined PC

void print_speed_dangerzone(int speed, int dangerzone){
	printf("\n================================\n");
	printf("Quadrocopter travels at speed %d\n", speed);
	printf("dangerous zone is %d\n", dangerzone);
}

void print_dangerzone_ir(unsigned char *irBooleans){
	printf("\n================================\n");
	printf("Result for which ir is triggered: \n");
	outputIR(irBooleans);
}

void print_result_after_dangerzone(unsigned char *result){
	printf("\n================================\n");
	printf ("after filter the according to the ir BOOLEANS\n\n");
	print_result(result);
}

void print_result_after_flying_dir(int dir, unsigned char *result){
	printf("\n================================\n");
	printf("Quadrocopter heading towards ");
	outputdirection(dir);
	printf("\n================================\n");
	printf("after filter according to the heading directions\n\n");
	print_result(result);
}

void print_movingCloser_ir(unsigned char *moving_close){
	printf("\n================================\n");
	printf("Result for which direction is moving closer \n");
	outputIR(moving_close);
}

void print_result_after_movingCloser(unsigned char *result){
	printf("\n================================\n");
	printf("after filter according to the moving object\n");
	print_result(result);
}

void print_final_result(unsigned char *result){
	printf("\n================================\n");
	printf("\nFINAL\n\n");
	print_result(result);
}

void print_final_direction(int finalDir){
	printf("\n================================\n");
	printf("\nIF I HAVE TO PICK A DIRECTION\nI CHOOSE ");
	outputdirection(finalDir);
}

/*translate the output of IR*/
void outputIR(unsigned char *result)
{
	printf("\n detects an object at ");

    if (*result == 1) {
		printf("\n Front ");
	}

    if (*(result + 1) == 1) {
		printf("\n Back ");
	}

    if (*(result + 2) == 1) {
		printf("\n Left ");
	}
	if (*(result + 3) == 1){
		printf("\n Right ");
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
		printf("Hover\n");
		break;

    case 1:
		printf("Front\n ");
		break;

    case 2:
		printf("Back\n ");
		break;

    case 3:
		printf("Left\n ");
		break;

    case 4:
		printf("Right\n ");
		break;

	case 5:
		printf("SAME AS CURRENT DIR\n ");
		break;

    default:
		printf("NO PLACE TO GO\n");
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
			printf("Front is %s\n", answer);
		}

		if (i == 1){
			printf("Back is %s\n", answer);
		}

		if (i == 2){
			printf("Left is %s\n", answer);
		}

		if (i == 3){
			printf("Right is %s\n", answer);
		}

		if (i == 4){
			printf("Hover is %s\n", answer);
		}
    }
}
#endif
