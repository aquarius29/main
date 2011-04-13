#include <pthread.h>
#include <stdio.h>

void printTHIS();
void *loop( void *ptr );
void kill();

int main(int argc, char **argv) 
{
	int  iret1, iret2;
	char *message = "Manual Commands thread\n";
	char *message2 = "EXTRA THREAD\n";
	pthread_t thread1, thread2;
	
	iret1 = pthread_create(&thread1, NULL, loop, (void *) message);
	iret2 = pthread_create(&thread2, NULL, loop, (void *) message2);
	
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	
	printf("Value from iret1 is %d\n", iret1);
	printf("Value from iret2 is %d\n", iret2);
	
	return (1);
}

void *loop( void *ptr )
{
	char *message;
	message = (char *) ptr;
 	printf("%s \n", message);
	int alive = 0;
	
	// while (alive == 0)
	// {
	// 	printf("threaded %s\n", message);
	// 	printTHIS();
	// }
	 int i = 0;
	 
	 for(i = 0; i < 20; i++)
	 {
		printf("threaded %s is : %d\n", message, i);
	}
	kill();
//	pthread_exit(NULL);
}

void printTHIS()
{
	printf("Called a function here\n");
}

void kill()
{
	printf("KILL ME\n");
	pthread_exit(NULL);
}