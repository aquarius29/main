/*!
 * @file:         mov_logic.c
 * @brief:        Contains the logic for calculate movement
 * @author:       
 * @date:         2011-05-10
 * @version:      0.1
 * @history      
 *
 * @detail:
 */
#ifdef PC
#include <stdlib.h>
#include <stdio.h>
#elif defined ARDUINO
#include "WProgram.h"
#endif

#include "mov_interface.h"

#define BUFF_YAW 15
#define BUFF_DISTSNCE 10
#define BUFF_PR 10
#define SPEED 100
#define DEFAULT_CA_DISTANCE 100

/*For Sending to Simulation */
#define INCREASING 1
#define DECREASING 2

extern int16_t distanceToTravel;
extern int16_t distanceTraveled;

extern uint8_t yawArrived;
extern uint8_t heightArrived;

uint8_t changingAltitude;
uint8_t changingHeading;

extern double duration;

extern struct nav navCommand;
extern struct nav *p;
extern struct sensor sensorCommand;
extern struct sensor *pSensorC;
extern struct sensor oldSensorCommand;


/*
 * This function init the movement of the drone
 * It checks the command from collision avoidance first
 * And then move according to the movement orders
 */
void command_logic(void) {

	//	doCa();

    printOrientation();
	convertCommand();

    uint8_t order = navCommand.order;  

	if (order == 1) {
		moveCommand();
		send_dir_to_ca(1);
    }else if(order == 2) {
		landCommand();
		send_dir_to_ca(0);
    }else { 
		hoverCommand();
		send_dir_to_ca(0);
	} 
}



void convertCommand(void){
	if(navCommand.type==0){
		p->type=1;
		p->height=navCommand.height+sensorCommand.height;
		p->yaw=navCommand.yaw+sensorCommand.yaw;
	}
}

/*
 *If Order is Hover, we will not attempt to move a distance.
 * Our pitch and roll is set to hover mode 
 */
void hoverCommand(void) {
	distanceToTravel = 0;
	check_heading();
	check_pitch_roll(0);
	check_changingAltitude();
	check_height();
}

/*
 *If order is set to move, 
 *we will attempt to control height, heading, and movement
 */
void moveCommand (void){
	if(yawArrived!=1){
		check_heading();
		check_pitch_roll(0);
		check_changingAltitude();
		check_height();
	}
	else{
		updateDistanceToTravel();
		check_pitch_roll(1);
		check_changingAltitude();
		check_height();
	}
}

/*
 *If order is set land, 
 *we attempt to go into hover mode and then land 
 */
void landCommand(void){
	navCommand.height=0;
	hoverCommand();
	if (sensorCommand.height <= 0){
		heightArrived = 1;
		stop_motors();
	}
	/*Order is invalid. Land! */
	else { 
		land(); 
		pSensorC->height = do_sensor_simulation(sensorCommand.height, DECREASING);
	} 
}


/*
 * Check the collision avoidance
 * Change the drone's heading according to the instruction
 * Set the default distance to 100
 */
void doCa(void){
	extern int8_t caDir;
	if(caDir>0){
		p->order = 1;
		yawArrived = 0;
		distanceToTravel = DEFAULT_CA_DISTANCE;

		if(caDir == 1){ /*FORWARDS ..add no sensor data */
			p->yaw = sensorCommand.yaw;
		}
		else if(caDir == 2){ /* BACKWARDS .. add 180 degrees to sensor data */
			p->yaw = sensorCommand.yaw + 180;
		}
		else if(caDir == 3){ /*GO LEFT... add -90 degrees to sensor data  */
			p->yaw = sensorCommand.yaw - 90;
		}
		else if(caDir == 4){ /*GO RIGHT ... add 90 degrees to sensor data */
			p->yaw = sensorCommand.yaw + 90;
		}
	}
	else if(caDir==0){
		p->order = 0;
		yawArrived = 0;
		distanceToTravel =0;
	}
    caDir = 5;
}

/*
 * Check if the Altitude is changing
 * return 1 as changing, 0 as not changing
 */
void check_changingAltitude(void){
    if(oldSensorCommand.height != sensorCommand.height + BUFF_DISTSNCE) {
		changingAltitude = 1;
	}
    else {
		changingAltitude = 0;
	}
}


/*
 * Check the drone height,
 * Adjust the motor according to the drone's height
 */
