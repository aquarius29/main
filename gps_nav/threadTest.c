#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "gps_nav.h"


extern int ON_OFF;


void printTHIS();

void *Setup_gps( void *ptr );

void *Setup_nav( void *ptr );

void *Monitor(void *ptr);

void kill();


pthread_mutex_t mut;


int main(int argc, char **argv) 
{
	int  iret1, iret2, iret3;
	char *message = "GPS-thread\n";
	char *message2 = "NAV-thread\n";
	char *message3 = "MONITOR-thread\n";

	ON_OFF = 1;

	pthread_t thread1, thread2, thread3;
	
	iret1 = pthread_create(&thread1, NULL, Setup_gps, (void *) message);
	iret2 = pthread_create(&thread2, NULL, Setup_nav, (void *) message2);
	iret3 = pthread_create(&thread3, NULL, Monitor, (void *) message3);

	
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	pthread_join( thread3, NULL);

	ON_OFF = 0;
	
	printf("Value from iret1 is %d\n", iret1);
	printf("Value from iret2 is %d\n", iret2);
	printf("Value from iret3 is %d\n", iret3);
	
	return (1);
}


void *Setup_gps(void *ptr)
{
	char *message;
	message = (char *) ptr;
 	printf("%s \n", message);
	int alive = 0;

	setup_gps(UNO,57600);				

	kill();

}


void *Setup_nav(void *ptr)
{
	char *message;
	message = (char *) ptr;
 	printf("%s \n", message);
	int alive = 0;

	struct point Destination = {-2,5742.307,1156.002};

	gps_navigation(Destination);

	kill();
}



void *Monitor(void *ptr)
{
	char *message;
	message = (char *) ptr;
 	printf("%s \n", message);
	int alive = 0;

	sleep(5);
	

	pthread_mutex_lock(&mut);

	ON_OFF = 0;

	pthread_mutex_unlock(&mut);


	printf("stop the loops \n");	

	kill();
}




void kill()
{
	printf("KILL ME\n");
	pthread_exit(NULL);
}

