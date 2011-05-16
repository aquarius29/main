<<<<<<< HEAD
<<<<<<< HEAD
/*
 * file:         ca_sensor.c
 * brief:        Read IR sensor data
 * author:       Yanling Jin
 * date:         2011-04-26
 * version:      0.1
 * history       2011-03-30 - create the file\n
 * detail:       This is for calculating the collision avoidance
 */
 

#ifdef ARDUINO
#include <stdio.h>
#include <math.h>
#include "WProgram.h"
#include "ca_interface.h"


/*
 * require 5 volts, if running 3.3.volts then change 3.3/1024
 * convert to the distance according to the formula from luckylarry.co.uk
 */
int ir_distance(int irpin)
{
	int value=analogRead(irpin);
	int distance = 65*pow(value*0.0048828125, -1.10);
	return distance; 
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
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


int ir_distance(int irpin)
{
  int value=analogRead(irpin);
  // printf ("value is %d \n",value);

  // value convert to volts
  // value from sensor * (5/1024)
  // if running 3.3.volts then change 5 to 3.3
  //convert to the distance according to the formula from luckylarry.co.uk
  
//  int distance = 65*pow(value*0.0048828125, -1.10);
  int distance = 65*pow(value*0.0048828125, -1.10);
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
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}
#endif
