#ifndef GPS_NAV
#define GPS_NAV

<<<<<<< HEAD
=======
#define FLY = 1;
#define GROUND = 0;

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#include <stdio.h>
#include "nav_outdoor_dijkstra.h"
#include "nav_serial.h"
#include "nav_gps_parser.h"
<<<<<<< HEAD

#include "nav_corelogic.h"

//extern int ON_OFF;

=======
#include "nav_corelogic.h"

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

extern int GPSIO_ON_OFF;

extern int GPSNAV_ON_OFF; 

extern int sendMovement;

<<<<<<< HEAD

=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
extern GPSLocation currentOutdoorPosition;	/* current position, this data will be modified by gps device reader */ 

struct point curr;

<<<<<<< HEAD
int good_data;
=======
int32_t good_data;

int32_t liftoff;
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

void setup_gps(char *dev,int baud);

struct trac* calc_path(struct point *pts,struct point destination);

void gps_navigation(GPSLocation* Destination);

void get_startp(struct point *pt);

struct trac* update_path(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

struct link* connect_nodes(struct dist *st1,struct dist *st2,struct dist *end1,struct dist *end2,struct point *pts,struct link *lk);

<<<<<<< HEAD
int give_angle(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

int give_distance(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

void move_a_step(struct point *currp,struct point nextp);

int check_gps_output(char buf []);

int get_goodData();

GPSLocation** path_for_UI(struct trac* path,struct point* pts);

void set_MovementCommand_True(void);

void set_MovementCommand_False(void);

int get_MovementCommand(void);
=======
int32_t give_angle(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

int32_t give_distance(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

void move_a_step(struct point *currp,struct point nextp);

int32_t check_gps_output(char buf []);

int32_t get_goodData();

GPSLocation** path_for_UI(struct trac* path,struct point* pts,struct point destination);

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

#endif
