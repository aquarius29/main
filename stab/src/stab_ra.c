/*
 * 
 *
 *
 */

#include <Wire.h>
#include "WProgram.h"
#define ADDRESS 0x40   /* address of the accelerometer on the board */


int x,y,z;
int temp;


void init_accel();
void readAccel();
void checkResult(int result);



/*int main()*/
/*//void setup()*/
/*{*/
/*  init();*/
/*  Wire.begin();*/
/*  Serial.begin(9600);*/
/*// initBMA180() should be done once, it will write appropriate adjustments for range and mode. */
/*//  initBMA180();*/
/*//  delay(2000);*/
/*	while(1){*/
/*  readAccel();*/
/*  delay(300);*/
/*	}*/
/*  return 0;*/
/*}*/


/*Read data from accelerometer memory*/
void readAccel()
{
    unsigned int result;
  
  Wire.beginTransmission(ADDRESS);
  Wire.send(0x02);  							/*start of x LSB for reading data*/
  Wire.endTransmission();
  Wire.requestFrom((int)ADDRESS, 7);
  if(Wire.available()==7)
  {
    int lsb = Wire.receive()>>2;
    int msb = Wire.receive();
    x=(msb<<6)+lsb; 
    if (x&0x2000) x|=0xc000; // set full 2 complement for neg values
    lsb = Wire.receive()>>2;
    msb = Wire.receive();
    y=(msb<<6)+lsb;
    if (y&0x2000) y|=0xc000;
    lsb = Wire.receive()>>2;
    msb = Wire.receive();
    z=(msb<<6)+lsb;
    if (z&0x2000) z|=0xc000;
    temp = Wire.receive();
    if (temp&0x80) temp|=0xff00;
  }
  result = Wire.endTransmission();
/*  Serial.print("raw data: ");*/
/*  Serial.print("X=");*/
/*  Serial.print(x);*/
/*  Serial.print(" Y=");*/
/*  Serial.print(y);*/
/*  Serial.print(" Z=");*/
/*  Serial.print(z);*/
/*  Serial.println();*/
}
//============================

void init_accel()
{
  int temp, result, error;
  int tempid;
  
  Wire.beginTransmission(ADDRESS);
  Wire.send(0x00);
  Wire.requestFrom(ADDRESS, 1);
  while(Wire.available())
  {
    temp = Wire.receive();
  }
  result = Wire.endTransmission();
  checkResult(result);
  if(result > 0)
  {
    error = 1;
  }
  delay(10);
  if(temp == 3)
  {
    // Connect to the ctrl_reg1 register and set the ee_w bit to enable writing.
    Wire.beginTransmission(ADDRESS);
    Wire.send(0x0D);
    Wire.send(B0001);
    result = Wire.endTransmission();
    checkResult(result);
    if(result > 0)
    {
  	 	error = 1;
    }
    delay(10);
    // Connect to the bw_tcs register and set the filtering level to 10hz.
    Wire.beginTransmission(ADDRESS);
    Wire.send(0x20);
    Wire.send(B00001000);
    result = Wire.endTransmission();
    checkResult(result);
    if(result > 0)
    {
   	error = 1;
    }
    delay(10);
    // Connect to the offset_lsb1 register and set the range to +- 2.
    Wire.beginTransmission(ADDRESS);
    Wire.send(0x35);
    Wire.send(B0100);
    result = Wire.endTransmission();
    checkResult(result);
    if(result > 0)
    {
   error = 1;
    }
    delay(10);
  }

  if(error == 0)
  {
    Serial.print("\nBMA180 Init Successful");
  }
}

void checkResult(int result)
{
  if(result >= 1)
  {
	//probably device is not connected or not all bits are ready to be read.
    Serial.print("PROBLEM. Result code is ");  
    Serial.print(result);
	 Serial.print(". Device is probably not connected properly");  
   /* result code explanation
	1 = data too long to fit in transmit buffer
	2 = received NACK on transmit of address
	3 = received NACK on transmit of data
	4 = other error
	*/
  }
  else
  {
// device is connected properly and there are bytes ready to be read.
//    Serial.println("Read/Write success");
  }
}




