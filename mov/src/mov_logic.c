#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "movement.h"

#define OBJECT_MASS 1000
#define STANDARD_ACCELERATION 20
#define OBJECT_LENGTH 50

//force components
struct motor{
  int force;
  int yawForce;
  int pitchForce;
  int rollForce;
}

//physical position
  struct position{
    double yawAngle;
    double pitchAngle;
    double rollAngle;
  }

  struct quadro {
    double heading;
    struct position;
    struct motor motors[4];
  }

  struct quadro quadrocopter;

//************************************************************
// update the pitch, roll and yaw                       pitch (x) , roll (y),  yaw (z)
//************************************************************
void update_p_r_y(double user_yaw, double user_pitch,double user_roll){

  //measured
  double force1=100;
  double force2=100;
  double force3=100;
  double force4=100;

  //record forces received
quadrocopter.motor[0].force = force1;
quadrocopter.motor[1].force = force2;
quadrocopter.motor[2].force = force3;
quadrocopter.motor[3].force = force4;
 
  //received quadrocopter attitude
  double yaw;
  double pitch;
  double roll;
  double heading;

  //record information to struct
  quadrocopter.position.yawAngle = yaw;
  quadrocopter.position.pitchAngle = pitch;
  quadrocopter.position.rollAngle = roll;
  quadrocopter.heading = heading;
  
 
  //seperate force components
  getForceComponents();
}


//************************************************************
// seperate force components
//************************************************************
getForceComponents()
{
  int count;

  for(count = 0; count <  4; count++)
    {
       quadrocopter.motor[count].yawForce = getForce(quadrocopter.motor[count].force, yaw);
       quadrocopter.motor[count].pitchForce = getForce(quadrocopter.motor[count].force, pitch);
       quadrocopter.motor[count].rollForce = getForce(quadrocopter.motor[count].force, roll);
    }
}



//************************************************************
// angular velocity is in radians per second
//************************************************************
double get_moment_of_inertia(int angular_velocity)
{
  double moment_of_inertia;
  moment_of_inertia = 0.5 * pow(angular_velocity,2) * OBJECT_MASS * pow(OBJECT_LENGTH,2);
  return moment_of_inertia;
}


//************************************************************
// gets the force components
//************************************************************
double  get_force(double totalForce, double angle)
{
   //http://www.mathalino.com/reviewer/engineering-mechanics/components-of-a-force
      double ForceComponent = totalForce * cos(angle);
      return ForceComponent;
 }


get totalForceUp(double f1, double f2, double f3, double f4, double x, double y){

  return (f1+f2+f3+f4)*cos(x)*cos(y);
}

