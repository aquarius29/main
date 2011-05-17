/*!
 * @file:         ca_logic.c
 * @brief:
 * @author:       Yanling Jin
 * @date:         2011-04-26
 * @version:      0.1
 * @history       2011-03-30 Jin - create the file
 *                2011-03-31 Jin - fix the memory leak problem
 *                2011-04-26 Jin - add printouts for arduino and pc
 * @detail:
 */

#include "ca_interface.h"


#ifdef ARDUINO
#include "WProgram.h"
#define IRPIN1 0
#define IRPIN2 1
#define IRPIN3 3
#define IRPIN4 4

#elif defined PC
#include <stdio.h>
#include <stdlib.h>
#endif

#include <stdint.h> 

uint16_t const speed=100;  /*cm*/

#ifdef ARDUINO
/*
 * ARDUINO
 * filter the direction according to the collision logic
 * return the direction to go
 */
uint8_t direction_filter(void)
{
    uint8_t dir = get_dir();

    /* get the distance */
	uint16_t ir1 = ir_distance(IRPIN1);
    uint16_t ir2 = ir_distance(IRPIN2);
    uint16_t ir3 = ir_distance(IRPIN3);
    uint16_t ir4 = ir_distance(IRPIN4);

    /* SPEED -> DANGERZONE */
	uint16_t dangerzone;
    dangerzone = speed_filter(speed);
#ifdef DEBUG
	print_speed_dangerzone(speed,dangerzone);
#endif

    /* DANGERZONE + IR DISTANCE-> BOOLEANS */
    uint8_t *irBooleans;
    irBooleans = distance_filter(dangerzone, ir1, ir2, ir3, ir4);
#ifdef DEBUG
	print_dangerzone_ir(irBooleans);
#endif

    /* BOOLEANS -> DIRECTION RESULTS */
    uint8_t *result;
    result = ir_filter(irBooleans);
    free(irBooleans);
#ifdef DEBUG
	print_result_after_dangerzone(result);
#endif

    /* CURRENT DIRECTION -> DIRECTION RESULTS */
    result = currentDirection_filter(dir, result);
#ifdef DEBUG
	print_result_after_flying_dir(dir,result);
#endif

    /* DISTANCE DIFFERENCE-> TOWARDS WHICH IR  */
	int16_t *distance_diff = distance_differ(ir1,ir2,ir3,ir4,
											ir_distance(IRPIN1), ir_distance(IRPIN2),
											ir_distance(IRPIN3),ir_distance(IRPIN4));

	uint8_t *moving_close = moving_closer(distance_diff);
    free(distance_diff);
#ifdef DEBUG
	print_movingCloser_ir(moving_close);
#endif

    /* TOWARDS WHICH IR -> DIRECTION RESULT */
    result = moving_closer_filter(moving_close, result);
    free(moving_close);
#ifdef DEBUG
	print_result_after_movingCloser(result);
	print_final_result(result);
#endif

    /* RESULT -> PICK ONE DIRECTION */
	uint8_t finalDir = final_direction(dir, result);
    free(result);

	/* 
	 *if the final direction is same as the current direction, 
	 *return an invalid value 
	 */
	if(dir==finalDir){
		finalDir=5;
	}

#ifdef DEBUG
	print_final_direction(finalDir);
#endif

    return finalDir;
}


#elif defined PC

/*
 * PC
 * filter the direction according to the collision logic
 * return the direction to go
 */

uint8_t direction_filter(uint16_t ir1, uint16_t ir2, uint16_t ir3,uint16_t ir4,
						 uint16_t ir11, uint16_t ir22, uint16_t ir33,uint16_t ir44) {

	uint8_t dir = get_dir();

    /* SPEED -> DANGERZONE */
    uint16_t dangerzone;
    dangerzone = speed_filter(speed);
#ifdef DEBUG
	print_speed_dangerzone(speed, dangerzone);
#endif

    /* DANGERZONE+IR DISTANCE-> BOOLEANS */
	uint8_t *irBooleans;
    irBooleans = distance_filter(dangerzone, ir1, ir2, ir3, ir4);
#ifdef DEBUG
	print_dangerzone_ir(irBooleans);
#endif


    /* BOOLEANS -> DIRECTION RESULTS */
    uint8_t *result;
    result = ir_filter(irBooleans);
    free(irBooleans);
#ifdef DEBUG
	print_result_after_dangerzone(result);
#endif


	/* CURRENT DIRECTION -> DIRECTION RESULTS */
	result = currentDirection_filter(dir, result);
#ifdef DEBUG
	print_result_after_flying_dir(dir, result);
#endif

	/* DISTANCE DIFFERENCE-> TOWARDS WHICH IR  */
	int16_t *distance_diff = distance_differ(ir1,ir2,ir3,ir4,
											ir11, ir22, ir33,ir44);
	unsigned char *moving_close = moving_closer(distance_diff);
	free(distance_diff);
#ifdef DEBUG
	print_movingCloser_ir(moving_close);
#endif

    /* TOWARDS WHICH IR -> DIRECTION RESULT */
    result = moving_closer_filter(moving_close, result);
    free(moving_close);
#ifdef DEBUG
	print_result_after_movingCloser(result);
	print_final_result(result);
#endif

    /* RESULT -> PICK ONE DIRECTION */
    uint8_t finalDir = final_direction(dir, result);
    free(result);

	/* 
	 *if the final direction is same as the current direction, 
	 *return an invalid value 
	 */
	if(dir==finalDir){
		finalDir=5;
	}
#ifdef DEBUG
	print_final_direction(finalDir);
#endif

    return finalDir;
}

#endif
