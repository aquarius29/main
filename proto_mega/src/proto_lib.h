<<<<<<< HEAD
/*!
* @file proto_lib.h 
* @brief Interface for protocol library
* @date 2011-05-12 
* @authors Elnaz Shahmehr, Mihail Anton, Navid Amiri, Pooyan Majd
* @details Describes how the protocol library
* facilitates data storage.
*/

//Collision to Movement Header
#include <stdint.h>

//write yaw from movement to collision avoidance   
void proto_write_yaw(int16_t value);// proto API 
 
//read yaw from movement to collision avoidance
int16_t proto_read_yaw(void);// proto API 

/***************************************************************************/
//camera to connectivity

void proto_write_camera(uint16_t message);
uint16_t proto_read_camera(void);
void proto_write_connect(uint16_t message);
uint16_t proto_read_connect(void);

/***************************************************************************/
//Providing message handling Between Navigation and Connectivity 

unsigned char proto_read_navi_to_connectivity(void); //API
void proto_send_navi_to_connectivity(unsigned char msg); //API

/***************************************************************************/

//movement to collision

//write movement
void proto_write_direction(int16_t value);
 
//read ca
uint16_t proto_read_direction(void);

/***************************************************************************/
//Move to Nav
struct movCommand
{
  uint16_t type; // (manual/auto)
  //(hovering/moving/landing/lift off/forward/backward/right/left)
  uint16_t order;
  int16_t height;
  uint16_t distance;
  int16_t yaw;
};

struct movCommand * proto_read_move_to_nav(void);
void createDefaultmove_to_nav();
void proto_write_nav_to_move(uint16_t type, uint16_t order, int16_t height,
    uint16_t distance, int16_t yaw);

//write movement to nav
void proto_write_move_to_nav(uint16_t isca);
 
//read nav from move
uint16_t proto_read_nav_to_move(void);

/***************************************************************************/
//movement to Motor
void proto_write_motor(uint8_t message);
uint8_t proto_read_motor(void);

struct move_commands * proto_read_motor2(void);
void createDefaultmove();
void proto_write_motor2(uint8_t message1, uint8_t message2, uint8_t message3,
	uint8_t message4, uint8_t message5, uint8_t message6, uint8_t message7,
	uint8_t message8);

struct move_commands{
	uint8_t message1;
	uint8_t message2;
	uint8_t message3;
	uint8_t message4;
	uint8_t message5;
	uint8_t message6;
	uint8_t message7;
	uint8_t message8;
};

/***************************************************************************/
 //Providing message handling Between Navigation and Connectivity

// Read msg from navigation to Movement and C/A
unsigned char proto_read_nav_to_mov_ca(void);// proto API

// send msg between navigation and Movement and C/A
void proto_send_nav_to_mov_ca(unsigned char msg);// proto API

// Read msg between connectivity and Navigation
unsigned char proto_read_connect_to_nav(void);// proto API

// Send msg between connectivity and Navigation
void proto_send_connect_to_nav(unsigned char msg); //proto API

// read current location from 
unsigned char proto_get_current_location(void);// proto API

//send current location via connecivity
void proto_send_current_location(unsigned char msg);// proto API

//read destination from navigation via connectivity
unsigned char proto_read_destination_msg_(void);// proto API


// pass msg of destination to navigation
void proto_send_destination_msg(unsigned char msg);

/***************************************************************************/



struct stab_attitude{
        float roll; // degrees
        float pitch; // degrees
        float yaw; //degrees
};

struct stab_gyroscope{
	float gyro_x; // raw data
	float gyro_y; // raw data
	float gyro_z; // raw data
};


float proto_stabReadHeight(void);
void proto_stabWriteHeight(float messageHeight);

void proto_stabWriteHeading(int messageHeading);
int proto_stabReadHeading(void);

void proto_stabWriteAttitude(float roll,float pitch,float yaw);
void proto_stabWriteGyro(float gyro_x,float gyro_y,float gyro_z);

struct stab_attitude * proto_stabReadAttitude(void);
struct stab_gyroscope * proto_stabReadGyro(void);

void createDefaultstabatt();
void createDefaultstabgyro();


/***************************************************************************/

///Test and Integration group

#define PROTO_READ 0
#define PROTO_WRITE 1

#define PROTO_STAB 3
#define PROTO_COLLISION 4
#define PROTO_NAV 5
#define PROTO_MOTOR 6
#define PROTO_MOVEMENT 7
#define PROTO_CONNECTIVITY 8
#define PROTO_CAMERA 9
#define PROTO_FILTER 10
#define PROTO_UI 10
#define PROTO_UNKNOWN -1

