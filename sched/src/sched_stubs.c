
#include <stdio.h>

#ifdef ARDUINO
    #define ARDUINO_F 1
#else
    #define ARDUINO_F 0
#endif

int caRun(void){
    if(ARDUINO_F){

    }
    else{
        printf("inside caRun\n");        
    }
    return 1;
}

int stabRun(void){
    if(ARDUINO_F){
        
    }
    else{
        printf("inside stabRun\n");
    }
    return 1;   
}

int moveRun(void){
    if(ARDUINO_F){

    }
    else{
        printf("inside moveRun\n");        
    }
    return 1;   
}

int motoRun(void){
    if(ARDUINO_F){

    }
    else{
        printf("inside motoRun\n");        
    }
    return 1;
}

int protoRun(void){
    if(ARDUINO_F){

    }
    else{
        printf("inside protoRun\n");    
    }
    return 1;
}