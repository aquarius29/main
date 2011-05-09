/*
 * file:         mov_main.c
 * brief:        Running the movement component
 * author:       Yanling Jin, Amber Olsson
 * date:         2011-05-03
 * version:      0.1
 * history       2011-04-17 create the file
 *
 * detail:      This file contains the main method for running the movement component,\n
 *              This file should not be included for integration
 */

#include "mov_interface.h"

/*
 * The main function, for running the movement module only
 */
int main(int argc, char *argv[]){

	mov_init();

	/*Movement Loop*/
	int loop = 0;
	while(loop == 0)  {
		loop = mov_run();
	}
    return 1;
}
