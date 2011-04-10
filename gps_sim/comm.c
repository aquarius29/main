/*
  this file is to simulate the Map modules request current position 
 
	Author: Qiushi Wang, Ezeh Prince Anthony Anayo
	Date:   Apr 3, 2011
 
*/
#include "comm.h"


void get_()
{

	if(read_gps()!=1)
	return;

	printf("lat: %f",current.lat);
	printf("lon: %f\n",current.lon);

}


int main(void){

	init();

	while(1){
	get_();
	usleep(100000);
	}

return 0;
}

