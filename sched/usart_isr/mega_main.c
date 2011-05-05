
#include "usart_isr_mega.h"

int main(void){
    usartInitMega();
    usartLoop();
    
    return 0;
}