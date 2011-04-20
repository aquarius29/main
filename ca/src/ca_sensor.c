  /*****************************************************************************
  * Product: collision_sensor.c
  * Version: 0.1
  * Created: March 30 2011
  * History:
  *
  * Movement/CA Group
  *****************************************************************************/

#ifdef ARDUINO
#include "WProgram.h"
#include <stdio.h>
#include <math.h>
#include "ca_interface.h"


uint8_t ir_distance(int irpin)
{
  uint8_t value=analogRead(irpin);
  // printf ("value is %d \n",value);

  // value convert to volts
  // value from sensor * (5/1024)
  // if running 3.3.volts then change 5 to 3.3
  //convert to the distance according to the formula from luckylarry.co.uk
  
//  int distance = 65*pow(value*0.0048828125, -1.10);
  uint8_t distance = 65*pow(value*0.0048828125, -1.10);
  return distance; 
}


 float sonar_distance(int sonarPin) 
{
  /* long duration; */

  /* pinMode(sonarPin, OUTPUT); */
  /* digitalWrite(sonarPin, LOW); */
  /* _delay_ms(2); */
  /* digitalWrite(sonarPin, HIGH); */
  /* _delay_ms(5); */
  /* digitalWrite(sonarPin, LOW); */

  /* pinMode(sonarPin, INPUT); */
  /* duration = pulseIn(sonarPin, HIGH); */

  /* float distance= duration/29/2; */

  /* return distance; */
  return 1;
}
#endif
