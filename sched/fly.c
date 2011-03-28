/*
this is in some way similation to the action of other groups functions
and an attempt to test thier action with wrong (zero command line argument) 
or right (any argument other than zero) to flag error 
in case of wrong 

*/

#include<stdio.h>
#include"fly.h"
int main(int argc, char **argv){
int a =1;
int collid,mot,stab,nav,connect,cam;
if (argc < 2){
printf("you should enter argument to test \n");
return;
}
collid= atoi(argv[1]);
mot = atoi(argv[2]);
stab= atoi(argv[3]);
nav= atoi(argv[4]);
connect= atoi(argv[5]);
cam= atoi(argv[6]);
 while(a==1 ){
collidence(collid);
motor(mot);
stablization(stab);
navigation(nav);
connectivity(connect);
camera(cam);
//set a to zero to stop the loop 
a = 0; 
}
return 0;
}


void collidence(int x){
// if this function gets (0) as argument it will flag ( show ) error for collidence
if(x == 0){
printf("movement NOT GOOD     ---------->->->\n");
}
// the normal flying no collidence possibilty arguments can be any thing than (0)
else {
printf("movement is  OK\n");
    }
}


void motor(int x){
// if this function gets (0) as argument it will flag ( show ) error with motors
if(x == 0){
printf("motor  NOT GOOD      ---------->->->\n");
      }
// the normal flying no collidence possibilty arguments should be more than one 
else {
printf("motor is  OK\n");
    }
}


void stablization(int x){
// if this function gets (0) as argument it will flag ( show ) error with stablization
if(x == 0){
printf("stablization NOT GOOD ---------->->->\n");
      }
// the normal stablization , arguments can be any thing than (0) 
else {
printf("stablization is  OK\n");
    }
}


void navigation(int x){
// if this function gets (0) as argument it will flag ( show ) error with navigation
if(x == 0){
printf("navigation NOT GOOD ---------->->->\n");
      }
// the normal navigation action , arguments can be any thing than (0)
else {
printf("navigation is    OK \n");
    }
}


void connectivity(int x){
// if this function gets (0) as argument it will flag ( show ) error for connectivity
if(x == 0){
printf("connectivity NOT GOOD ---------->->->\n");
      }
// the normal connectivity , arguments can be any thing than (0)
else {
printf("connectivity is   OK\n");
    }
}


void camera(int x){
// if this function gets (0) as argument it will flag ( show ) errore for camera action
if(x == 0){
printf("camera NOT GOOD     ---------->->->\n");
      }
// the normal camera action , arguments can be any thing than (0)
else {
printf("camera is       OK\n");
    }
}

