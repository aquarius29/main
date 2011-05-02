#include "mov_interface.h"
//#include "proto_mov_motor.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define QUAD_MASS 1 //1kg
#define QUAD_RADUIS 0.5 //m
#define MOTOR_MASS 0.1 //m
#define PROPELLER_RADUIS 0.2 //m
#define MOTOR_RADUIS 0.1 //m
#define MOTOR_HEIGHT 0.1 //m
#define QUAD_HEIGHT 0.2 //m

#define CONSTANT 0.5 //m/s
#define AVERAGE_ANGULAR_VELOCITY 30 //degree/s
#define G 0.9807 //m/s^2
#define PI 3.14159265358979323846f
#define KTM 0.026//m constant which relats moment and thrust of a propeller


/* 
 * Print out the data from the navigation
 * For testing purpose only
 */
void test(void) {
    printf("==============================\n");
    printf("Type = %c\n", navCommand.type);
    printf("Order = %c\n", navCommand.order);
    printf("Height = %d\n", navCommand.height);
    printf("Distance = %d\n", navCommand.distance);
    printf("Yaw = %d\n", navCommand.yaw);
    printf("Speed = %d\n", navCommand.speed);
    printf("==============================\n");
}

void moveL(){
	printf("\nmove! ");
	parse_naviInfo();
}


/*
 * parse the navigation information
 */
void parse_naviInfo(void) {
    if (navCommand.type == 0){
		//auto mode 
		parse_auto_order();
	}
	else{
		//manual mode
		float distance=1000; //guess a distance?
		float height= 1000;//guess a height?
		parse_manual_order(distance,height);
	}
}


/*
 * parse the order when it's the auto mode
 */
void parse_auto_order(void) {

    char order = navCommand.order;
    float speed = navCommand.speed;

    if (order == 0) {
		lift_off(navCommand.height);
    } else if (order == 1) {
		hover();
    } else if (order == 2) {
		float angle= calc_pitch_roll(navCommand.height, navCommand.distance);
		move(navCommand.height, navCommand.distance, angle, angle);
    } else {
		float height = 1;//read sensor data, remember to change
	    land(height);
    }
}

/*
 * parse the order when it's the manual mode
 */
void parse_manual_order(float distance, float height) {

    char order = navCommand.order;

    if (order == 0) {
		lift_off(height);
    } else if (order == 1) {
		hover();
    } else if (order == 2) {
		float angle = calc_pitch_roll(height, distance);
		move(height,distance, angle, angle);
    } else {
		float height = 1;//read sensor data, remember to change
	    land(height);
    }
}


/*
 * lift off
 */
void lift_off(float height) {

    float f;

    f = (QUAD_MASS * G + QUAD_MASS * calc_accel(height, navCommand.speed)) / 4;
    write_to_motor(f, f, f, f);
}


/*
 * hover
 */
/* void hover(void) { */

/*     float f; */

/*     f = (QUAD_MASS * G) / 4; */
/* 	write_to_motor(f, f, f, f); */
/* } */


/*
 * land
 */
void land(float height) {
 
    float f;

    f = (QUAD_MASS * G - QUAD_MASS * calc_accel(height, navCommand.speed)) / 4;
    //write to motor
	write_to_motor(f, f, f, f);
}


/*
 * rotate
 */
void rotate(float angle) {

    //20 degree per sec
    float angular_velocity = calc_accel(normalize_angle(angle), AVERAGE_ANGULAR_VELOCITY);
	float totalforce = momentOfInertia('z') * angular_velocity;

    if (angle > 180) {
		
    } else {
		//m2 + m4 > m1 + m3
    }

}


/*
 * calcute the moment of inertia 
 */
float momentOfInertia(char i) {

    if (i == 'x') {
		float lxx=MOTOR_MASS *pow(MOTOR_RADUIS,2)/2+MOTOR_MASS*pow(MOTOR_HEIGHT,2)/6
			+2*MOTOR_MASS*pow(PROPELLER_RADUIS,2)+QUAD_MASS*pow(QUAD_RADUIS,2)/4
			+QUAD_MASS*pow(QUAD_HEIGHT,2)/12;
		return lxx;
    } else if (i == 'y') {
		float lyy=MOTOR_MASS *pow(MOTOR_RADUIS,2)/2+MOTOR_MASS*pow(MOTOR_HEIGHT,2)/6
			+2*MOTOR_MASS*pow(PROPELLER_RADUIS,2)+QUAD_MASS*pow(QUAD_RADUIS,2)/4
			+QUAD_MASS*pow(QUAD_HEIGHT,2)/12;
	    return lyy;
    } else if (i == 'z') {
		float lzz = QUAD_MASS * pow(QUAD_RADUIS, 2) / 2 
			+ 4 * MOTOR_MASS * pow(PROPELLER_RADUIS, 2);
		return lzz;
    }
	else{
		return 0;//should never reach here
	}
}


