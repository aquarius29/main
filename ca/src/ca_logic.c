/*
 * file:         ca_logic.c
 * brief:
 * author:       Yanling Jin
 * date:         2011-04-26
 * version:      0.1
 * history       2011-03-30 Jin - create the file
 *               2011-03-31 Jin - fix the memory leak problem
 *               2011-04-26 Jin - add printouts for arduino and pc
 * detail:
 */

#include "ca_interface.h"

/* CHANGE HERE TO GET PRINTOUT OR REMOVE PRINTOUT */
const int PRINTABLE = 0;

#ifdef ARDUINO
#include "WProgram.h"
#define IRPIN1 0
#define IRPIN2 1
#define IRPIN3 3
#define IRPIN4 4

#elif defined PC
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#endif


#ifdef ARDUINO
/*
 * ARDUINO
 * filter the direction according to the collision logic
 * return the direction to go
 */
int direction_filter(void)
{
    int speed = get_speed();
    int dir = get_dir();

    /* get the distance */
    int ir1 = ir_distance(IRPIN1);
    int ir2 = ir_distance(IRPIN2);
    int ir3 = ir_distance(IRPIN3);
    int ir4 = ir_distance(IRPIN4);

    /* SPEED -> DANGERZONE */
    int dangerzone;
    dangerzone = speed_filter(speed);
    if (PRINTABLE) {
		Serial.println("================================");
		Serial.print("Quadrocopter travels at speed ");
		Serial.print(speed);
		Serial.println();
		Serial.print("Dangerous zone is ");
		Serial.print(dangerzone);
		Serial.println();
    }

    /* DANGERZONE+IR DISTANCE-> BOOLEANS */
    unsigned char *irBooleans;
    irBooleans = distance_filter(dangerzone, ir1, ir2, ir3, ir4);
    if (PRINTABLE) {
		Serial.println("================================");
		Serial.println("Result for which ir is triggered:");
		outputIR(irBooleans);
		Serial.println();
    }

    /* BOOLEANS -> DIRECTION RESULTS */
    unsigned char *result;
    result = ir_filter(irBooleans);
    free(irBooleans);
    if (PRINTABLE) {
		Serial.println("================================");
		Serial.println("after filter the according to the ir BOOLEANS");
		print_result(result);
    }

    /* CURRENT DIRECTION -> DIRECTION RESULTS */
    result = currentDirection_filter(dir, result);
    if (PRINTABLE) {
		Serial.println("================================");
		Serial.println("Quadrocopter heading towards ");
		outputdirection(dir);
		Serial.println();

		Serial.println("================================");
		Serial.println("after filter according to the heading directions");
		print_result(result);
    }

    /* DISTANCE DIFFERENCE-> TOWARDS WHICH IR  */
    int *distance_diff = (int *) calloc(4, sizeof(int));
    *distance_diff = ir_distance(IRPIN1) - ir1;
    *(distance_diff + 1) = ir_distance(IRPIN2) - ir2;
    *(distance_diff + 2) = ir_distance(IRPIN3) - ir3;
    *(distance_diff + 3) = ir_distance(IRPIN4) - ir4;

    unsigned char *moving_close = moving_closer(distance_diff);
    free(distance_diff);
    if (PRINTABLE) {
		Serial.println("================================");
		Serial.println("Result for which direction is moving closer");
		outputIR(moving_close);
		Serial.println();
    }

    /* TOWARDS WHICH IR -> DIRECTION RESULT */
    result = moving_closer_filter(moving_close, result);
    free(moving_close);
    if (PRINTABLE) {
		Serial.println("================================");
		Serial.println("after filter according to the moving object\n");
		print_result(result);

		Serial.println("=============FINAL=============");
		print_result(result);
    }

    /* RESULT -> PICK ONE DIRECTION */
    int finalDir = final_direction(dir, result);
    free(result);
    if (PRINTABLE) {
		Serial.println("================================");
		Serial.println("IF I HAVE TO PICK A DIRECTION, I CHOOSE: ");
		outputdirection(finalDir);
    }
	
	/* if the final direction is same as the current direction, return an invalid value */
	if(dir==finalDir){
		finalDir=5;
	}

    return finalDir;
}


#elif defined PC

/*
 * PC
 * filter the direction according to the collision logic
 * return the direction to go
 */
int direction_filter(int ir1, int ir2, int ir3, int ir4)
{
    int speed = get_speed();
    int dir = get_dir();

    /* SPEED -> DANGERZONE */
    int dangerzone;
    dangerzone = speed_filter(speed);
    if (PRINTABLE) {
		printf("\n================================\n");
		printf("Quadrocopter travels at speed %d\n", speed);
		printf("dangerous zone is %d\n", dangerzone);

    }

    /* DANGERZONE+IR DISTANCE-> BOOLEANS */
    unsigned char *irBooleans;
    irBooleans = distance_filter(dangerzone, ir1, ir2, ir3, ir4);
    if (PRINTABLE) {
		printf("\n================================\n");
		printf("Result for which ir is triggered: \n");
		outputIR(irBooleans);
    }

    /* BOOLEANS -> DIRECTION RESULTS */
    unsigned char *result;
    result = ir_filter(irBooleans);
    free(irBooleans);
    if (PRINTABLE) {
		printf("\n================================\n");
		printf("after filter the according to the ir BOOLEANS\n\n");
		print_result(result);
    }

    /* CURRENT DIRECTION -> DIRECTION RESULTS */
    result = currentDirection_filter(dir, result);
    if (PRINTABLE) {
		printf("\n================================\n");
		printf("Quadrocopter heading towards ");
		outputdirection(dir);

		printf("\n================================\n");
		printf("after filter according to the heading directions\n\n");
		print_result(result);
    }

    /* DISTANCE DIFFERENCE-> TOWARDS WHICH IR  */
    int *distance_diff = calloc(4, sizeof(int));
    *distance_diff = 100 - ir1;
    *(distance_diff + 1) = 100 - ir2;
    *(distance_diff + 2) = 100 - ir3;
    *(distance_diff + 3) = 100 - ir4;

    unsigned char *moving_close = moving_closer(distance_diff);
    free(distance_diff);
    if (PRINTABLE) {
		printf("\n================================\n");
		printf("Result for which direction is moving closer \n");
		outputIR(moving_close);
    }

    /* TOWARDS WHICH IR -> DIRECTION RESULT */
    result = moving_closer_filter(moving_close, result);
    free(moving_close);
    if (PRINTABLE) {
		printf("\n================================\n");
		printf("after filter according to the moving object\n");
		print_result(result);

		printf("\n================================\n");
		printf("\nFINAL\n\n");
		print_result(result);
    }

    /* RESULT -> PICK ONE DIRECTION */
    int finalDir = final_direction(dir, result);
    free(result);
    if (PRINTABLE) {
		printf("\n================================\n");
		printf("\nIF I HAVE TO PICK A DIRECTION\nI CHOOSE ");
		outputdirection(finalDir);
		printf("\n================================\n");
    }

	/* if the final direction is same as the current direction, return an invalid value */
	if(dir==finalDir){
		finalDir=5;
	}

    return finalDir;
}

#endif
