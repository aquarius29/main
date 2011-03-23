/*
 ============================================================================
 Name        : angle.c
 Author      : Jianfeng, Eric
 Version     :1.0
 Description : radians to degree conversion based on two points
 ============================================================================
 */
#include "path_data_structure.h";
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double calc(position a, position b) {
	double angle = atan((b.lon - a.lon)/(b.lat - a.lat)) * (180/ M_PI) + 180;
	printf("%f\n", angle);
	return angle;
}
