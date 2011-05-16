<<<<<<< HEAD
/**************************************************************************
* @file main.c
* @brief Main file for all the code, used only by the stab group
* @author Adam Debbiche
* @date 08/04/2011
* @history
* 08/04/2011: Initial version // Adam
* 13/04/2011: Added ifdefs for arduino and pc modes //Adam
* 14/04/2011: Added comments to functions //Adam
* 15/04/2011: Merged gyro and accel code so both can be read
* simultaneously //Adam
* 18/04/2011: Updated code to reflect coding standards //Adam
**************************************************************************/

/*
* Different header files are included depending on the mode
*(arduino or pc)
*/
#include <stdio.h>
#include "stab.h"
#include "stab_interface.h"

/*
* If the code for the pc is being compiled then
* the simulator is run. Otherwise, the arduino code is run
*/
int main(void)
{
  stab_init();
  stab_run();
  return 0;
=======
#include "stab.h"
#include <stdio.h>



int main(void)
{
  
  stab_init();
  stab_run();  
  return 0;
  
 
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
}
