/*! 
    @file blink.c
    @brief Modified Arduino blinking example \n
    Brief description can be split into multiple lines.
    @date 2011-04-13
    @author Eugene
    @version 3
    @history 2011-04-13 - added code of original Arduino example\n
             2011-04-12 - added Doxygen comments \n
             2011-04-07 - created this example
    @details This is a modification of blinking example shipped with Arduino IDE:\n 
    @code

        void setup() {                
            // initialize the digital pin as an output.
            // Pin 13 has an LED connected on most Arduino boards:
            pinMode(13, OUTPUT);     
        }

        void loop() {
            digitalWrite(13, HIGH);   // set the LED on
            delay(1000);              // wait for a second
            digitalWrite(13, LOW);    // set the LED off
            delay(1000);              // wait for a second
        }
    @endcode
    This example was created to demonstrate the following:\n
    1) Use of preprocessor directives for conditional compialtion. The code below icnludes the actual blinking functionality when compiled for Arduino, while compilation for PC replaces it with print outs. ARDUINO and PC macros used below are defined automatically during compilation using project's makefile.\n
    2) Use of Doxygen commands for commenting code for later documentation generation.
  
 */

#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

/*! @brief Including the blinking interface */
#include "blink_interface.h"

/*!
@brief Hardware initialization function.
@details This function initializes digital pin 13, which has a connected LED on most Arduino borard, as an output. It prints out test string when compiled for PC.
 */
static void setup() {                

#ifdef ARDUINO // Arduino code
   pinMode(13, OUTPUT);
  
#elif defined PC // PC code
   printf("%s\n", "Pin 13 mode = output");
   	
#endif
      
}

/*!
@brief Endless loop function.
@details This endless loop function blinks the pin 13 LED based on the arguments values. It does test printouts when compiled for PC. 
@param on blinking time in ms
@param off off time in ms 
 */
static void loop(int on, int off) {

  //int on = 500;
  //int off = 500;

#ifdef ARDUINO // Arduino code
  digitalWrite(13, HIGH);   // set the LED on
  delay(on);               // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  delay(off);               // wait for a second

#elif defined PC // PC code
  printf("%s%d%s\n", "Set pin 13\t ON\t for ", on, " ms");
  printf("%s%d%s\n", "Set pin 13\t OFF\t for ", off, " ms"); 
#endif
}


int main(void)
{

#ifdef ARDUINO // Arduino code
  init(); // init the Arduino hardware
#endif

  setup();

  for (;;)
    loop(500, 500);

  return 0;
}
