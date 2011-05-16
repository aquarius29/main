<<<<<<< HEAD
/*
 * file:         ca_main.c
 * brief:        main file for collsion avoidance
 * author:       Yanling Jin
 * date:         2011-04-26
 * version:      0.1
 * history       2011-03-30 create the file

 * detail:       for test only 
 */

#include <stdlib.h>
#include <stdio.h>
#include "ca_interface.h"

int main(int argc, char *argv[])
{
	ca_init();
	ca_run();
	return 0;
=======
#include "ca_interface.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  ca_run();
  return 0;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
}
