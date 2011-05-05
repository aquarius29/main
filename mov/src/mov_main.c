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

/*
 * 
 */
int main(int argc, char *argv[]){

    /* start anything that needs to be started ahead of time */
    mov_init(); 
	/*Movement Loop*/
	int loop = 0;
	while(loop == 0)  {
		loop = mov_run();
	}
    return 1;
}
