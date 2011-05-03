/*****************************************************************************
* Product: 
* Version: 
* Released: April 8 2011
* Updated: May 3 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

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


void stabWriteAttitude(struct stab);

void stabWriteAcc(struct stab);

void stabWriteHeading(struct stab);

void stabWritePressure(struct stab);



