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

#include <unistd.h> 
#include <time.h>

//
// 
//  Extended Scheduler - Process Manager
//
//
//

struct proc{
  pid_t pid;
  //pid_t parent_id;
  char running;
  time_t running_time;
  int (*init_fun)(); // init function pointer
  int (*run_fun)(); // run function pointer
};

struct proc_poll{
  struct proc *p;
  struct proc_poll *next_proc;
  short int num_procs;
};

// creates a process by passing a function pointer.

struct proc create_proc(int (*init_fun)(), int (*run_fun)());
void init_proc(struct proc *, struct proc_poll *);
void add_proc(struct proc_poll *, struct proc *);
void init_poll(struct proc_poll **);
void run_procs(struct proc_poll *);
void free_poll(struct proc_poll *);
void run_poll(struct proc_poll *);

