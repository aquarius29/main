#include <stdio.h>
#include "../../src/pn.h"


//OutdoorPtr outdoor  = NULL;

/* Set up and clean up test suite */

int init_suite(void) {
	return 0;
  
}

int clean_suite(void) {
 return 0;
}

void testCase1(void){
	//CU_ASSERT(calc_dist((struct start),(2,5742.2950,1156.1050))==303.806324);
	printf("testing\n");
	struct point start;
	struct point dest;
	start.lat=5742.47;
	start.lon=1158.170;
	dest.lat=5742.435;
	dest.lon=1158.181;
	printf("%f/n",calc_dist(start,dest));
	CU_ASSERT(65.845345==calc_dist(start,dest));
	
}
void testCase2(void){
	struct point start;
	struct point dest;
	start.lat=5742.447;
	start.lon=1156.219;
	dest.lat=5742.2950;
	dest.lon=1156.1050;
	printf("%f\n",calc_k(start,dest));
	CU_ASSERT(0.750000==calc_k(start,dest));
}
void testCase3(void){
	struct point start;
	struct point dest;
	start.lat=5742.447;
	start.lon=1156.219;
	dest.lat=5742.2950;
	dest.lon=1156.1050;
	CU_ASSERT(1.3==calc_c(start,dest));
}
/*void testCase4(void){
	double position; 
	struct point node;
	node.lat=5742.447;
	node.lon=1156.219;
	CU_ASSERT(
	
	
}*/
void testCase4(void){
	printf("%f\n",in_degree(5742.477));
 CU_ASSERT(0==in_degree(0));	
}

void testCase5(void){
	printf("%f\n",degree_minutes(5742.477));
	CU_ASSERT(0==degree_minutes(0));	
}