#include <stdio.h>

#define dt 0.01             //100ms loop time
#define Kp  0.1
#define Kd  0.01
#define Ki  0.005

static float preError=0;
float proportional;
float integral;
float derivation;
float error;
float output;

float PIDcontroller(float setPoint,float currentPos){
	error=setPoint-currentPos;
	integral= integral + (error * dt );
	derivation=(error - preError) / dt ;
	output = (Kp*error) + (Ki*integral) + (Kd*derivation);
	printf("\n\nthe output is %f \n\n",output);
}

void main(){

PIDcontroller(10,4);

}
