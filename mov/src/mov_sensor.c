/*!
 * @file:         mov_sensor.c
 * @brief:        Read SONAR sensor data
 * @author:       Alina Butko
 * @date:         2011-05-05
 * @version:      0.1
 * @history       
 * @detail:       
 */
 

#include <stdint.h>

#ifdef ARDUINO
#include <math.h>
#include "WProgram.h"
#include "mov_interface.h"

/* int main(int argc, char *argv[]) */
/* { */
/* 	init(); */
/* 	Serial.init(9600); */
/* 	while(1){ */
/* 		sonar_distance(5); */
/* 	} */
/*     return 0; */
/* } */



/* uint16_t sonar_distance(uint8_t sonarPin) */
/* { */
/* 	double duration; */
/* 	uint16_t cm; */
/* 	duration = pulseIn(sonarPin, HIGH); */
/* 	/\* The number 57.874 I got from the MaxSonar datasheet where we can see */
/* 	 * that the distance can be calculated using the scale factor of 147uS */
/* 	 * per inch but as soon as we want data in cm we need to divide 147 by */
/* 	 * 2.54 and we get distance in cm */
/* 	 *\/ */
/* 	cm = duration/57.874; */
/* 	//	Serial.println(cm); */
/* 	return cm; */
/* } */


/*
 * reference: 
 * http://arduino.cc/en/Tutorial/Ping?from=Tutorial.UltrasoundSensor
 */
uint16_t sonar_distance(uint8_t sonarPin){

  long duration;

  pinMode(sonarPin, OUTPUT);
  digitalWrite(sonarPin, LOW);
  delay(2);
  digitalWrite(sonarPin, HIGH);
  delay(5);
  digitalWrite(sonarPin, LOW);

  pinMode(sonarPin, INPUT);
  duration = pulseIn(sonarPin, HIGH);
  uint16_t distance= duration/29/2;

  return distance;

  }

#elif defined PC
uint16_t sonar_distance(uint8_t sonarPin)
{
	return 100;
}
#endif
