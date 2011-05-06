/*
 *@File: prioritize_node.c
 *
 *@Date: Apr 11, 2011
 *      
 *@Author: Jianfeng Xie
 *
 *@Description: Depending on geometric algorthem, the fucntion tries to find 2 the most suitable nodes near start or destination, then calculate the distance.
 *this source file should be compiled by command gcc pn.c -o pn -lm
 */

#include "pn.h"


/* calculate the distance between 2 nodes using latitude and longitude
 *
 *
 *@param two points 
 *@return double distance (meter)
 *
 */
double calc_dist(struct point start, struct point node){
    double dist;
    double dRadLatitude1 = start.lat*PI/180.0;
    double dRadLatitude2 = node.lat*PI/180.0;
    double dDisLatitude = dRadLatitude1 - dRadLatitude2;
    double dDisLongitude = start.lon*PI/180.0 - node.lon*PI/180.0;
    dist= 2 * asin(sqrt(pow(sin(dDisLatitude/2),2) + cos(dRadLatitude1)*cos(dRadLatitude2)*pow(sin(dDisLongitude/2),2)));
    dist *= EARTH_RADIUS*1000;
    return dist;
}


/* calculate slope of linear function
 *
 *@param two points: start and destination
 *@return double k;
 *
 */
double calc_k(struct point start, struct point dest){
    double k,c;	
    k= (start.lon - dest.lon)/(start.lat-dest.lat);
    return k;	
    }


/* calculate c of linear function
 *
 *@param two points: start and destination
 *@return double c;
 *
 */
double calc_c(struct point start,struct point dest){
    double k,c;
    k= (start.lon- dest.lon)/ (start.lat-dest.lat);	
    c=start.lon-k*start.lat;	
    return c;	
    }

/* check the node postion
 *
 *@param double slope,double c and point structre node
 *@return int number to show the node is up,down or on the line
 */



int check_position(double k, double c, struct point node){
    double position;
    position = node.lon - k*node.lat-c;
    if (position>0)        /*position>0, the node is up of line,return 1*/          
    return 1;
    if (position<0)
    return -1;             /*position<0, the node is down of line,return -1*/
    if (position == 0)
    return 0;	           /*position=0, the node is on the line, return 0*/
    }



/* prioritize the nodes near start and destination, in detail we can find 2 the most suitable points which are on the 2 sides of line connecting
 * start and destination
 *
 *@param two points: start and dest, list of nodes in map, and reuqest: up or down
 *@return one the most suitable point
 *
 *
 */
#define MAX_DIST 10000

struct dist* pnode(struct point start, struct point dest, struct point* node, char request){
    struct dist* p = malloc(sizeof(struct dist));
    int i=0;
    double dist,k,c;
    p->distance = MAX_DIST;
    p->name = 0;
	
    switch (request) {
        case 0 : 
        while(node[i].name != -1){	           /*down of the line*/
            k=calc_k(start,dest);
            c=calc_c(start,dest);	
            if(check_position(k,c,node[i])<0){
                dist=calc_dist(start,node[i]);
                if(i>0 && dist>p->distance){
                    i++;
                    continue;					
                } 
                p->distance = dist;
                p->name = node[i].name;	
                i++;
            }
            else{			
                i++;		
            }
        }		
	break;	
	
	case 1 :
        while(node[i].name != -1){	           /*up of the line*/
            k=calc_k(start,dest);
            c=calc_c(start,dest);	
            if(check_position(k,c,node[i])>0){
                dist=calc_dist(start,node[i]);			
                if(i>0 && dist>p->distance){
                    i++;
                    continue;					
                } 
                p->distance = dist;
                p->name = node[i].name;		
                i++;
            }
            else{				
	        i++;			
	    }
        }		
	break;	
	}	
	return p;	
	}



/* in longitudinal */
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


/* longitudinal & minutes */
double degree_minutes(double input)
{
	double output = 0;
	int degree = 0;	

	degree = (int)input;

	output = (input - degree)*60 + degree*100;

	return output;
}


/* Calculate the direction between 2 points, the angle is in degree(0~360)
 *
 *
 */
double calc_angle(struct point start, struct point dest){
     double x,y,angle;
     x=dest.lon-start.lon;
     y=dest.lat-start.lat;
     if(x>=0 && y>0){
          angle = atan(x/y)*180/PI;   // 0 <=angle<90 
     }
     else if(x<0 && y>0){
          angle = 360+atan(x/y)*180/PI; // 270<angle<360
     }
     else if(x<=0 && y<0){
          angle = 180+atan(x/y)*180/PI; // 180 <=angle <270 
     }
     else if(x>0 && y<0){
          angle = 180+atan(x/y)*180/PI; // 90<angle<180 
     }
     else if(x>=0 && y==0){
          angle = 90;   //angle =90
     }
     else if(x<=0 && y==0){
          angle = 270; // angle =270
     }
     return angle;
}

