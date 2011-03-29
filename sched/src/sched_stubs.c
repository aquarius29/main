
#include <stdio.h>

int caRun(void){
    #ifdef ARDUINO
    
    #else
        printf("inside caRun\n")
    #endif
    return 1;
}

int stabRun(void){
    #ifdef ARDUINO
    
    #else
        printf("inside stabRun\n")
    #endif
    return 1;
}

int moveRun(void){
    #ifdef ARDUINO
    
    #else
        printf("inside moveRun\n")
    #endif
    return 1;
}

int motoRun(void){
    #ifdef ARDUINO
    
    #else
        printf("inside motoRun\n")
    #endif
    return 1;
}

int protoRun(void){
    #ifdef ARDUINO
    
    #else
        printf("inside protoRun\n")
    #endif
    return 1;
}