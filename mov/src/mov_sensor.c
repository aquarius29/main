/*
 * file:         mov_sensor.c
 * brief:        Read SONAR sensor data
 * author:       
 * date:         2011-04-26
 * version:      0.1
 * history       
 * detail:       
 */
 

#ifdef ARDUINO
#include <stdio.h>
#include <math.h>
#include "WProgram.h"
#include "mov_interface.h"

/*
 * reference: 
 * http://arduino.cc/en/Tutorial/Ping?from=Tutorial.UltrasoundSensor
 */
float sonar_distance(int sonarPin)
{
	long duration;

	pinMode(sonarPin, OUTPUT);
	digitalWrite(sonarPin, LOW);
	delay(2);
	digitalWrite(sonarPin, HIGH);
	delay(5);
	digitalWrite(sonarPin, LOW);

	pinMode(sonarPin, INPUT);
	duration = pulseIn(sonarPin, HIGH);
	float distance= duration/29/2;

	return distance;
}
#endif
