/* header for simulating processes */


#ifndef simulating_functions.h
#define simulating_functions.h

#define QUANTUM 5

typedef int (*function_fun)(void);

/* each process has a name, burst, waiting and working time */
typedef struct process{
  char *name;
  int burst;
  int waiting_time;
  int working_time;
}PROCESS;


  extern PROCESS *proc;

  int stab();
  int mov();
  int ca();
  int motor();
  void round_robin(PROCESS *proc);


  
#endif
