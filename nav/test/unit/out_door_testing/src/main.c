#include<stdio.h>
#include"pn.h"
//#include"outdoor_structure.h"

int main(){
	
	struct point start;
	struct point dest ;
	
	start.lat= 5742.447;
	start.lon= 1156.219;
	dest.lat= 5742.2950;
	dest.lon= 1156.1050;
	
	printf("dist: %f \n", calc_dist(start,dest));		
	
	return 0;
}