/*
 * Parser.h
 *
 *  Created on: Mar 29, 2011
 *      Author: feng
 */
#ifndef PARSER
#define PARSER


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nav_outdoor_structure.h"

struct rmc{
	 char* id;
	 double utc_time;
	 double lat;
	 char  ns_indicator;
	 double lon;
	 char ew_indicator;
	 char status;
	 char mode;
	 double speed;
	 double course;
	 double date;
};



int test();  // test for GPRMC parser

double parse_decimal(char *str); // parse number

struct point* parser(char* buffer); // parser for GPRMC

struct rmc* split (); // grap different data from stream and store them in structure

#endif
