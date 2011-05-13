#include <stdio.h>
//#include "../src/nav_pn.h"
//#include "../src/nav_outdoor_dijkstra.h"
//Amanpreet kaur

#include "../src/nav_gps_nav.h"

//OutdoorPtr outdoor  = NULL;

/* Set up and clean up test suite */

int init_suite(void) {
	return 0;
  
}

int clean_suite(void) {
 return 0;
}

void test_od_pn1(void){
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
void test_od_pn2(void){
	struct point start;
	struct point dest;
	start.lat=5742.447;
	start.lon=1156.219;
	dest.lat=5742.2950;
	dest.lon=1156.1050;
	CU_ASSERT_DOUBLE_EQUAL(calc_k(start,dest),0.75000,5);
}
void test_od_pn3(void){
	struct point start;
	struct point dest;
	start.lat=5742.447;
	start.lon=1156.219;
	dest.lat=5742.2950;
	dest.lon=1156.1050;
	printf("output = %f ",calc_dist(start,dest));
	CU_ASSERT_DOUBLE_EQUAL(calc_c(start,dest),-31.3436,4);
}
void test_od_pn4(void){
	struct point node;
	node.lat=5742.447;
	node.lon=1156.219;
	double k=0.75000;
	double c=-31.3436;
    CU_ASSERT_EQUAL(check_position(k,c,node),1);
	CU_ASSERT_EQUAL(check_position(k,c,node),0);
	CU_ASSERT_EQUAL(check_position(k,c,node),-1);	
	
}
void test_od_pn6(void){
      CU_ASSERT_DOUBLE_EQUAL(in_degree(5642.477),57.70795,5);	
}

void test_od_pn7(void){
      CU_ASSERT_DOUBLE_EQUAL(degree_minutes(57.70795),5742.477,3);	
}


void test_od_pn8(void){
	struct point start;
	struct point dest;
	start.lat=5742.447;
	start.lon=1156.219;
	dest.lat=5742.2950;
	dest.lon=1156.1050;
	CU_ASSERT_DOUBLE_EQUAL(calc_angle(start,dest),216.869898,5);
}
void test_od_dijk1(void){
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

/* author: Qiushi Wang */
/* test init_link(struct link* link,struct point *pts) */
void test_od_dijk2(void)
{
	struct points* pts = init_map();	
	struct link* lk = NULL;
	lk = init_link(lk,pts);
	
	CU_ASSERT_EQUAL(lk->from,0);
	
	struct link* curr = lk->last;	/* the first one is 0 to 0, so take 2rd ond */
	
	while(curr!=NULL)
	{
		CU_ASSERT_NOT_EQUAL(curr->from,0);
		curr = curr->last;
	}
	
	free(pts);
	deallocate_link(lk);
}


/* author: Qiushi Wang */
/* remove_from_list(struct link* this,struct link* list) */
void test_od_dijk3(void)
{
	struct points* pts = init_map();	
	struct link* lk = NULL;
	lk = init_link(lk,pts);
	
	int32_t listSize1 = 0, listSize2 = 0;
	
	struct link* curr = lk;
	
	while(curr != NULL)
	{
		listSize1++;
		curr = curr->last;
	}
	
	
	struct link *element1 = lk->last->last;
	struct link *element2 = lk->last->last->last;
	
	remove_from_list(element1,lk);
	remove_from_list(element2,lk);
	
	
	curr = lk;
	while(curr != NULL)
	{
		listSize2++;
		curr = curr->last;
	}
	
	//	printf("s1 %d, s2 %d\n",listSize1,listSize2);
	
	CU_ASSERT_EQUAL(listSize1-2,listSize2);
	
	/* dealloc */
	free(pts);
	deallocate_link(lk);
}


/* 
 author: Qiushi Wang 
 test: struct link* move_to_wl(struct link* curr,struct link* lk,struct link* wl)
 */
void test_od_dijk4(void)
{
	struct points* pts = init_map();	
	struct link* lk = NULL;
	struct link* waiting_list = NULL;
	lk = init_link(lk,pts);
	
	struct link* elementX = lk->last->last; 	
	
	waiting_list = move_to_wl(elementX,lk,waiting_list);
	
	CU_ASSERT_EQUAL( waiting_list->from == elementX->from,waiting_list->to == elementX->to );
}


/*
 author: Qiushi Wang
 test: struct link* remove_from_wl(struct link* next,struct link* wl)
 */
void test_od_dijk5(void)
{
	struct points* pts = init_map();	
	struct link* lk = NULL;
	struct link* waiting_list = NULL;
	lk = init_link(lk,pts);
	
	struct link* element1 = lk->last->last; 
	struct link* element2 = lk->last;
	struct link* element3 = lk->last->last->last;
	
	waiting_list = move_to_wl(element1,lk,waiting_list);
	waiting_list = move_to_wl(element2,lk,waiting_list);
	waiting_list = move_to_wl(element3,lk,waiting_list);
	
	remove_from_wl(waiting_list->last,waiting_list);
	
	/*	printf("from : %d %d\n",waiting_list->from,waiting_list->to);
	 printf("from : %d %d\n",waiting_list->last->from,waiting_list->last->to);
	 printf("from : %d %d\n",waiting_list->last->last->from,waiting_list->last->last->to);
	 */
	CU_ASSERT_EQUAL(waiting_list->last->from,0);
	
	/* dealloc */
	free(pts);
	deallocate_link(lk);
	deallocate_link(waiting_list);
}


/*
 author: Qiushi Wang
 test: struct trac* get_path(struct link* collection,char startp,char endp)
 */
void test_od_dijk8(void)
{
	struct link *collection = NULL;
	struct trac *path = NULL,*curr = NULL;
	collection = add_link(12,11,0,collection);
	collection = add_link(9,8,0,collection);
	collection = add_link(11,7,0,collection);
	collection = add_link(2,3,0,collection);
	collection = add_link(7,5,0,collection);
	collection = add_link(2,4,0,collection);
	collection = add_link(5,6,0,collection);
	
	path = get_path(collection,-1,-2);
	curr = path;
	
	//printf("\n%d \n",curr->p);
	CU_ASSERT_EQUAL(curr->p,-1);
	curr = curr->last;
	//printf("%d \n",curr->p);
	CU_ASSERT_EQUAL(curr->p,11);
	curr = curr->last;
	//printf("%d \n",curr->p);
	CU_ASSERT_EQUAL(curr->p,7);
	curr = curr->last;
	//printf("%d \n",curr->p);
	CU_ASSERT_EQUAL(curr->p,5);
	curr = curr->last;
	//printf("%d \n",curr->p);
	CU_ASSERT_EQUAL(curr->p,-2);
	curr = curr->last;
	
	deallocate_link(collection);
	deallocate_trac(path);
}

