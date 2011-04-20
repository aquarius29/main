/*
	gps_nav.c: integrate the gps-outdoor-navigation system. Give interface to CoreLogic of Navigation.

	Author: Qiushi Wang

	Date: April 16th, 2011
*/
#include "gps_nav.h"

 int main(void)
 {
 	setup_gps();	/* new thread */		
 
 
 
 	struct point destination; /*get the destination from UI*/
 	
 	struct point *pts = init_map(); /*init the map*/
 
 	struct trac *path = outdoor_nav(pts,destination); /* calc the path */
 
 /*under developed
 
 	loop: get_direction(curr,destination,path,pts);
 
 */
 
 /*dealloc pts and path, kill gps navigation*/
 
 //	int angle = get_direction(curr,destination,path,pts);
 
 	free(pts);
 	deallocate_trac(path);
 
 return 0;
 }




void setup_gps()
{
	/*
		setup the GPS receiver, build Serial communication, keep updating the current position.
	*/

	curr.name = 0;
//	curr.lat = 5742.353;
//	curr.lon = 1156.275;

	curr.lat = 5742.386;	
	curr.lon = 1156.063;	

}




/*
         0: arrive the destination
	-1: waiting
     0-359: moveing there	
*/

int get_direction(struct point curr,struct point dest,struct trac *path,struct point *pts)
{
	struct trac *head;
	struct point next_Node;
	int angle = -1;	/* inavaliable */

	if(path->p == -1){
		head = path->last;
		free(path);
		path = head;
		int element = path->p;
		next_Node = pts [element - 1];	
	}
	else if(path->p = -2)
	{
		next_Node = dest;
	}
	else
	{
		int element = path->p;
		next_Node = pts [element - 1];	
	}	

//	angle = calc_angle(curr,next_Node);

	if(calc_dist(curr,next_Node) <= 10)
	{
		if(next_Node.name == -2)
			angle = 0;	
		else
		{
			head = path->last;
			free(path);
			path = head;
			angle = -1;		
		}
	}


	angle = 0;

	return angle;
}





void get_startp(struct point *pt)
{
	pt->name = -1;
	pt->lat = curr.lat;
	pt->lon = curr.lon;
}




struct link* connect_nodes(struct dist *st1,struct dist *st2,struct dist *end1,struct dist *end2,struct point *pts,struct link* lk)
{
	
//	struct link *lk = NULL;

	if(st1->name == end1->name && st1->name == 0)
	{
		printf("go there straight\n");
		lk = add_link(-1,-2,0,lk);			
	//	return lk;
		
	}
	else if(st2->name == end2->name && st2->name == 0)
	{
		printf("go there straight\n");
		lk = add_link(-1,-2,0,lk);
//		return lk;		
	}else{

	if(st1->name != 0)
	lk = add_link(-1,st1->name,st1->distance,lk);
	
	if(st2->name != 0)	
	lk = add_link(-1,st2->name,st1->distance,lk);

	if(end1->name != 0)
	lk = add_link(end1->name,-2,end1->distance,lk);
	
	if(end2->name != 0)	
	lk = add_link(end2->name,-2,end2->distance,lk);
	
	lk = init_link(lk,pts);
		
//	return lk;
}

	return lk;
}







struct trac* outdoor_nav(struct point *pts,struct point destination)
{

	struct link *lk = NULL;
	struct dist *st_1, *st_2, *end_1, *end_2;	/* extra link	*/

	struct trac *path;

	struct point startp;
	get_startp(&startp);

	struct point endp;
	endp.name = -2;
//	endp.lat= 5742.307;
//	endp.lon= 1156.002;

	endp.lat= 5742.313;
	endp.lon= 1156.022;


	st_1 = pnode(startp,endp,pts,0);
//		printf("st1 %d\n", st_1->name);	
	st_2 = pnode(startp,endp,pts,1);
//		printf("st2 %d\n", st_2->name);
	end_1 = pnode(endp,startp,pts,0);
//		printf("end1 %d\n", end_1->name);
	end_2 = pnode(endp,startp,pts,1);
//		printf("end2 %d\n", end_2->name);

	lk = connect_nodes(st_1,st_2,end_1,end_2,pts,lk);


/*
	if(st_1->name == end_1->name && st_1->name == 0)
	{
		printf("go there straight\n");
	}
	else if(st_2->name == end_2->name && st_2->name == 0)
	{
		printf("go there straight\n");	
	}
					
								
	if(st_1->name != 0)
	lk = add_link(-1,st_1->name,st_1->distance,lk);
	
	if(st_2->name != 0)	
	lk = add_link(-1,st_2->name,st_1->distance,lk);

	if(end_1->name != 0)
	lk = add_link(end_1->name,-2,end_1->distance,lk);
	
	if(end_2->name != 0)	
	lk = add_link(end_2->name,-2,end_2->distance,lk);
	
	lk = init_link(lk,pts);
*/


	if(lk->last == NULL)
	{
//		printf("single lk \n");

		struct trac *head;	

		path = malloc(sizeof(struct trac));
		path->p = -2;
		path->last = NULL;

		head = path;

		path = malloc(sizeof(struct trac));
		path->p = -1;
		path->last = head;
	}
	else{
	path = calculate(startp.name,endp.name,lk);
	}


	struct trac *head;

	head = path;	

	while(head != NULL){
		
		printf("%d + ",head->p);

		int element = head->p;
		struct point m;
		switch(element) {
		
		case -1: printf("start latitude:%f,longitude:%f\n", startp.lat,startp.lon);
			break;		
		case -2: printf("end latitude:%f, longitude: %f \n", endp.lat,endp.lon);
			break;
		default: m = pts [element-1];
			printf("latitude:%f,longitude:%f\n",m.lat,m.lon);
			break;
		}	
		head = head->last;
	}



/*---------------------- deallocate memory ------------------------------*/

	free(st_1);
	free(st_2);
	free(end_1);
	free(end_2);

	if(lk != NULL)
	deallocate_link(lk);

return path;
}

