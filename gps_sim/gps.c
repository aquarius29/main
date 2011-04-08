/*

	Author: Qiushi Wang, Ezeh Prince Anthony Anayo
	Date:   2011.3.30

*/


#include "gps.h"

void init(){

	printf("init GPS\n");

}


unsigned char read_gps(){

	char *buf = malloc(128);
	char *result;

	struct rmc *data;

	int i;
	
	i = 0;
	
	result = read_info(buf);
	
	if(memcmp(buf,"$GPRMC",6) == 0){
	
	data = rmc_parser(result);

	current.lat = data->lat;
	current.lon = data->lon;

	free(buf);
	free(data);

	return 1;

	}else{
	free(buf);
	}

	return 0;
}


/*
int main(void){
	init();

	while(1){
	read_gps();
	usleep(100000);
	}
	
	return 0;
}
*/
