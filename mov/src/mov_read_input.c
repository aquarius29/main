/*****************************************************************************
  * Product: mov_read_input.c
  * Version: 0.1
  * Created: April 18, 2011
  * History:
  * Author: Sepideh Fazlmashhadi,Alina Butko, Dong Yu         
  * Description: Responsible for reading data from standart input. The data
  * mentioned is desired data
  *
  * Movement/CA Group
  *****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mov_header.h"


//main method
int read_input (FILE *in) {
	FILE *output;
	char line[50];
	char *label;
	char *name;

	struct data *d = (struct data*) malloc(sizeof(struct data));
	while(fgets(line, sizeof(line), in) != NULL ) {
		label = strtok(line, ": ");
		name = strtok(NULL, "\n");
	
		if((strcmp(label, "TYPE")) == 0){
			d->type = (char *)malloc(20);
			strcpy(d->type, name);
			printf("\n%s: %s\n", label, d->type);
		}
		else if((strcmp(label, "ORDER")) == 0){
			d->order = (char *)malloc(20);
			strcpy(d->order, name);
			printf("%s: %s\n", label, d->order);
		}
		else if((strcmp(label, "HEIGHT")) == 0){
				d->height = atoi(name);
				printf("%s: %d\n", label, d->height);
		}
		else if((strcmp(label, "DISTANCE")) == 0){
				d->distance = atoi(name);
				printf("%s: %d\n", label, d->distance);
		}
		else if((strcmp(label, "YAW")) == 0){
				d->yaw = atoi(name);
				printf("%s: %d\n", label, d->yaw);
		}
		else if((strcmp(label, "PITCH")) == 0){
				d->pitch = atoi(name);
				printf("%s: %d\n", label, d->pitch);
		}
		else if((strcmp(label, "ROLL")) == 0){
				d->roll = atoi(name);
				printf("%s: %d\n", label, d->roll);
		}
		else if((strcmp(label, "SPEED")) == 0){
				d->speed = atoi(name);
				printf("%s: %d\n", label, d->speed);
		}
	}
	free((void *)d);
	return 0;
}
