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


void proto_stabWriteAttitude(struct stab);

void proto_stabWriteAcc(struct stab);

void proto_stabWriteHeading(struct stab);

void proto_stabWritePressure(struct stab);



