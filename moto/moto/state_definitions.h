/* Module: msg_parsing.c
*  Author:  Rahwa Bahta, Reza moussavi
*  
*/

//Dont put any lines of code before this line
#ifndef _STATE_DEFINITIONS_H_
#define _STATE_DEFINITIONS_H_

//MASKS
#define MSG_ID_MASK		0xC0
#define MSG_CONTROL_MASK	0x80
#define MSG_SPECIAL_MASK	0xC0

#define MSG_REAR_MOTOR_MASK	0x01
#define MSG_FRONT_MOTOR_MASK	0x02
#define MSG_LEFT_MOTOR_MASK	0x04
#define MSG_RIGHT_MOTOR_MASK	0x08

#define MSG_PANIC_MASK	0x10
#define MSG_INCREASE_MASK	0x20

//MESSAGE STATES
# define  START_MOTOR 0x40
# define  STOP_MOTOR 0x0


# define  INCREASE_REAR_MOTOR 0xA1
# define  DECREASE_REAR_MOTOR 0x81
# define  INCREASE_FRONT_MOTOR 0xA2
# define  DECREASE_FRONT_MOTOR 0x82
# define  INCREASE_LEFT_MOTOR 0xA4
# define  DECREASE_LEFT_MOTOR 0x84
# define  INCREASE_RIGHT_MOTOR 0xA8
# define  DECREASE_RIGHT_MOTOR 0x88 
# define  DECREASE_FRONT_INCREASE_REAR 0xE3
# define  DECREASE_REAR_INCREASE_FRONT 0xC3
# define  DECREASE_RIGHT_INCREASE_LEFT 0xEC
# define  DECREASE_LEFT_INCREASE_RIGHT 0xCC

# define  FORWARD 
# define  BACKWARD 195
# define  TURN_RIGHT 236
# define  TURN_LEFT 206
 
# define  PANIC_INCREASE_REAR_MOTOR 177
# define  PANIC_DECREASE_REAR_MOTOR 145
# define  PANIC_INCREASE_FRONT_MOTOR 178
# define  PANIC_DECREASE_FRONT_MOTOR 146
# define  PANIC_INCREASE_LEFT_MOTOR 180
# define  PANIC_DECREASE_LEFT_MOTOR 148
# define  PANIC_INCREASE_RIGHT_MOTOR 184
# define  PANIC_DECREASE_RIGHT_MOTOR  152

# define  PANIC_FORWARD 243
# define  PANIC_BACKWARD 211
# define  PANIC_TURN_RIGHT 252
# define  PANIC_TURN_LEFT 220


struct bits_type
{
	unsigned char ID :2;
	unsigned char INCREASE :1;
	unsigned char PANIC :1;
	unsigned char RIGHT :1;
	unsigned char LEFT :1;
	unsigned char FRONT :1;
	unsigned char REAR :1;
};

// Dont put any code after this line
#endif