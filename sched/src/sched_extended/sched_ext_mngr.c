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

//
// 
//  Extended Scheduler - Process Manager
//
//
//

struct proc{
  pid_t pid;
  pid_t parent_id;
  char running;
  int running_time;
};

struct proc_poll{
  struct proc *p;
  struct proc *next_proc;
  short int num_procs;
}

//
//
// Create a process.
// parameters: a function pointer, and the parent pid.
//
(struct proc*) create_proc(int , pid_t);
void init_proc(struct proc *);
void add_proc(struct proc_poll *, struct proc *);
void init_poll(struct proc_poll *);
