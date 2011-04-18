#include <stdio.h>
#include "dijk.h"

/*external struct point curr*/

struct point curr;	/* current position, this data will be modified by gps device reader.  should be defined */ 
				    /* at read_dev.c 									     */
void setup_gps();

void get_startp(struct point *pt);

struct link* connect_nodes(struct dist *st1,struct dist *st2,struct dist *end1,struct dist *end2,struct point *pts,struct link *lk);

struct trac* outdoor_nav(struct point *pts,struct point destination);

int get_direction(struct point curr,struct point dest,struct trac *path,struct point *pts);
