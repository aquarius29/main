/*
 * file:         mov_interface.c
 * brief:
 * author:       Yanling Jin, Amber Olsson
 * date:         2011-05-03
 * version:      0.1
 * history      
 *
 * detail:
 */

#include <stdio.h>

/* global variables*/
int distanceToTravel;
int distanceTraveled;

int yawArrived;
int heightArrived;


/*mov_logic.c*/
void printNavCommand(void);
void command_logic(void);
void check_height(void);
void check_heading(void);
void check_pitch_roll(int isHovering);
void updateDistanceToTravel(void);
void printOrientation(void);

/*mov_motor.c*/
void start_motors(void);
void stop_motors(void);
void increase_rear_motor(void);
void decrease_rear_motor(void);
void increase_front_motor(void);
void decrease_front_motor(void);
void increase_left_motor(void);
void decrease_left_motor(void);
void increase_right_motor(void);
void decrease_right_motor(void);
void increase_rear_decrease_front(void);
void increase_front_decrease_rear(void);
void increase_left_decrease_right(void);
void increase_right_decrease_left(void);
void increase_all(void);
void decrease_all(void);
void hover(void);
void go_forwards(void);
void go_backwards(void);
void strafe_left(void);
void strafe_right(void);
void turn_left(void);
void turn_right(void);
void land(void);

char to_MotorMessage(char ID0, char ID1, char increasing, char panicMode, 
					 char motor1,char motor2, char motor3, char motor4);
void pWrite(char msg);
void print_char_to_Binary(char bin);



/*mov_main.c*/
//simulator variables
int readSensorTest(int currentSensor, char command);



struct nav
{
	char type;         // (manual/auto)
	char order;       //(lift off/ hovering/ moving/ land)
	int height;
	int distance;
	int yaw;
	int speed;
};

struct sensor
{
	int pitch;
	int roll;
	int yaw;
	int height;
};



/*main*/
int old_x_desired;
int old_y_desired;
int old_z_desired;

struct nav navCommand;
struct sensor sensorCommand;

int read_command();
int get_loc(char line[],char c,int indexOfColumn);
void assignValue(int index,char *temp);



/*interface*/
int mov_init();
int mov_run();

//global time variables
static int start_time;
int duration;