void check_height(void)
{
#ifdef DEBUG
#ifdef PC
    printf("@@@@@@@check height: \n");
#elif defined ARDUINO
	Serial.println("@@@@@@@@check height:");
#endif
#endif

    uint16_t height_desire =navCommand.height;
    uint16_t height_current =sensorCommand.height;

	/*higher than it supposed to be, decrease all motors*/
    if(height_current > height_desire+BUFF_DISTSNCE){	
		if(changingAltitude == 1) {
		    hover();	
		    decrease_all();
		}
		pSensorC->height = do_sensor_simulation(sensorCommand.height, DECREASING);
    }

	/*lower than it supposed to be, increase all motors*/
    else if(height_current<height_desire-BUFF_DISTSNCE){
		if(changingAltitude == 1) {	
			hover();
			increase_all();
		}			
		pSensorC->height = do_sensor_simulation(sensorCommand.height, INCREASING);
    }
	/*it's under the perfect height*/
    else{
		hover();
		heightArrived = 1;
    }
    printOrientation();
}



/*
 * Check the drone's heading
 * Adjust the drone's motor according to that
 */
void check_heading(void)
{
#ifdef DEBUG
#ifdef PC
    printf("@@@@@@@@check heading: \n");
#elif defined ARDUINO
	Serial.println("@@@@@@@check heading:");
#endif
#endif

   int16_t heading_desire=navCommand.yaw;
   int16_t heading_current=sensorCommand.yaw;
   int16_t difference = abs(heading_current-heading_desire);

    if(heading_current>heading_desire+BUFF_YAW && difference>180){
		turn_right();
		pSensorC->yaw = do_sensor_simulation(sensorCommand.yaw, INCREASING);
    }
	else if(heading_current>heading_desire+BUFF_YAW && difference<180){
		turn_left();
		pSensorC->yaw = do_sensor_simulation(sensorCommand.yaw, DECREASING);
    }
    else if(heading_current<heading_desire-BUFF_YAW && difference>180){
		turn_left();
		pSensorC->yaw = do_sensor_simulation(sensorCommand.yaw, DECREASING);
    }
    else if(heading_current<heading_desire-BUFF_YAW && difference<180){
		turn_right();
		pSensorC->yaw = do_sensor_simulation(sensorCommand.yaw, INCREASING);
    }
    else{
		hover();
		yawArrived = 1;
    }
    printOrientation();
}

/*
 * 
 */
void check_pitch_roll(uint8_t isHovering) {

#ifdef DEBUG
#ifdef PC
    printf("@@@@@@@@check pitch and roll: \n");
#elif defined ARDUINO
	Serial.println("@@@@@@@check pitch and roll:");
#endif
#endif

    int16_t pitch_current=sensorCommand.pitch;
	int16_t roll_current=sensorCommand.roll;
	int16_t pitch_desire;
    int16_t roll_desire;

    if(isHovering==0){
		pitch_desire=0;
		roll_desire=0;
    }
    else{
		pitch_desire=20;
		roll_desire=20;
    }
    //pitch clac
    if(pitch_current>pitch_desire+BUFF_PR){
		increase_left_decrease_right();
		
		/* simulated */
		pSensorC->pitch = do_sensor_simulation(sensorCommand.pitch, DECREASING);
    }
    else if(pitch_current<pitch_desire-BUFF_PR){
		increase_right_decrease_left();

		/* simulated */
		pSensorC->pitch = do_sensor_simulation(sensorCommand.pitch, INCREASING);
    }
    else{
		//great
    }

    //roll calc
    if(roll_current>roll_desire+BUFF_PR){
		increase_front_decrease_rear();

		/* simulated */
		pSensorC->roll = do_sensor_simulation(sensorCommand.roll, DECREASING);
    }
    else if(roll_current<roll_desire-BUFF_PR){
		increase_rear_decrease_front();


		/* simulated */
		pSensorC->roll = do_sensor_simulation(sensorCommand.roll, INCREASING);
    }
    else{
		//great
    }
    printOrientation();
}


/*
 * calculate the distance left
 */
void updateDistanceToTravel(void){
    distanceTraveled = SPEED * duration;
    distanceToTravel = distanceToTravel - distanceTraveled ;
}


/*
 * print the drone's current attitude,
 * DEBUG only
 */
void printOrientation(void)
{
#ifdef DEBUG
#ifdef PC
	printf("\n {pitch: %d roll: %d, yaw: %d height: %d distance left: %d}\n",
		   sensorCommand.pitch, sensorCommand.roll,sensorCommand.yaw,
		   sensorCommand.height, distanceToTravel );
#elif defined ARDUINO
	Serial.print("PITCH:");
	Serial.println(sensorCommand.pitch);
	Serial.print(" ROLL:");
	Serial.println(sensorCommand.roll);
	Serial.print(" YAW:");
	Serial.println(sensorCommand.yaw);
	Serial.print(" HEIGHT:");
	Serial.println(sensorCommand.height);
	Serial.print(" DISTANCE TO TRAVEL:");
	Serial.println(distanceToTravel);
#endif
#endif
}
