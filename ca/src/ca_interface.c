/*****************************************************************************
 * Product: movementInterface.c
 * Version: 0.1
 * Created: April 7, 2011
 * History:
 *          
 *
 * Movement/CA Group
 *****************************************************************************/

#include "ca_header.h"
#include <stdlib.h>
#include <stdio.h>
#include "WProgram.h"

#ifdef ARDUINO
//************************************************************
// ARDUINO
// All collision preperation goes here.
//************************************************************
int collision_init(void)
{
  return 1;
}


//************************************************************
// ARDUINO
// Collision is started here
//************************************************************
int collision_run(void)
{
  init();

  /* //init the serial output */
  // serial_init();
  // fdevopen(serial_putchar, serial_getchar);

  int i=0;
  while(i<1000)
    {
      direction_filter();
      i++;
    }

  return 1;

}


#elif defined PC
//************************************************************
// PC
//  All movement preperation goes here.
//************************************************************
int collision_init(void)
{
  

  return 1;


}

//************************************************************
// PC
// Movement is started here
//************************************************************
int collision_run(void)
{

  int ir1=100;
  int ir2=100;
  int ir3=100;
  int ir4=100;
  int i=0;
  while (i<5){
    direction_filter(get_speed(),get_dir(),ir1, ir2, ir3, ir4);
    i++;
  }

  return 1;
}


#endif


/* int main(int argc, char *argv[]) */
/* { */
/*   collision_run(); */
/*   return 0; */
/* } */

