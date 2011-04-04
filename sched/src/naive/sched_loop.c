
#include <stdio.h>
#include "sched_stubs.h"

/* number of function pointers to use in array */
#define FUNS 5
#define FOREVER 1

#ifdef DEBUG
    #define DEBUG_F 1
#else
    #define DEBUG_F 0
#endif

/* type fun_t is type "function that returns int and takes no arguments" */
typedef int (*fun_t)(void); 

void loop(fun_t *funArr);

int main(void){
    /*  declare array of funtion pointers to loop around 
        the functions are declared in sched_stubs */
    fun_t funArr[FUNS] = {  &caRun,
                            &stabRun,
                            &moveRun,
                            &motoRun,
                            &protoRun};
    
    /* loop around the array of function pointers */
    loop(funArr);
    
    return 1;
}

void loop(fun_t *funArr){
    int i;
    int res;
    
    i = 0;
    while(FOREVER){
        res = (int)funArr[i](); /* call function at index i */
        i++;
        if(i == FUNS){          /* end of array */
            i = 0;              /* reset counter */
            if(DEBUG_F){
                return;
            }
        }
    }
}