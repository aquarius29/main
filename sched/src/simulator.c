/* loop to call processes */
#include <stdio.h>
#include "simulating_functions.h"

void loop(function_fun *array);

void main(void){
  
  /* array consist of functions */
  function_fun array[]= {stab(),motor(),mov(),motor(),ca(),motor()};
  loop(array);
}

void loop(function_fun *array){
  int i=0;
  
  while(1){
    array[i]();
    i++;
  }
}  
  
