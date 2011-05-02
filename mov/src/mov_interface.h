/*****************************************************************************
 * Product: mov_interface.h
 * Version: 0.1
 * Created: April 4 2011
 *
 * Movement/CA Group
 *****************************************************************************/
#include <stdio.h>


/**************************NEW*/

//mov_logic.c
void testNavCommand(void);
void command_logic(void);

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


char to_MotorMessage(char ID0, char ID1, char increasing, char panicMode, 
					 char motor1,char motor2, char motor3, char motor4);
void pWrite(char msg);
void print_char_to_Binary(char bin);

void check_height(void);
void check_heading(void);
void check_pitch_roll(int isHovering);

int speed;

int distanceToTravel;
int distanceTraveled;

int yawArrived;
int heightArrived;

void updateDistanceToTravel(void);


//*******************
//simulator variables
int arrived;
int readSensorTest(int currentSensor, char command);


/*movement*/
void moveL(void);

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

void test(void);  //test only, remove soon
void parse_naviInfo(void);
void parse_auto_order(void);
void parse_manual_order(float distance, float height);

void lift_off(float height);
//void hover(void);
void land(float height);

float assign_time(float distance,float speed);
float calc_accel(float distance,float speed);
float calc_pitch_roll(float height, float distance);


float normalize_angle(float angle);
float get_direction_angle(float height, float distance);
float get_quad_angle(float roll, float pitch);


float momentOfInertia(char i);
void move(float height ,float distance, float pitch, float roll);
void write_to_motor(float f1, float f2, float f3, float f4);

/*main*/
int old_x_desired;
int old_y_desired;
int old_z_desired;

struct nav navCommand;
struct sensor sensorCommand;

int read_command();
int get_loc(char line[],char c,int indexOfColumn);
void assignValue(int index,char *temp);

/*stab*/
void stabL(void);
int error_calc(int desired, int measured);
int pid_X(void);
int pid_Y(void);
int pid_Z(void);

/*interface*/
int mov_init();
int mov_run();

//global time variables
static int start_time;
int duration;


/*mov_matrix*/
void PrintMatrix3x3 (float ar[][3], int row);
void PrintMatrix3x1 (float ar[][1], int row);

void Matrix_3Mult3(float a1[][3], float a2[][3], float a3[][3] );
void Matrix_3Mult1(float m1[][3], float m2[][1], float answer[][1]);

void rotationMatrix(float roll, float pitch, float yaw, float rotation_matrix[][3]);

void transposeMatrix3x3(float rotation_matrix[][3], float transpose_rotation_matrix[][3]);
void transposeMatrix3x1(float matrix1[][3],float matrix2[][1]);

void MatrixScale3x1(float s, float matrix[][1],float newMatrix[][1], int row);
void MatrixScale3x3(float s, float matrix[][3],float newMatrix[][3], int row);

void Matrix_1Add1(float m1[][1], float m2[][1], float answer[][1] );
void Matrix_1Minus1(float m1[][1], float m2[][1], float answer[][1]);