/*
 * 
 */
float normalize_angle(float angle) {

    if (angle > 180)
		return (angle - 180);
}

/*
 * receives an angle between 0 and 359 degrees
 * resturns the same angle between -pi and pi radians
 */
float degree2radians (float x)
{
	if(x>=0 && x<=180){
		x=-x*PI/180;
	}
	else{
		x = (360-x)*PI/180;
	}
	return x;
}

float radians2degree(float x){

	return x*180/PI;
}



/*
 * calculate the acceleration
 */
float calc_accel(float distance,float speed) {

    return distance* 2 / pow(assign_time(distance, speed), 2);
}



/*
 * assign time slot for fulfill the action
 * this is just an estimation time
 */
float assign_time(float distance, float speed) {

    float time = distance / speed;
    return time;
}



/*
 * 
 */
float calc_pitch_roll(float height, float distance){

	return 20;

}


/*
 * 
 */
void move(float height ,float distance, float pitch, float roll) {

    float force_direction = QUAD_MASS * calc_accel(distance,navCommand.speed);
    float fx = cos(get_direction_angle(height ,distance)) * force_direction;
    float ftotal = fx / sin(get_quad_angle(roll, pitch));
}


/*
 * 
 */
float get_direction_angle(float height, float distance) {
    float sinValue = height / distance;
    return asin(sinValue);
}


/*
 * 
 */
float get_quad_angle(float roll, float pitch) {

    float cosValue = cos(roll) * cos(pitch);
    return acos(cosValue);

}







































































/* float Vx; */
/* float Vy; */
/* float Vz; */

/* float turnAngle; */

/* float Ax; */
/* float Ay; */
/* float Az; */

/* float linearVelocities[3][1]={{Vx},{Vy},{Vz}}; */
/* float linearAccelerations[3][1]={{Ax},{Ay},{Az}}; */


/* void get_linearVelocity(float height, float distance){ */
/* 	float speed=navCommand.speed; */
/* 	Vz=get_direction_angle(height, distance)*speed; */
/* 	Vy=sqrt(pow(speed,2)-pow(Vz,2))*cos(turnAngle); */
/* 	Vx=sqrt(pow(speed,2)-pow(Vz,2))*sin(turnAngle); */
/* } */

/* void get_linearAcceleration(float height, float distance){ */
/* 	float acc=calc_accel(distance,navCommand,speed); */
/* 	Az=get_direction_angle(height, distance)*acc; */
/* 	Ay=sqrt(pow(acc,2)-pow(Az,2))*cos(turnAngle); */
/* 	Ax=sqrt(pow(acc,2)-pow(Az,2))*sin(turnAngle); */
/* } */

/* float q0,q1,q2,q3; */
/* float roll, pitch, yaw; */
/* void get_quaternion(){ */
/* 	float temp1=cos(roll/2)*cos(pitch/2)*cos(yaw/2); */
/* 	float temp2=sin(roll/2)*sin(pitch/2)*sin(yaw/2); */

/* 	float temp3=cos(yaw/2)*sin(pitch/2)*cos(roll/2); */
/* 	float temp4=sin(yaw/2)*cos(pitch/2)*sin(roll/2); */
/* 	float temp5=sin(yaw/2)*cos(pitch/2)*cos(roll/2); */
/* 	float temp6=cos(yaw/2)*sin(pitch/2)*sin(roll/2); */
/* 	q0=temp1+temp2; */
/* 	q1=temp1-temp2; */
/* 	q3=temp3+temp4; */
/* 	q4=temp5-temp6; */
/* } */

/* void get_pictch_roll_yaw(){ */

/* 	roll=atan(2*(q2*q3+q0*q1)/(pow(q0,2)-pow(q1,2)-pow(q2,2)-pow(q3,2))); */
/* 	pitch=asin(-1*(q1*q3-q0*q2)); */
/* 	yaw=atan(2*(q2*q3+q0*q1)/(pow(q0,2)+pow(q1,2)-pow(q2,2)-pow(q3,2))); */


