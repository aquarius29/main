/*
  @file: outdoor_structure.h
 
  @brief: define some data structure for outdoor nav system.	

  @author: Qiushi Wang

  @date: 2011-4-15
*/

#ifndef OUTDOOR_STRUCTURE
#define OUTDOOR_STRUCTURE

/* define a node, contains 3 attributes: node name, latitude, longitude */
struct point
{
  char name;
  double lat;
  double lon;
};


/* 
   define the relationship of 2 nodes, from one to another, 
   distance between the 2 nodes. 
*/
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

/*

*/
struct dist
{
  char name;
  double distance;
};

#endif
