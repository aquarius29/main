#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define NUM_THREADS     1

int init(){return 1;}

void *TaskCode(void *argument)
{
  int tid;
 
  tid = *((int *) argument);
  while (1){
    printf("Hello World! It's me, thread %d!\n", tid);
    usleep(1000*800);
}
 
  /* optionally: insert more useful stuff here */
 
  return NULL;
}
 
int run()
{
  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];
  int rc, i;
 
  /* create all threads */
  for (i=0; i<NUM_THREADS; ++i) {
    thread_args[i] = i;
    printf("In main: creating thread %d\n", i);
    rc = pthread_create(&threads[i], NULL, TaskCode, (void *) &thread_args[i]);
    assert(0 == rc);
  }
 
  /* wait for all threads to complete */
  for (i=0; i<NUM_THREADS; ++i) {
    rc = pthread_join(threads[i], NULL);
    assert(0 == rc);
  }
 
  //exit(EXIT_SUCCESS);
  return 1;
}