struct Message {
	int16_t operation;
	int16_t source;
	int16_t meaning;
	double value;
	struct Message *next;
};

void storeForTint(int16_t operation, int16_t source, int16_t meaning,
	double value);

struct Message * retrieve(void);
void flush_messages(void);

/***************************************************************************/

void proto_init(void);
=======
/*****************************************************************************
* Product: 
* Version: 
* Released: May 4 2011
* Updated: May 10 2011
*
* Copyright (C) 2011 Elnaz Shahmehr,Mihail Anton,Navid Amiri ,Pooyan Majd
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/



//Collision to Movement Header
#include <stdint.h>

//ca write yaw  
void proto_write_yaw(int value);// proto API 
 
 
//movement read yaw 
int proto_read_yaw(void);// proto API 


/****************************************************************************/
//camera to connectivity

void proto_write_camera(unsigned int message);

unsigned int proto_read_camera(void);

void proto_write_connect(unsigned int message);

unsigned int proto_read_connect(void);

/****************************************************************************/
//Providing message handling Between Navigation and Connectivity 

unsigned char proto_read_navi_to_connectivity(void); //API
 
void proto_send_navi_to_connectivity(unsigned char msg); //API

/****************************************************************************/

//movement to collision

//write movement
void proto_write_direction(int value);
 
 
//read ca
unsigned int proto_read_direction(void);



/****************************************************************************/
//movement to Motor
void proto_write_motor(uint8_t message);
uint8_t proto_read_motor(void);

struct move_commands * proto_read_motor2(void);
void createDefaultmove();

void proto_write_motor2(uint8_t message1,uint8_t message2,uint8_t message3,uint8_t message4,uint8_t message5,uint8_t message6,uint8_t message7,uint8_t message8);

struct move_commands{
	uint8_t message1;
	uint8_t message2;
	uint8_t message3;
	uint8_t message4;
	uint8_t message5;
	uint8_t message6;
	uint8_t message7;
	uint8_t message8;
};


/****************************************************************************/
 //Providing message handling Between Navigation and Connectivity

// Read msg from navigation to Movement and C/A

unsigned char proto_read_nav_to_mov_ca(void);// proto API

// send msg between navigation and Movement and C/A

void proto_send_nav_to_mov_ca(unsigned char msg);// proto API

// Read msg between connectivity and Navigation

unsigned char proto_read_connect_to_nav(void);// proto API

// Send msg between connectivity and Navigation

void proto_send_connect_to_nav(unsigned char msg); //proto API

// read current location from 

unsigned char proto_get_current_location(void);// proto API

//send current location via connecivity

void proto_send_current_location(unsigned char msg);// proto API

//read destination from navigation via connectivity

unsigned char proto_read_destination_msg_(void);// proto API


// pass msg of destination to navigation

void proto_send_destination_msg(unsigned char msg);

/****************************************************************************/


/// stab to movement
struct stab_gyroscope{
        float roll;
        float pitch;
	float yaw;

};


struct stab_accelerometer{
	float acc_x;
	float acc_y;
	float acc_z;
};


struct stab_magnetometer{
	int heading;
	float height;
};


void proto_stabWriteAttitude(float roll,float pitch,float yaw);

void proto_stabWriteAcc(float acc_x,float acc_y,float acc_z);

void proto_stabWriteHeading(int heading);

void proto_stabWriteHeight(float height);



struct stab_gyroscope * proto_stabReadAttitude(void);
struct stab_accelerometer * proto_stabReadAcc(void);
struct stab_magnetometer * proto_stabReadHeading(void);
struct stab_magnetometer * proto_stabReadHeight(void);


void createDefaultstabgyro();
void createDefaultstabacc();
void createDefaultstabmag();

/****************************************************************************/

///Test and Integration group



#define READ 0
#define WRITE 1

#define STAB 3
#define COLLISION 4
#define NAV 5
#define MOTOR 6
#define MOVEMENT 7
#define CONNECTIVITY 8
#define CAMERA 9
#define FILTER 10
#define UI 10
#define UNKNOWN -1

struct Message {
	int operation;
	int source;
	int meaning;
	double value;
	struct Message *next;
};

void storeForTint(int operation, int source, int meaning, double value);

struct Message * retrieve(void);

void flush(void);

/****************************************************************************/


>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
