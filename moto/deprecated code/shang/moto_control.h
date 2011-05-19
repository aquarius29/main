#include <stdint.h>
#define MOTORS 4
#define MAX_SPEED 100
#define SLEEP 60*1000
#define MOTOR_STARTTIMES 10

typedef 

struct motor
{
  int16_t speed;
  int16_t pinNumber;
} 

motor;

#define MOTOR_SIZE sizeof(motor)*4

typedef motor* motor_ptr;

void initMotors(motor_ptr);
void startMotors(motor_ptr);
void stopMotors(motor_ptr);
void setSpeed(motor_ptr, int16_t);
void printStatus(motor_ptr);
void frontMotors(motor_ptr, int16_t ,char);
void backMotors(motor_ptr, int16_t, char);
void rightMotors(motor_ptr, int16_t, char);
void leftMotors(motor_ptr, int16_t, char);
