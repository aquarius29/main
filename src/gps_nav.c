/*

	gps_nav.c: integrate the gps-outdoor-navigation system. Give interface to CoreLogic of Navigation.

	@author: Qiushi Wang

	Date: May 1st, 2011

	to do:
		1. handle bad data in parser.c .
		3. fix init functions in serial.c 
		2. send movement command.
*/
#include "gps_nav.h"

/*
int main(void)
{
//	struct point Destination = {-2,in_degree(5742.307),in_degree(1156.002)};

	ON_OFF = 1;

	setup_gps(UNO1,57600);			

//	gps_navigation(Destination);

return 0;
}
*/


void setup_gps(char *dev,int baud)
{
//	setup the GPS receiver, build Serial communication, keep updating the current position.

	good_data = 0;

	curr.name = 0;
//	curr.lat = 57.7071;
//	curr.lon = 11.9377;
//	curr.lat = 5742.386;	
//	curr.lon = 1156.063;	

	curr.lat = 0;
	curr.lon = 0;


	int fd = 0;
	char buf [256];

	fd = dev_init(dev,baud);

	if(fd == -1)
	{
	printf("can not init device\n");
	return;
	}

	usleep(1000*1000);

	while(ON_OFF){

	    	serial_read(fd,buf,10);

		if (strncmp(buf, "$GPRMC",6) == 0)
		{

			if(check_gps_output(buf))
			{			
		    		printf("%s",buf);
				struct point *position = parser(buf);

				curr.name = 0;
				curr.lat = in_degree(position->lat);
				curr.lon = in_degree(position->lon);
				free(position);
		

				if(curr.lat != 0)
				{
					good_data = 1;
				}
	
				printf("lat: %f ",curr.lat);
				printf("lon: %f\n",curr.lon);
			}	
		}
	}
}




void gps_navigation(struct point Destination)
{
	struct point *pts = init_map(); 			

	struct trac *path = outdoor_nav(pts,Destination); 	

	struct trac *next_Node = path;

	int angle = 0; 

	while(ON_OFF){

	next_Node = update_path(curr,Destination,pts,next_Node);
/*	
	printf("new path: %d\n",next_Node->p);
	printf("new curr lat: %f, lon: %f\n",curr.lat,curr.lon);	
*/
	angle = give_angle(curr,Destination,pts,next_Node);

	printf("angle : %d\n",angle);

/*
	send movement command here.
*/
	sleep(1);
}
	free(pts);
	deallocate_trac(path);
}



/*
         0: arrive the destination
	-1: waiting
     0-359: moveing there	
*/
int give_angle(struct point currp,struct point dest,struct point *pts,struct trac *next_Node)
{
	struct point next_Point = {0,0,0};

	int angle = -1;
			
	if(next_Node->p == -2)
	{	
		next_Point = dest;

		angle = (int)calc_angle(currp,next_Point);

		if(calc_dist(currp,next_Point)<10)
		{
			angle = 0;
		}
	}
	else
	{
		next_Point = pts [next_Node->p - 1];
		angle = (int)calc_angle(currp,next_Point);			
	}	
	return angle;		
}




struct trac* update_path(struct point currp,struct point dest,struct point *pts,struct trac *next_Node)
{
	struct point next_Point = {0,0,0};

	if(next_Node->p == -1)
	{	
		return next_Node->last;
	}
	else if( next_Node->p == -2 )
	{
//		move_a_step(&currp,dest);

		return next_Node;
	}
	else
	{
		next_Point = pts [next_Node->p - 1];

		if(calc_dist(currp,next_Point) <= 10)
		{
			if(next_Point.name != -2)
			{
			return next_Node->last;		
			}
			else{
			return next_Node;}			
		}
		else
		{
//			move_a_step(&curr,next_Point);
			return next_Node;
		}

	}
}





void get_startp(struct point *pt)
{
	pt->name = -1;
	pt->lat = curr.lat;
	pt->lon = curr.lon;
}




struct link* connect_nodes(struct dist *st1,struct dist *st2,struct dist *end1,struct dist *end2,struct point *pts,struct link* lk)
{
	if(st1->name == end1->name && st1->name == 0)
	{
		printf("go there straight\n");
		lk = add_link(-1,-2,0,lk);			
	}
	else if(st2->name == end2->name && st2->name == 0)
	{
		printf("go there straight\n");
		lk = add_link(-1,-2,0,lk);
	}
	else
	{
	if(st1->name != 0)
	lk = add_link(-1,st1->name,st1->distance,lk);
	
	if(st2->name != 0)	
	lk = add_link(-1,st2->name,st1->distance,lk);

	if(end1->name != 0)
	lk = add_link(end1->name,-2,end1->distance,lk);
	
	if(end2->name != 0)	
	lk = add_link(end2->name,-2,end2->distance,lk);
	
	lk = init_link(lk,pts);
	}

	return lk;
}





struct trac *outdoor_nav(struct point *pts,struct point destination)
{
	struct link *lk = NULL;
	struct dist *st_1, *st_2, *end_1, *end_2;	/* extra link	*/

	struct trac *path;

	struct point startp;

	get_startp(&startp);

	struct point endp;
	endp.name = -2;
	endp.lat = destination.lat;
	endp.lon = destination.lon;

	st_1 = pnode(startp,endp,pts,0);
							//printf("st1 %d\n", st_1->name);	
	st_2 = pnode(startp,endp,pts,1);
							//printf("st2 %d\n", st_2->name);
	end_1 = pnode(endp,startp,pts,0);
							//printf("end1 %d\n", end_1->name);
	end_2 = pnode(endp,startp,pts,1);
							//printf("end2 %d\n", end_2->name);

	lk = connect_nodes(st_1,st_2,end_1,end_2,pts,lk);

	if(lk->last == NULL)	/*you can go there straight, no necessary to run dijkstra*/
	{
		struct trac *head;
	
		path = malloc(sizeof(struct trac));
		path->p = -2;
		path->last = NULL;

		head = path;

		path = malloc(sizeof(struct trac));
		path->p = -1;
		path->last = head;
	}
	else
	{
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

/*---- deallocate memory ----*/
	free(st_1);
	free(st_2);
	free(end_1);
	free(end_2);
	deallocate_link(lk);

return path;
}



/* check that the output of gps is available */
int check_gps_output(char buf [])
{
	int i = 0;
	int num = 0;

	while(buf [i] != 10)
	{
		if(buf [i] == 44)
		num++;
	i++;
	}	
	
	if( num == 12)
	return 1;
	else
	return 0;
}



int get_goodData()
{
	return good_data;
}

