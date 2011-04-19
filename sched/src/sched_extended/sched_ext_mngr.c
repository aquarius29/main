/*****************************************************************************
 * Product:  . .  
 * Version:  . .  
 * Released: Dec 27 2003 
 * Updated:  Dec 17 2004 
 *
 * Copyright (C) 2002-2004 Quantum Leaps. All rights reserved. 
 *
 * <licensing terms> (if any) 
 *
 *******************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "sched_ext_mngr.h"
#include "sched_types.h"

//#include "sched_proc_test.c"
//#include "sched_proc_test2.c"
#include "ex_pthread.c"

#define NUM_PROC 2 // number of processes

int main(void){
  struct proc p, p2;
  struct proc_poll *poll;
  p = create_proc(&init, &run);
  p2 = create_proc(&init, &run);

  
  init_poll(&poll);
  
  init_proc(&p, poll);
  init_proc(&p2, poll);
  /*init_proc(&p2, poll);
  init_proc(&p, poll);
  init_proc(&p2, poll);*/

  printf("Poll holds %d processes\n", poll->num_procs);

  run_poll(poll);

  free_poll(poll);
}

struct proc create_proc(int (*init_fun)(), int (*run_fun)()){
  struct proc p;
  p.init_fun = init_fun;
  p.run_fun  = run_fun;
  p.running_time = 0;
  p.running= 0;
  return p;
}

// calls the process function's init. and adds the proc to the poll.
void init_proc(struct proc *p, struct proc_poll *poll){
  if (poll->num_procs >= NUM_PROC) {
    // todo: error handling 
  }
  int ret= (*p->init_fun)();
  if ( ret == SUCCESS ){
    poll[poll->num_procs].p = p;
    poll[poll->num_procs-1].next_proc = &poll[poll->num_procs];
    poll->num_procs= poll->num_procs+1;
  }
}

// allocates memory for the processes to be added.
void init_poll(struct proc_poll **poll){
  *poll = malloc( sizeof(struct proc_poll) * NUM_PROC);
  if (*poll == NULL) {
    printf("Error allocating memory for poll...\n");
    exit(-1);
  }
  (*poll)->num_procs = 0;
  (*poll)->next_proc = NULL;

  //printf("poll inited... num procs = %d\n", poll->num_procs);
}

void free_poll(struct proc_poll *poll){
  free(poll);
}

void run_poll(struct proc_poll *poll){
  struct proc *p;
  pid_t pid;
  time_t t;
  do {
    pid= fork();
    p = poll->p;
    if (pid == 0){
      p->running_time = 0;
      p->pid= getpid();
      p->running = 1;
      int ret= (*p->run_fun)();
      _exit(0);
    } else {
      poll = poll->next_proc; /* iterate */
    } 
  } while (poll != NULL);
  
}

