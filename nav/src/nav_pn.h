#ifndef PN
#define PN

#include <math.h>
#include <stdlib.h>

#define EARTH_RADIUS 6387.137
#define PI 3.1415926
<<<<<<< HEAD

=======
#define MAX_DIST 10000

#define DEGREE_CONVERTER 0.6
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

#include "nav_outdoor_structure.h"

double calc_dist(struct point start, struct point node);

double calc_k(struct point start, struct point dest);

double calc_k(struct point start, struct point dest);

double calc_c(struct point start,struct point dest);

<<<<<<< HEAD
int check_position(double k, double c, struct point node);
=======
int32_t check_position(double k, double c, struct point node);
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

struct dist* pnode(struct point start, struct point dest, struct point* node, char request);

double in_degree(double input);

<<<<<<< HEAD
double degree_minutes(double input);
=======
/*double degree_minutes(double input);*/
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

double calc_angle(struct point start, struct point dest);

#endif
