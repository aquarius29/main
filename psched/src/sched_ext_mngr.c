/*! * * * * * * * * * * * * * * * * * *
 * @file extsched_mngr.c
 * @brief Extended Sheduler process manager.
 * @date 2011-05-04
 * @author Taher Odeh
 * @version 1.2
 * * * * * * * * * * * * * * * * * * * */

#include <sys/types.h>
#include "sched_ext_mngr.h"

void _psched_debug(char *msg){
#ifdef PC
  //fprintf(strerr, "psched: %s\n", msg);
#endif
}
#define NUM_PROC 2 /* number of processes */

/* creates a process.
 * type: process type
 * init_fun: init function of module
 * run_fun: run function of module 
 * return: a process struct member with it's type, init function and run function set.
 */
struct extsched_proc create_proc(enum proc_type type, int16_t (*init_fun)(), int16_t (*run_fun)()){
  struct extsched_proc p;
  p.init_fun = init_fun;
  p.run_fun  = run_fun;
  p.running_time = 0;
  p.running= 0;
  p.type= type;
  return p;
}

/* initializes a process and adds it to the poll 
 * p - pointer to a process member.
 */
void init_proc(struct extsched_proc *p){

  if (pool->num_procs >= NUM_PROC) {
    _psched_debug("Maximum number of processes reached ...");
    _exit(1);
  }
  
  (*p->init_fun)(); /* run initialization function */
  
  pool[pool->num_procs].p = p;
  pool[pool->num_procs-1].next_proc = &pool[pool->num_procs];
  pool->num_procs= pool->num_procs+1;
  
}

/* 
 *  initializes a process poll 
 *  pool - a process poll
 */
void init_pool(struct proc_pool **pool){
  /* allocating memory for the process poll. */
  *pool = malloc( sizeof(struct proc_pool) * NUM_PROC);
  
  if (*pool == NULL) {
    _psched_debug("Error allocating memory for poll, exiting...");
    _exit(1);
  }
  
  (*pool)->num_procs = 0;
  (*pool)->next_proc = NULL;

  /* creating a shared memory space. */
  if ( ((*pool)->shmid= sm_create()) == -1){
    _psched_debug("Failed to create shared memory");
    _exit(1);
  }
}

/* frees the poll 
 * pool - pointer to process poll to free.
 */
void free_pool(struct proc_pool *pool){
  free(pool);
}

/* runs the processes in the poll passed 
 *  pool- pointer to process poll to run.
*/
void run_pool(struct proc_pool *pool){
  struct extsched_proc *p;
  pid_t pid;
  //time_t t; (not used yet).

  do {
    pid= fork(); /* fork a process */
    p = pool->p; /* grab process from poll */
    if (pid == 0){ /* child process? */
      p->running_time = 0; // not used yet.  
      p->pid= getpid(); // not used.
      p->running = 1; // not used
      while (1) (*p->run_fun)(); /* start the run loop for the process */ 
      _exit(0);
    } else {
      pool = pool->next_proc; /* itedrate */
    } 
  } while (pool != NULL);
  
}

/* reads the process' state from the shared memory
 * allocated and stores it in a buffer. 
 * type - process type id
 * buff - buffer pointer to the write data to.
 * return: length of data read.
 */
int proc_read_state(enum proc_type type, void *buff){
  if (pool->shmid == -1){
    _psched_debug("Shared memory id error");
    return -1;
  }

  if (sm_read(pool->shmid, type, buff) == -1){
    _psched_debug("Error reading state from shared memory");
    return -1;
  }

  return 1;
}

/* writes the buffer to the shared memory
 * located to a specific process.
 * type - process type id.
 * data - data to write to state.
 * return: length of data written. or -1 if failed to write state.
 */
int proc_write_state(enum proc_type type, void* data)
{
  size_t len;
  
  if (pool->shmid == -1){
    _psched_debug("Shared memory id error");
    return -1;
  }
  
  if ((len=sm_write(pool->shmid, type, (char*)data)) == -1){
    _psched_debug("Error writing to shared memory");
    return -1;
  }
  
  return len;
}

/*
size_t proc_send(enum proc_type from, enum proc_type to, char *msg){
  size_t msg_len;
  int from_mqid;

  if ((from_mqid= get_mqid(from)) < 0){
    // error handling 
    return -1;
  }

  if ((msg_len= mq_send(from_mqid, to, msg)) < 0){
    // error handling 
    return -1;
  }
  
  return msg_len;
}



size_t proc_recv(enum proc_type own_proc, char *buff){
  size_t msg_len;
  int mqid;
  
  if ((mqid= get_mqid(own_proc)) < 0){
    // error handling 
    return -1;
  }
  
  if ((msg_len=mq_recv(mqid, own_proc, buff)) < 0){
    // error handling 
    return -1;
  }

  return msg_len;
  }
*/


