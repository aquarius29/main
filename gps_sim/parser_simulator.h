/*
	Author: Qiushi Wang
	Date:   2011.3.30
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rmc{

	double lat;
	double lon;

};


int take_element(char *buffer);

struct rmc* rmc_parser(char *buffer);
