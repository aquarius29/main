#ifndef PN
#define PN

#include <math.h>
#include <stdlib.h>

#define EARTH_RADIUS 6387.137
#define PI 3.1415926
#define MAX_DIST 10000

#define DEGREE_CONVERTER 0.6

#include "nav_outdoor_structure.h"

double calc_dist(struct point start, struct point node);

double calc_k(struct point start, struct point dest);

double calc_k(struct point start, struct point dest);

double calc_c(struct point start,struct point dest);

int32_t check_position(double k, double c, struct point node);

struct dist* pnode(struct point start, struct point dest, struct point* node, char request);

double in_degree(double input);

/*double degree_minutes(double input);*/

double calc_angle(struct point start, struct point dest);

#endif
