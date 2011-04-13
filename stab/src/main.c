#ifdef PC
  #include "stab.h"
  #include <stdio.h>
#elif defined ARDUINO
  #include "stab.h"
  #include <Wire.h>
  #include <WProgram.h>
#endif 

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
