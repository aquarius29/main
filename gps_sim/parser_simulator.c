/*

	Author: Qiushi Wang
	Date:   2011.3.30

*/



#include "parser_simulator.h"


int take_element(char *buffer){

	int i = 0;

	while(buffer [i] != ','){
	i++;
	}	

	return i;

}





struct rmc* rmc_parser(char *buffer){
 
	char *lat = strchr(strchr(strchr(buffer,44)+1,44)+1,44)+1;

	char *NS = strchr(strchr(strchr(strchr(buffer,44)+1,44)+1,44)+1,44)+1;
	
	char *lon = strchr(strchr(strchr(strchr(strchr(buffer,44)+1,44)+1,44)+1,44)+1,44)+1;

	char *EW = strchr(strchr(strchr(strchr(strchr(strchr(buffer,44)+1,44)+1,44)+1,44)+1,44)+1,44)+1;
	
	char *lat1 = malloc(10),*lon1 = malloc(10);
	
	memcpy(lat1,lat,take_element(lat));
	
	memcpy(lon1,lon,take_element(lon));
	
	struct rmc *curr = malloc(sizeof(struct rmc));

	curr->lat = atof(lat1);
	curr->lon = atof(lon1);

	return curr;	
}


/*
int main(){

	char *buffer = malloc(128);

	strcpy(buffer,"$GPRMC,053740.000,A,2503.6319,N,12136.0099,E,2.69,79.65,100106,,,A*53");
	
	printf("%d\n",take_element(buffer));

	rmc_parser(buffer);

	return 0;
}
*/
