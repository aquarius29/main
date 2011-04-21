#include <stdio.h>

#define START_MASK 1
#define LIFT_OFF_MASK 2
#define ALTITUDE_MASK 4 

//function for start
void start(int number){

  printf("in start %i\n", number);

  number = number & START_MASK;

  if(number < 1){
    printf("Shut down\n");    
  }
  else{
    printf("Power on\n");
  }
}
//function for lift off
void lift_off(int number){

  printf("in lift_off %i\n", number);

  number = number & LIFT_OFF_MASK;

  number = number >> 1;

  if (number < 1){
    printf("lift down\n");
  }
  else{
    printf("lift up\n");
  }

}
//function for altitude
void altitude(int number){

  printf("in alt%i\n", number);

  number = number & ALTITUDE_MASK;

  number = number >> 2;

  if (number < 1){

    printf("alt down\n");
  }
  else{
    printf("alt up\n");
  }
  //   main();
}


/*
int main(void){

  int number;
  printf("\n");
  printf("Enter a value");
  scanf("%i", &number);

  start(number);
  lift_off(number);
  altitude(number);
  return 0;
}

*/
