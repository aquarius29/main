/*!
 * @file:         mov_simulator.c
 * @brief:
 * @author:       Yanling Jin, Amber Olsson
 * @date:         2011-05-03
 * @version:      0.1
 * @history      
 *
 * @detail:
 */

#include <stdint.h>

#ifdef SIMULATOR

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mov_interface.h"

extern FILE *file;
extern struct nav *p;


/*
 * read commend of simulation line and parse it
 * return 1 as normal, 
 * return 0 as error, which shall indicate it's the end of the file
 */
uint8_t read_command(void){

    char line[60];
    if (fgets(line, sizeof(line) + 1, file) != NULL) {
#ifdef DEBUG
		printf("$$$$$$$$$$$$$$LINE: %s\n", line);
#endif
		uint8_t i;
		for (i = 1; i < 6; i++) {
			uint8_t start = get_loc(line, ':', i);
			uint8_t end = get_loc(line, ' ', i);
			uint8_t length = end - start;
			char *temp = (char *) malloc(length);
			strncpy(temp, line + start, length);
			assignValue(i, temp);
			free(temp);
		}	
		return 1;
    }
	else {
		return 0;
    }
}



/*
 * assign value to the navigation command
 */
void assignValue(uint8_t index, char *temp){

    switch (index) {
    case 1:
		p->type = atoi(temp);
		printf("Type is %d\n", p-> type); 
		break;
    case 2:
		p->order =atoi(temp);
		printf("Order is %d\n", p-> order);
		break;
    case 3:
		p->height = atoi(temp);
		printf("Height is %d\n", p-> height);
		break;
    case 4:
		p->distance = atoi(temp);
		printf("Distance is %d\n", p-> distance);
		break;
    case 5:
		p->yaw = atoi(temp);
		printf("Yaw is %d\n", p-> yaw);
		break;
    default:
		printf("Don't give me invalid value\n");
		break;
    }
}


/*
 * TYPE: 0 ORDER: 2 HEIGHT: 5 DISTANCE: 0 YAW: 0
 * get the location of ":" and " "
 */
uint8_t get_loc(char line[], char c, uint8_t indexOfChar){
    uint8_t i = 0;
    uint8_t count = 0;
    while (count != indexOfChar) {
		while (line[i] != c) {
			i++;
		}
		count++;
		i = i + 1;
    }
    return i;
}
#endif 



/*
 * (rand() % (max - min + 1) + min)
 * for simulating the sensor data
 * 
 * Only changing values if simulation is on
 */
int16_t do_sensor_simulation(int16_t currentSensorValue, uint8_t command){
#ifdef SIMULATOR
    int8_t i = (rand() % (6 - 0 + 1) + 0);  

    int new;

    switch (command) {
    case 1:
		new = currentSensorValue + i;
		break;
    case 2:
		new = currentSensorValue - i;
		break;
    }
    return new;
#else
    return currentSensorValue;
#endif
}
