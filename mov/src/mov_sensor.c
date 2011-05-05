/*
 * File:         mov_sensor.c
 * Brief:        Read SONAR sensor data
 * Author:       Alina Butko
 * Date:         2011-05-05
 * Version:      0.1
 * History       
 * Detail:       
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
	double duration, cm;
	duration = pulseIn(sonarPin, HIGH);
	cm = duration/57.874;
	Serial.print(cm);
	Serial.print("cm");
	Serial.println();
/*	long duration;

	pinMode(sonarPin, OUTPUT);
	digitalWrite(sonarPin, LOW);
	delay(2);
	digitalWrite(sonarPin, HIGH);
	delay(5);
	digitalWrite(sonarPin, LOW);

	pinMode(sonarPin, INPUT);
	duration = pulseIn(sonarPin, HIGH);
	float distance= duration/29/2;

	return distance;*/
}
#endif
