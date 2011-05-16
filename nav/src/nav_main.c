#include nav_corelogic.h

int main(int argc, char **argv) {


/*
 	GPSLocation *Destination = malloc(sizeof(GPSLocation));
 	Destination->latitude = 57.7053;
 	Destination->longitude = 11.9340;

	nav_runGpsSystem(Destination->latitude, Destination->longitude);
*/
	nav_init();
	nav_run();

	//runProtocolThread();
	
    // tile a, b;
    // a.x = 1;
    // a.y = 1;
    // b.x = 9;
    // b.y = 5;
    // 
    // nav_runIndoorSystem(a.x, a.y, b.x, b.y);
	
	
	

    return 0;
}
