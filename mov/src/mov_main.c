/*
 * file:         mov_main.c
 * brief:
 * author:       Yanling Jin, Amber Olsson
 * date:         2011-05-03
 * version:      0.1
 * history      
 *
 * detail:
 */

#include "mov_interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct nav *p = &navCommand;
FILE *file;

/*
 * 
 */
int main(int argc, char *argv[]){

    /* start anything that needs to be started ahead of time */
    mov_init(); 
    
    file = fopen("input.txt", "r");

    /*Movement Loop*/
	int loop = 0;
	while(loop == 0)  {
		loop = mov_run();
	}

    fclose(file);
    return 1;
}


/*
 * 
 */
int read_command(){

    char line[60];
    if (fgets(line, sizeof(line) + 1, file) != NULL) {
		printf("line is %s\n", line);
		int i;
		for (i = 1; i < 6; i++) {
			int start = get_loc(line, ':', i);
			int end = get_loc(line, ' ', i);
			int length = end - start;
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
 * 
 */
void assignValue(int index, char *temp){

    switch (index) {
    case 1:
		p->type = temp[0];
			/* printf("Type is %c\n", navCommand.type); */
		break;
    case 2:
		p->order = temp[0];
			/* printf("Order is %c\n", navCommand.order); */
		break;
    case 3:
		p->height = atoi(temp);
		/* printf("Height is %d\n", navCommand.height); */
		break;
    case 4:
		p->distance = atoi(temp);
		/* printf("Distance is %d\n", navCommand.distance); */
		break;
    case 5:
		p->yaw = atoi(temp);
		/* printf("Yaw is %d\n", navCommand.yaw); */
		break;
    default:
		/* printf("Don't give me invalid value\n"); */
		break;
    }
}


/*
 * TYPE: 0 ORDER: 2 HEIGHT: 5 DISTANCE: 0 YAW: 0
 */
int get_loc(char line[], char c, int indexOfChar){
    int i = 0;
    int count = 0;
    while (count != indexOfChar) {
		while (line[i] != c) {
			i++;
		}
		count++;
		i = i + 1;
    }
    return i;
}


  
