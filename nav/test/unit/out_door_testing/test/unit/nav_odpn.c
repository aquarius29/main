#include <stdio.h>
#include "../../src/outdoor/nav_pn.h"

//Amanpreet kaur

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
	struct point start;
	struct point dest;
	start.lat=5742.47;
	start.lon=1158.170;
	dest.lat=5742.435;
	dest.lon=1158.181;
	printf("output = %f ",calc_dist(start,dest));
	CU_ASSERT_DOUBLE_EQUAL(calc_dist(start,dest),65.845345,4);
	
}
void testCase2(void){
	struct point start;
	struct point dest;
	start.lat=5742.447;
	start.lon=1156.219;
	dest.lat=5742.2950;
	dest.lon=1156.1050;
	printf("output = %f ",calc_k(start,dest));
	CU_ASSERT_DOUBLE_EQUAL(calc_k(start,dest),0.75000,5);
}
void testCase3(void){
	struct point start;
	struct point dest;
	start.lat=5742.447;
	start.lon=1156.219;
	dest.lat=5742.2950;
	dest.lon=1156.1050;
	printf("output = %f ",calc_c(start,dest));
	CU_ASSERT_DOUBLE_EQUAL(calc_c(start,dest),-31.3436,4);
}
void testCase4(void){
      printf("%f\n",in_degree(5742.477));
      CU_ASSERT_DOUBLE_EQUAL(in_degree(5642.477),57.70795,5);	
}

void testCase5(void){
      printf("%f\n",degree_minutes(57.70795));
      CU_ASSERT_DOUBLE_EQUAL(degree_minutes(57.70795),5742.477,3);	
}

void testCase6(void){
	struct point node;
	node.lat=5742.447;
	node.lon=1156.219;
	double k=0.75000;
	double c=-31.3436;
    CU_ASSERT_EQUAL(check_position(k,c,node),1);
	CU_ASSERT_EQUAL(check_position(k,c,node),0);
	CU_ASSERT_EQUAL(check_position(k,c,node),-1);	
     
}
void testCase7(void){
	struct point start;
	struct point dest;
	start.lat=5742.447;
	start.lon=1156.219;
	dest.lat=5742.2950;
	dest.lon=1156.1050;
	printf("output = %f ",calc_angle(start,dest));
	CU_ASSERT_DOUBLE_EQUAL(calc_angle(start,dest),216.869898,5);
}


