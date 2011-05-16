#ifndef GPS_NAV
#define GPS_NAV

#define FLY = 1;
#define GROUND = 0;

#include <stdio.h>
#include "nav_outdoor_dijkstra.h"
#include "nav_serial.h"
#include "nav_gps_parser.h"
#include "nav_corelogic.h"


extern int GPSIO_ON_OFF;

extern int GPSNAV_ON_OFF; 

extern int sendMovement;

extern GPSLocation currentOutdoorPosition;	/* current position, this data will be modified by gps device reader */ 

struct point curr;

int32_t good_data;

int32_t liftoff;

void setup_gps(char *dev,int baud);

struct trac* calc_path(struct point *pts,struct point destination);

void gps_navigation(GPSLocation* Destination);

void get_startp(struct point *pt);

struct trac* update_path(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

struct link* connect_nodes(struct dist *st1,struct dist *st2,struct dist *end1,struct dist *end2,struct point *pts,struct link *lk);

int32_t give_angle(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

int32_t give_distance(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

void move_a_step(struct point *currp,struct point nextp);

int32_t check_gps_output(char buf []);

int32_t get_goodData();

GPSLocation** path_for_UI(struct trac* path,struct point* pts,struct point destination);


#endif
