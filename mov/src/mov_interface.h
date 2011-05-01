/*****************************************************************************
 * Product: mov_header.h
 * Version: 0.1
 * Created: April 4 2011
 *
 * Movement/CA Group
 *****************************************************************************/
#include <stdio.h>


/**************************NEW*/

//mov_logic.c
char to_MotorMessage(char ID0, char ID1, char increasing, char panicMode, char motor1,char motor2, char motor3, char motor4)



/*******************
//simulator variables
int arrived;


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


void test(void);  //test only, remove soon
void parse_naviInfo(void);
void parse_auto_order(void);
void parse_manual_order(float distance, float height);

void lift_off(float height);
void hover(void);
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

