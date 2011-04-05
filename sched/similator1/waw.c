#include<stdio.h>
#include"waw.h"

int main(int argc , char **argv){

     if (argc < 2){
       printf("\n\n\n you should enter argument through \n  command line to define the time of flying \n\n");
        return;
         }
      printf("\n\nStarting of the flight -- nice trip -- !!!!\n \n");

      int time_of_flying = atoi(argv[1]);
      feed(time_of_flying  ); 
      
      printf("\n\n End of the flight ,, hope you travel with us again  \n\n");
  
     return 0;  
  }








 
  
