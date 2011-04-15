#include <stdio.h>
#include "dijk.h"



struct point curr;	/* current position, this data will be modified by gps device reader */


unsigned char setup_gps()
{
	/*int fd = dev_init(char* dev,int baud) 

	if(fd == ?)
	return 0;
	

	get coordinate of current position

	*/
	return 1;
}


unsigned char outdoor_nav()
{
	struct point *pts = init_map();
	struct link *lk = NULL;
	struct dist *st_1, *st_2, *end_1, *end_2;	/* extra link	*/

	struct point startp;
	startp.name = -1;
	startp.lat= 5742.338;
	startp.lon= 1156.241;

	struct point endp;
	endp.name = -2;
	endp.lat= 5742.379;
	endp.lon= 1156.081;

	st_1 = prioritize_node(startp,endp,pts,0);
	printf("######start_down:%d \n",st_1->name);	
	
	st_2 = prioritize_node(startp,endp,pts,1);
	printf("######start_up:%d \n",st_2->name);
	
	end_1 = prioritize_node(endp,startp,pts,0);
	printf("######end_down:%d \n",end_1->name);	
	
	end_2 = prioritize_node(endp,startp,pts,1);
	printf("######end_up:%d \n",end_2->name);


	if(st_1->name == 0 && end_1->name == 0)
	{
		printf("go there straight\n");
	}
	else if(st_2->name == 0 && end_2->name == 0)
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

	struct trac *path = calculate(startp.name,endp.name,lk);
	struct trac *head = NULL;

	head = path;	

	while(head != NULL){
		
		printf("%d + ",head->p);

		int element = head->p;
		struct point m;
		switch(element) {
		
		case -1: printf("start>>>>latitude: %f, longitude: %f \n ", startp.lat,startp.lon);
			break;		
		case -2: printf("end>>>>latitude: %f, longitude: %f \n", endp.lat,endp.lon);
			break;
		default: m = pts [element-1];
			printf("latitude: %f, longitude: %f \n",m.lat,m.lon);
			break;
		}	
		head = head->last;
	}







/*---------------------- deallocate memory ------------------------------*/

	free(st_1);
	free(st_2);
	free(end_1);
	free(end_2);
	
	deallocate_link(lk);

	deallocate_trac(path);
	free(pts);


	/*	angle	*/

return 0;
}




int main(void)
{
	outdoor_nav();

return 0;
}
