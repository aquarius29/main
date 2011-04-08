#include "WProgram.h"
#include "HMC5843.h"

/* PUBLIC METHODS */
HMC5843::HMC5843() { 
	x_scale=1;
	y_scale=1;
	z_scale=1;
}

void HMC5843::init(bool setmode) {
  // note that we don't initialize Wire here. 
  // You'll have to do that in setup() in your Arduino program
	delay(5); // you need to wait at least 5ms after power on to initialize
	if (setmode) {
		setMode(0);
	}
}

void HMC5843::setMode(unsigned char mode) { 
	if (mode > 2) {
		return;
	}
	writeReg(HMC5843_R_MODE, mode);
	delay(100);
}

void HMC5843::calibrate(unsigned char gain) {
	x_scale=1; // get actual values
	y_scale=1;
	z_scale=1;
	writeReg(HMC5843_R_CONFA, 0x010 + HMC_POS_BIAS); // Reg A DOR=0x010 + MS1,MS0 set to pos bias
	setGain(gain);
	float x, y, z, mx=0, my=0, mz=0, t=10;
	for (int i=0; i<(int)t; i++) { 
		setMode(1);
		getValues(&x,&y,&z);
		if (x>mx) mx=x;
		if (y>my) my=y;
		if (z>mz) mz=z;
	}
	float max=0;
	if (mx>max) max=mx;
	if (my>max) max=my;
	if (mz>max) max=mz;
	x_max=mx;
	y_max=my;
	z_max=mz;
	x_scale=max/mx; // calc scales
	y_scale=max/my;
	z_scale=max/mz;
	writeReg(HMC5843_R_CONFA, 0x010); // set RegA/DOR back to default
}
// set data output rate
// 0-6, 4 default, normal operation assumed
void HMC5843::setDOR(unsigned char DOR) {
	if (DOR>6) return;
	writeReg(HMC5843_R_CONFA,DOR<<2);
}

void HMC5843::setGain(unsigned char gain) { 
  // 0-7, 1 default
	if (gain > 7) return;
	writeReg(HMC5843_R_CONFB, gain << 5);
}

void HMC5843::writeReg(unsigned char reg, unsigned char val) {
	Wire.beginTransmission(HMC5843_ADDR);
	Wire.send(reg);        // send register address
	Wire.send(val);        // send value to write
	Wire.endTransmission(); //end transmission
}

void HMC5843::getValues(int *x,int *y,int *z) {
	float fx,fy,fz;
	getValues(&fx,&fy,&fz);
	*x= (int) (fx + 0.5);
	*y= (int) (fy + 0.5);
	*z= (int) (fz + 0.5);
}

void HMC5843::getValues(float *x,float *y,float *z) {
	int xr,yr,zr;
	Wire.beginTransmission(HMC5843_ADDR);
	Wire.send(HMC5843_R_XM); // will start from DATA X MSB and fetch all the others
	Wire.endTransmission();
	Wire.beginTransmission(HMC5843_ADDR);
	Wire.requestFrom(HMC5843_ADDR, 6);
	if(6 == Wire.available()) {
	// read out the 3 values, 2 bytes each.
		xr = Wire.receive();
		xr = (xr << 8) + Wire.receive();
		*x= ((float) xr) / x_scale;
		yr = Wire.receive();
		yr = (yr << 8) + Wire.receive();
		*y = ((float) yr) / y_scale;
		zr = Wire.receive();
		zr = (zr << 8) + Wire.receive();
		*z = ((float) zr) / z_scale;
	// the HMC5843 will automatically wrap around on the next request
	}
	Wire.endTransmission();
}

void HMC5843::getValues(float *xyz) {
  getValues(&xyz[0], &xyz[1], &xyz[2]);
}

