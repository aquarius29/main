#ifndef GPS_NAV
#define GPS_NAV

#include <stdio.h>
#include "dijk.h"

#include "serial.h"
#include "parser.h"


int ON_OFF; 

struct point curr;	/* current position, this data will be modified by gps device reader */ 

void setup_gps(char *dev,int baud);

void gps_navigation(struct point Destination);

void get_startp(struct point *pt);

struct link* connect_nodes(struct dist *st1,struct dist *st2,struct dist *end1,struct dist *end2,struct point *pts,struct link *lk);

struct trac* outdoor_nav(struct point *pts,struct point destination);

struct trac* update_path(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

int give_angle(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

void move_a_step(struct point *currp,struct point nextp);

#endif
