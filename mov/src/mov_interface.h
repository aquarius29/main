/*****************************************************************************
 * Product: mov_header.h
 * Version: 0.1
 * Created: April 4 2011
 *
 * Movement/CA Group
 *****************************************************************************/
#include <stdio.h>


/*movement*/
struct nav
{
	char type; // (manual/auto)
	char order; //(lift off/ hovering/ moving/ land)
	int height;
	int distance;
	int yaw;
	int speed;
};

void test(void);  //test only, remove soon

void parse_naviInfo(void);
void parse_auto_order(void);
void parse_manual_order(float distance, float height);
void lift_off(float height);
void hover(void);
void land(float height);
float assign_time(float distance,float speed);
float calc_accel(float distance,float speed);
float normalize_angle(float angle);
float get_direction_angle(float height, float distance);
float get_quad_angle(float roll, float pitch);
float momentOfInertia(char i);
float calc_pitch_roll(float height, float distance);
void move(float height ,float distance, float pitch, float roll);
void write_to_motor(float f1, float f2, float f3, float f4);

/*main*/
int old_x_desired;
int old_y_desired;
int old_z_desired;

struct nav navCommand;

int read_command(FILE *file);
int get_loc(char line[],char c,int indexOfColumn);
void assignValue(int index,char *temp);

/*stab*/
int error_calc(int desired, int measured);
int pid_X(void);
int pid_Y(void);
int pid_Z(void);

/*interface*/
int mov_init();
int mov_run();

//global time variables
int start_time;
int duration;
