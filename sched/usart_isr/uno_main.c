
#include "usart_isr_uno.h"

int main(void){
    usartInitUno();
    usartLoop();
    // usart_uno();
    
    return 0;
}