/* } */




/* //\***************************************************************************************\// */

/* //Earth Axis */
/* float linearVelocities[3][1] = {{0}, */
/* 								 {0}, */
/* 			                 	 {0}}; */

/* float linearAcceleration[3][1] = {{0}, */
/* 				                  {0}, */
/* 								  {0}}; */

/* //Quadrocopter */
/* float angularVelocities[3][1] =  {{0}, */
/* 								  {0}, */
/* 								  {0}}; */

/* float angularAccelerations[3][1] =  {{0}, */
/* 									 {0}, */
/* 									 {0}}; */
/* float roll; */
/* float yaw; */
/* float pitch; */

/* float thrust1; */
/* float thrust2; */
/* float thrust3; */
/* float thrust4; */

/* float forceVector[3][1] = {{0},{0},{0}}; */

/* float moment_of_inertiaXY; */
/* float moment_of_inertiaZ; */

/* float  torqueNet  [3][1] = {{0}, */
/* 	  			         {0}, */
/* 				         {0}}; */

/* float momentx; */
/* float momenty; */
/* float momentz; */

/* /\*principal moments of inertia.*\/ */
/* float Mx; */
/* float My ; */
/* float Mz; */
    
/* float yz; */
/* float zx ; */
/* float xy; */
  

/* void  get_linearAccelerations_EarthAxis(){ */

/*     float forceMass[3][1]; */
/*     MatrixScale3x1((1/QUAD_MASS),forceVector,forceMass,3); */
    
/*     float gravityQuadro[3][1] = {{-1 * sin(pitch)},  //- sin pitch */
/* 								 {cos(pitch) * sin(roll)}, //cos pitch * sin roll */
/* 								 {cos(pitch) * sin(roll)}}; //cos pitch * sin roll */
    
/*     float gForce[3][1]; */
/*     MatrixScale3x1(G, gravityQuadro, gForce,3 ); */
/* } */


/* void get_torqueNet(){ */
/* 	float Mx =momentOfInertia('x'); */
/* 	float My = momentOfInertia('y'); */
/* 	float Mz = momentOfInertia('z'); */
/* 	float yz = angularVelocities[2][1] * angularVelocities[3][1]; */
/* 	float zx = angularVelocities[3][1] * angularVelocities[1][1]; */
/* 	float xy = angularVelocities[1][1] * angularVelocities[2][1]; */

    

/*     float  torque1[3][1] = { {Mx * angularAccelerations[1][1]}, */
/* 							 {My * angularAccelerations[2][1]} , */
/* 							 {Mz * angularAccelerations[3][1]}}; */

/*     float  torque2[3][1] = { {(Mz - My) * yz}, */
/* 		                	 {(Mx - Mz) * zx}, */
/* 			                 {(My - Mx) * xy}}; */

/*     Matrix_1Add1 (torque1, torque2, torqueNet); */
/* } */


/* void calc_moments(){ */
/* 	float temp[3][1]={{(Mz - My) * yz/Mx}, */
/* 					  {(Mx - Mz) * zx/My}, */
/* 					  {(My - Mx) * xy/Mz}}; */
/* 	float temp2[3][1]; */
/* 	Matrix_1Add1(temp,angularAccelerations, temp2); */

/* 	/\* momentx=(thrust4-thrust2)*QUAD_RADUIS; *\/ */
/* 	/\* momenty=(thrust1-thrust3)*QUAD_RADUIS; *\/ */
/* 	/\* momentz=(thrust1+thrust3-thrust2-thrust4)*KTM; *\/ */

/* 	/\* momentx=temp2[0][0]*Mx; *\/ */
/* 	/\* momenty=temp2[1][0]*My; *\/ */
/* 	/\* momentz=temp2[2][0]*Mz; *\/ */

/* 	/\* thrust2=thrust4-temp2[0][0]*Mx/QUAD_RADUIS; *\/ */
/* 	/\* thrust3=thrust1-temp2[1][0]*My/QUAD_RADUIS; *\/ */
/* 	/\* thrust1-thrust4=( temp2[2][0]*Mz/KTM+temp2[1][0]*My/QUAD_RADUIS-temp2[0][0]*Mx/QUAD_RADUIS)/2; *\/ */
/* } */


