#ifndef GPS_NAV
#define GPS_NAV

#include <stdio.h>
#include "dijk.h"

#include "serial.h"
#include "parser.h"

#include "nav_corelogic.h"

extern int ON_OFF; 

extern struct point curr;	/* current position, this data will be modified by gps device reader */ 

int good_data;

void setup_gps(char *dev,int baud);

struct trac* outdoor_nav(struct point *pts,struct point destination);

void gps_navigation(struct point Destination);

void get_startp(struct point *pt);

struct trac* update_path(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

struct link* connect_nodes(struct dist *st1,struct dist *st2,struct dist *end1,struct dist *end2,struct point *pts,struct link *lk);

int give_angle(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

void move_a_step(struct point *currp,struct point nextp);

int check_gps_output(char buf []);

int get_goodData();

#endif
