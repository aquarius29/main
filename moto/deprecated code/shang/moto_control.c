#include <stdio.h>
#include <stdlib.h>
#include "moto_control.h"

// 0 frontright 1 frontleft 2 backright 3 backleft
int main(){
  motor motors[MOTORS];
  motor_ptr ptr = &motors[0];
  
  initMotors(ptr);
  printStatus(ptr);
  startMotors(ptr);

  rightMotors(ptr,50,0);
  leftMotors(ptr,50,0);
  frontMotors(ptr,50,0);
  backMotors(ptr,50,0);

  return 1;
}

void initMotors(motor_ptr ptr)
{
  int i;
  motor_ptr mot;
  
  printf("initialized motors ... \n");

  for (i=0;i< MOTORS;i++)
    {
      mot=&ptr[i];
      mot->speed=0x0;
      mot->pinNumber= i;
    }
}

void startMotors(motor_ptr ptr)
{
  motor_ptr m;
  int i,count=0;

  while (count<MOTOR_STARTTIMES)
    {
      for (i=0; i< MOTORS; i++)
	{
	  m = &ptr[i]; // point to motor array
	  m->speed= m->speed + 5;
	  setSpeed(m, m->speed);
	}
      
      // printStatus(ptr);

      usleep(SLEEP);
      count+=1;
    }
}

void stopMotors(motor_ptr ptr)
{
  motor_ptr m;
  int i,count=0;
  for (i=0; i< MOTORS; i++)
    {
      m = &ptr[i];
      m->speed= 0;
      setSpeed(m, m->speed);
    }
}


void setSpeed(motor_ptr ptr, int16_t speed)
{
#ifdef ARDUINO 
  analodWrite(ptr->pinNumber, speed);
#else
  printf("Setting speed %d to pin %x\n", speed, ptr->pinNumber);
#endif
}

void printStatus(motor_ptr ptr) // for debugging
{
  int i;
  motor m;
  for (i=0; i< MOTORS; i++)
    {
      m = ptr[i];
      printf("Motor %d\n--------\n", i);
      printf("Pin number: %d\n", m.pinNumber);
      printf("Speed: %d\n\n", m.speed);
    }
}

void frontMotors(motor_ptr ptr, int16_t speed, char increase) // increase=1 : no increase, 0= increase, -1= decrease 
{
  printf("Front motors ... \n");
  motor_ptr m;
  m= &ptr[0];

  if (increase > 0)
    m->speed+= speed;
  else if(increase < 0)
    m->speed-= speed;
  else m->speed= speed;

  setSpeed(m, m->speed);

  m= &ptr[1];
  if (increase > 0)
    m->speed+= speed;
  else if(increase < 0)
    m->speed-= speed;
  else m->speed= speed;

  setSpeed(m, m->speed);
}

void backMotors(motor_ptr ptr, int16_t speed, char increase)
{
  printf("Back motors ... \n");
  motor_ptr m;
  m= &ptr[2];

  if (increase > 0)
    m->speed+= speed;
  else if(increase < 0)
    m->speed-= speed;
  else m->speed= speed;


  setSpeed(m, m->speed);
  m= &ptr[3];

  if (increase > 0)
    m->speed+= speed;
  else if(increase < 0)
    m->speed-= speed;
  else m->speed= speed;

  setSpeed(m, m->speed);
}

void rightMotors(motor_ptr ptr, int16_t speed, char increase)
{
  printf("Right motors ... \n");
  motor_ptr m;
  m= &ptr[0];


  if (increase > 0)
    m->speed+= speed;
  else if(increase < 0)
    m->speed-= speed;
  else m->speed= speed;

  setSpeed(m, m->speed);
  m= &ptr[2];
  if (increase > 0)
    m->speed+= speed;
  else if(increase < 0)
    m->speed-= speed;
  else m->speed= speed;


  setSpeed(m, m->speed);
}

void leftMotors(motor_ptr ptr, int16_t speed, char increase)
{
  printf("Left motors ... \n");
  motor_ptr m;
  m= &ptr[1];

  if (increase > 0)
    m->speed+= speed;
  else if(increase < 0)
    m->speed-= speed;
  else m->speed= speed;
  setSpeed(m, m->speed);

  m= &ptr[3];
  if (increase > 0)
    m->speed+= speed;
  else if(increase < 0)
    m->speed-= speed;
  else m->speed= speed;
  setSpeed(m, m->speed);
}
