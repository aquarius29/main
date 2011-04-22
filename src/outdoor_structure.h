/*

	outdoor_structure.h: define some data structure for outdoor nav system.
	Author: Qiushi Wang
	Date: April 15th,2011

*/

#ifndef OUTDOOR_STRUCTURE
#define OUTDOOR_STRUCTURE

struct point
{
	char name;
	double lat;
	double lon;
};

struct link
{
	char from;
	char to;
	double distance;
	struct link *last;
};

struct trac
{
	char p;
	struct trac *last;
};


struct dist
{
	char name;
	double distance;
};

#endif
