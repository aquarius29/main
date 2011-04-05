#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <libarduino.h>

int main (void)
{
  int i ;
  sei(); /* enable interrupts */
  
      pinMode(13, OUTPUT); /* button on digital pin i */
  
  while (1) 
    {
  		digitalWrite(13, 1);
	  _delay_ms(500);
  		digitalWrite(13, 0);
	  _delay_ms(500);
    }
  
  return 1;
}
