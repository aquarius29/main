#include <stdio.h>
#include "../../src/outdoor/nav_outdoor_dijkstra.h"

// !!!:AmanpreetKaur:20110510 
//OutdoorPtr outdoor  = NULL;

/* Set up and clean up test suite */

int init_suite(void) {
	return 0;
  
}

int clean_suite(void) {
 return 0;
}

void testCase_oddijkstra1(void){
	struct point* p = init_map();

	CU_ASSERT_EQUAL(p[0].name,1);
	CU_ASSERT_EQUAL(p[0].lat,57.7068);
	CU_ASSERT_EQUAL(p[0].lon,11.9374);


CU_ASSERT_EQUAL(p[1].name,2);
CU_ASSERT_EQUAL(p[1].lat,57.7064);
CU_ASSERT_EQUAL(p[1].lon,11.9371);

	CU_ASSERT_EQUAL(p[2].name,3);
	CU_ASSERT_EQUAL(p[2].lat,57.70622);
	CU_ASSERT_EQUAL(p[2].lon,11.93784);
	
	CU_ASSERT_EQUAL(p[3].name,4);
	CU_ASSERT_EQUAL(p[3].lat,57.70581);
	CU_ASSERT_EQUAL(p[3].lon,11.93749);


	CU_ASSERT_EQUAL(p[4].name,5);
	CU_ASSERT_EQUAL(p[4].lat,57.70597);
	CU_ASSERT_EQUAL(p[4].lon,11.93672);

	CU_ASSERT_EQUAL(p[5].name,6);
	CU_ASSERT_EQUAL(p[5].lat,57.70619);
	CU_ASSERT_EQUAL(p[5].lon,11.93589);

	CU_ASSERT_EQUAL(p[6].name,7);
	CU_ASSERT_EQUAL(p[6].lat,57.70636);
	CU_ASSERT_EQUAL(p[6].lon,11.93526);

	CU_ASSERT_EQUAL(p[7].name,8);
	CU_ASSERT_EQUAL(p[7].lat,57.70622);
	CU_ASSERT_EQUAL(p[7].lon,11.93626);

	CU_ASSERT_EQUAL(p[8].name,9);
	CU_ASSERT_EQUAL(p[8].lat,57.70679);
	CU_ASSERT_EQUAL(p[8].lon,11.93568);

	CU_ASSERT_EQUAL(p[9].name,10);
	CU_ASSERT_EQUAL(p[9].lat,57.70707);
	CU_ASSERT_EQUAL(p[9].lon,11.93670);

	CU_ASSERT_EQUAL(p[10].name,11);
	CU_ASSERT_EQUAL(p[10].lat,57.70723);
	CU_ASSERT_EQUAL(p[10].lon,11.93612);

CU_ASSERT_EQUAL(p[11].name,12);
CU_ASSERT_EQUAL(p[11].lat,57.70545);
CU_ASSERT_EQUAL(p[11].lon,11.93424);

CU_ASSERT_EQUAL(p[12].name,13);
CU_ASSERT_EQUAL(p[12].lat,57.70502);
CU_ASSERT_EQUAL(p[12].lon,11.93583);

CU_ASSERT_EQUAL(p[13].name,-1);
CU_ASSERT_EQUAL(p[13].lat,0);
CU_ASSERT_EQUAL(p[13].lon,0);
}
/*void testCase2(void){
	struct link* list= init_link(struct link* link,struct point* p);
	struct point* p = init_map();
	CU_ASSERT_EQUAL(list.to,2)
	

}*/




void testCase_oddijkstra2(void){
	
	struct link *this;
	
	struct point *p = init_map();
	
	struct link *list = NULL;
	//struct link *list ;
     //this.list =(1,2,calc_dist(p [0],p [1]),list);		
	/*this.from=13;
	this.to=12;
	this.distance= calc_dist(p[12],p[11]);
	this.last=link;*/
	CU_ASSERT(list != NULL);
	CU_ASSERT(list == NULL);	
	CU_ASSERT(remove_from_list(this,list));
	
	

}

