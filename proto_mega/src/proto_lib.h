/*****************************************************************************
* Product: 
* Version: 
* Released: May 4 2011
* Updated: May 4 2011
*
* Copyright (C) 2011 Elnaz Shahmehr,Mihail Anton,Navid Amiri ,Pooyan Majd
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/
//Collision to Movement Header


//write yaw from movement to collision avodance  
void proto_write_yaw(int value);// proto API 
 
 
//read yaw from movement to collision avodance 
unsigned int proto_read_yaw(void);// proto API 


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
//Filter To Motor

//void proto_write_filter(unsigned char message);

//unsigned char proto_read_filter(void);

//void proto_write_motor(unsigned char message);

//unsigned char proto_read_motor(void);

/****************************************************************************/
//proto interface

int proto_init(void);
int proto_run(void);

/****************************************************************************/

//filter to Motor Control

//void proto_write_motor_ctrl(char);
//	
//char proto_read_motor_ctrl(void);


/****************************************************************************/

//movement to collision

//write from movement to collision avodance 
void proto_write_direction(int value);
 
 
//read from movement to collision avodance 
unsigned int proto_read_direction(void);



/****************************************************************************/
//movement to Motor
void proto_write_motor(unsigned char message);
unsigned char proto_read_motor(void);


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
//Navigation to Movement


struct navigation {
      
char type;
char order;
int distance;
int yaw;
int height;

        }navigation;

       
struct proto read();//API


void write(struct proto msg);//API


/****************************************************************************/

/// stab to movement
struct stab {
        float roll;
        float pitch;
	float yaw;
	float acc_x;
	float acc_y;
	float acc_z;
	int heading;
	float pressure;
};


void proto_stabWriteAttitude(struct stab);

void proto_stabWriteAcc(struct stab);

void proto_stabWriteHeading(struct stab);

void proto_stabWritePressure(struct stab);

/****************************************************************************/

///Test and Integration group

#ifdef PC

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
} * mPtr;

void storeForTint(int operation, int source, int meaning, double value);

struct Message * retrieve(void);

void flush(void);

#endif


/****************************************************************************/
//UI to Connectivity

#define GO_FORWARD  1
#define GO_BACKWARD  0
#define GO_RIGHT  2
#define GO_LEFT  3
#define SET_TO_GPS 4

proto_readMsg(int instruction);
proto_sendMsg();


/****************************************************************************/



