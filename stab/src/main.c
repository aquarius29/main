/**************************************************************************
 * File: main.c
 * Description: Main file for all the code, used to select if arduino or
 *  pc mode is selected
 * Authors: Adam Debbiche 	       
 * Created: 08/04/2011
 * Log: 
 *    08/04/2011: Initial version // Adam
 *   13/04/2011: Added ifdefs for arduino and pc modes //Adam
 *   14/04/2011: Added comments to functions //Adam
 *   15/04/2011: Merged gyro and accel code so both can be read 
 *               simultaneously //Adam
 *   18/04/2011: Updated code to reflect coding standards //Adam
 **************************************************************************/

/*
 * Different header files are included depending on the mode 
 *(arduino or pc)
 */
#ifdef STAB
  #include <stdio.h>
  #include "stab.h"
#elif defined ARDUINO_STAB
  #include "stab.h"
  #include <Wire.h>
  #include <WProgram.h>
#endif 


/*
 * If the code for the pc is being compiled then 
 * the simulator is run. Otherwise, the arduino code is run 
 */
int main(void)
{  
#ifdef STAB
  stab_init();
  stab_run();
#elif defined ARDUINO_STAB
  init();
  Serial.begin(9600);
  Wire.begin();
  init_gyro_hardware();
  while (1)
    {
      read_gyro_data();
      readAccel();
      delay(50); 
    }
#endif 
  
  return 0;
}

