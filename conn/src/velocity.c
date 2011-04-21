#include <stdio.h>
#include <stdlib.h>

/*Author Michal Musialik*/

int alt = 0;

int main(void){
  
  char c;

  scanf("%c", &c);
  
    switch(c){
    case '+' :
    alt++;
    printf("%i\n",alt);
    main();
    case '-' :
    alt--;
    printf("%i\n",alt);
  
}
 
    if(alt < 0){
      printf("error altitide is to low\n");
      printf("Hover state iniciated\n");
      exit(-1);
    }
 main();

}
