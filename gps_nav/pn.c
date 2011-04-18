/*
 * prioritize_node.c
 *
 *  Created on: Apr 11, 2011
 *      Author: Jianfeng Xie
 */

#include "pn.h"

double calc_dist(struct point start, struct point node){
	double dist;

	double dRadLatitude1 = in_degree(start.lat)*3.1415926/180.0;
	double dRadLatitude2 = in_degree(node.lat)*3.1415926/180.0;
	double dDisLatitude = dRadLatitude1 - dRadLatitude2;
	double dDisLongitude = in_degree(start.lon)*3.1415926/180.0 - in_degree(node.lon)*3.1415926/180.0;

	dist= 2 * asin(sqrt(pow(sin(dDisLatitude/2),2) + cos(dRadLatitude1)*cos(dRadLatitude2)*pow(sin(dDisLongitude/2),2)));

	dist *= 6378.137*1000;

	//dist = pow((start.lat-node.lat),2)+ pow((start.lon - node.lon),2);
	//dist = sqrt(dist);
//	printf("dist: %f \n",dist);
	return dist;
}



double calc_k(struct point start, struct point dest){
	double k,c;	
//	k= (start.lon - dest.lon)/ (start.lat-dest.lat);

	k= (in_degree(start.lon) - in_degree(dest.lon))/ (in_degree(start.lat)-in_degree(dest.lat));

	return k;	
	}



double calc_c(struct point start,struct point dest){
	double k,c;
	k= (in_degree(start.lon) - in_degree(dest.lon))/ (in_degree(start.lat)-in_degree(dest.lat));	
	c=in_degree(start.lon)-k*in_degree(start.lat);	
	return c;	
	}


//position>0, the node is up of line,return 1
//position<0, the node is down of line, return -1
//position=0, the node is on the line, return 0
int check_position(double k, double c, struct point node){
	double position;

//	position = node.lon - k*node.lat-c;
	position = in_degree(node.lon) - k*in_degree(node.lat)-c;

	if (position>0)
	return 1;
	if (position<0)
	return -1;
	if (position == 0)
	return 0;	
	}




struct dist* pnode(struct point start, struct point dest, struct point* node, char request){
	struct dist* p = malloc(sizeof(struct dist));
	int i=0;
	double dist,k,c;
	p->distance = 1000000;

	switch (request) 
	{
	case 0 : while(node[i].name != -1){	//down of the line
			k=calc_k(start,dest);
			c=calc_c(start,dest);	
			if(check_position(k,c,node[i])<0){
				dist=calc_dist(start,node[i]);
				//printf("name: %d \n", node[i].name);
				if(i>0 && dist>p->distance){
					i++;
					continue;					
				} 
			p->distance = dist;
			p->name = node[i].name;
		//	printf("name: %d \n",p->name);
			//printf("k: %f \n",k);
			//printf("c: %f \n",c);
		//	printf("dist: %f \n",p->distance);
		//	printf("position: %d \n\n",check_position(k,c,node[i]));		
			i++;
			}
			else{			
			i++;		
			}
		}		
	break;	

	case 1 : while(node[i].name != -1){	//up of the line
			k=calc_k(start,dest);
			c=calc_c(start,dest);	
			if(check_position(k,c,node[i])>0){
				dist=calc_dist(start,node[i]);
				//printf("name: %d \n",node[i].name);				
				if(i>0 && dist>p->distance){
					i++;
					continue;					
				} 
			p->distance = dist;
			p->name = node[i].name;
		//	printf("name: %d \n",p->name);
//			printf("k: %f \n",k);
//			printf("c: %f \n",c);
		//	printf("dist: %f \n",p->distance);
		//	printf("position: %d \n\n",check_position(k,c,node[i]));		

			i++;
			}
			else{				
			i++;			
			}
		}		
	break;	
	}	
//	if(p->name == 0)	
//	free(p);	

	return p;	
	}



double in_degree(double input)
{
	double output = 0;
	int degree = 0;

	input = input/100;

	degree = (int)input;

	output = (input - degree)/0.6;

	output += degree;

	return output;
}


/*
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

*/


/*
int main(){
	struct point start;
	struct point dest ;
	struct point* node = init_map();
	struct dist* p;
	struct dist* p1;
	struct dist* p2;
	struct dist* p3;
	
	start.lat= 5742.447;
	start.lon= 1156.219;
	dest.lat= 5742.2950;
	dest.lon= 1156.1050;
	
	p =prioritize_node(start,dest,node,0);
	printf("####start:best_right_node: %d \n", p->name);
	
	p1 =prioritize_node(start,dest,node,1);	
	printf("####start:best_left_node: %d \n", p1->name);	
	
	p2 =prioritize_node(dest,start,node,0);	
	printf("####dest:best_left_node: %d \n", p2->name);
	
	p3 =prioritize_node(dest,start,node,1);	
	printf("##dest:best_left_node: %d \n", p3->name);
	
	return 0;
}
*/

