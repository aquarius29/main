/* The idea of simulating round-robin algorithm 
   is to create a structure for each process 
   and assign name, burst, working and waiting time 
   to be used  for round robin algorithm       */
#include <stdio.h>
#include "simulating_functions.h"


  PROCESS *proc;
 
  
int stab(){   
/* Allocate memory for proc*/
  proc = (PROCESS*)malloc(sizeof(PROCESS));
  if(proc == NULL){
    printf("ERROR!\n");
    return 1;
  }  
  proc->name = "STAB";
  proc->waiting_time=0;
  proc->working_time=0;  
  proc->burst = 8;
  round_robin(proc);
//  free(proc);
  return 0;
}

int ca(){
  proc = (PROCESS*)malloc(sizeof(PROCESS));
  if(proc == NULL){
    printf("ERROR!\n");
    return 1;
  }    
  proc->name = "COLLESION AVOIDENCE";
  proc->waiting_time=0;
  proc->working_time=0;
  proc->burst = 4;
  round_robin(proc);
//  free(proc);
  return 0;
}

int motor(){
  proc = (PROCESS*)malloc(sizeof(PROCESS));
  if(proc == NULL){
    printf("ERROR!\n");
    return 1;
  }  
  proc->name = "MOTOR";
  proc->waiting_time=0;
  proc->working_time=0;
  proc->burst = 5;
  round_robin(proc);
//  free(proc);
  return 0;
}

int mov(){
  proc = (PROCESS*)malloc(sizeof(PROCESS));
  if(proc == NULL){
    printf("ERROR!\n");
    return 1;
  }  
  proc->name = "MOVEMENT";
  proc->waiting_time=0;
  proc->working_time=0;
  proc->burst = 3;
  round_robin(proc);
//  free(proc);
  return 0;
}


/* According to algorithm, process burst time cant be more than 
   quantum time. If burst time less than quantum than process time 
   will be burst time instead quantum. 
   Quantum time is pre-fix time for each process. 
   Here is the algorithm analysis:
   http://choices.cs.uiuc.edu/~f-kon/RoundRobin/node2.html 
   http://www.springerlink.com/content/7tx6672754685622/    */
void round_robin(PROCESS *temp){  
  static int count=0;
  if((temp->burst <=QUANTUM) && (temp->burst != 0)){
    printf("process %s from %d to %d\n",temp->name, count,(count + proc->burst));
    count += proc->burst;
  }
  else{
    printf("process %s from %d to %d\n",temp->name, count,(count + QUANTUM));    
    count += QUANTUM;
  }
  free(temp);
}

