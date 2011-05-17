#include <stdio.h>
#define FORWARD 0xE3
#define TURN_RIGHT 0xEC
#define TURN_LEFT 0xCE
#define BACKWARD 0xC3

/*#define PANIC_STATE 0x80
#define START_STATE 0x40
#define INCREASE_MOTOR 0x20
#define DECREASE_MOTOR 0x10
#define RIGHT_MOTOR 0x8
#define LEFT_MOTOR 0x4
#define FRONT_MOTOR 0x2
#define REAR_MOTOR 0x1
#define STOP_STATE 0x0*/

unsigned char generate_value_Inc_motor(unsigned char motor);
unsigned char generate_value_Dec_motor(unsigned char motor);
unsigned char generate_value_Con_motor(unsigned char motor);
unsigned char generate_value_Pan_motor(unsigned char motor);




