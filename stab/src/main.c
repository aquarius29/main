/******************************************************************************
  File: main.c
  Description: Main file for all the code, used to select if arduino or pc mode 
  is selected
  Authors: Adam Debbiche 	       
  Created: 08/04/2011
  Log: 
     08/04/2011: Initial version // Adam
     13/04/2011: Added ifdefs for arduino and pc modes //Adam
     14/04/2011: Added comments to functions //Adam
*******************************************************************************/
/*
  Different header files are included depending on the mode 
  (arduino or pc)
*/
#ifdef PC
  #include "stab.h"
  #include <stdio.h>
#elif defined ARDUINO
  #include "stab.h"
  #include <Wire.h>
  #include <WProgram.h>
#endif 


/*
  If the code for the pc is being compiled then 
  the simulator is run. Otherwise, the arduino code is run 
*/
int main(void)
{  
#ifdef PC
  stab_init();
  stab_run();
#elif defined ARDUINO
  init();
  Serial.begin(9600);
  Wire.begin();
  init_gyro_hardware();
  while (1)
    {
      read_gyro_data();
      delay(50); 
    }
#endif 
  
  return 0;
}
