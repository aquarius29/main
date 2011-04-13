#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

#include "moto_run.h"
#include "moto_msg_manipulation.h"
#include "moto_driver_functions.h"
#include "moto_msg_handler.h"

msg binary;
msg_pointer mp;
int x = 5;

#ifdef ARDUINO
//Pins for testing
int ledPin = 13;

void setup(){
  moto_init();
}

void loop(){
  Serial.println("Inside loop, before");
  moto_run();
  Serial.println("Inside loop");
}
#endif

int main(void){
#ifdef ARDUINO
  setup();
  while (x-- != 0){
  loop();
  }
  Serial.println("Exited Loop");
#elif defined PC
  moto_init();
  moto_run();

#endif
}

int moto_init(void){
  mp = &binary;
#ifdef ARDUINO
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
#elif defined PC  
  x = 5;
#endif

  return 0;  
}


int moto_run(void){
#ifdef ARDUINO
  binary = scanHexMsgSTDIN();
  delay(200);
  examineID(mp);
  
  if(leftMotor > 0 && rightMotor > 0 && frontMotor > 0 && rearMotor > 0){
    digitalWrite(13, HIGH);  
  }
  else
    digitalWrite(13, LOW);
  
  printMsg(mp);
  printMotorStatus();
  //  delay(5000);
#elif defined PC
  while(x != 0){
    binary = scanHexMsgSTDIN();
    examineID(mp);
    printMsg(mp);
    printMotorStatus();
    x--;
  }

#endif
  return 0;
}
