/***************************************************************************
 * @file stab_ra.c
 * @brief Takes care of the communication with the accelerometer
 * @author Anton Shumeika & My Hogblom  	       
 * @date 10/04/2011
 * @history
 *    11/04/2011: following coding standards // anton
 ****************************************************************************/

#ifdef ARDUINO
#include "stab.h"
#include <Wire.h>
#include "WProgram.h"

struct vector
{
  float x;
  float y;
  float z;
};

/* 
 *address of the accelerometer on the board 
 */
#define ADDRESS 0x40   

/*
 *Function prototypes
 */
void init_accel();
struct vector readAccel();

/*Read data from accelerometer memory*/
struct vector readAccel()
{
  struct vector vect;
  unsigned int result;
  int x,y,z;
  int temp;
  
  Wire.beginTransmission(ADDRESS);
  Wire.send(0x02); /*start of x LSB for reading data*/
  Wire.endTransmission();
  Wire.requestFrom((int)ADDRESS, 7);
  
  if(Wire.available()==7)
    {
      int lsb = Wire.receive()>>2;
      int msb = Wire.receive();
      vect.x =(msb<<6)+lsb; 
      if (x&0x2000) x|=0xc000;
      /* shift 2 unused bits */
      lsb = Wire.receive()>>2;
      msb = Wire.receive();
      vect.y =(msb<<6)+lsb;
      if (y&0x2000) y|=0xc000;
      lsb = Wire.receive()>>2;
      msb = Wire.receive();
      vect.z =(msb<<6)+lsb;
      if (z&0x2000) z|=0xc000;
      temp = Wire.receive();
      if (temp&0x80) temp|=0xff00;
    }
  
  return vect;
}

/*
 *Initialize accelerometer and write all the values,
 * which corresponds to needed measurements. 
 */
void init_accel()
{
  int temp, result;
  int tempid;
  
  Wire.beginTransmission(ADDRESS);
  Wire.send(0x00);
  Wire.requestFrom(ADDRESS, 1);

  while(Wire.available())
  {
    temp = Wire.receive();
  }
  result = Wire.endTransmission();
  delay(10);
  if(temp == 3)
  {
    /* Connect to the ctrl_reg1 register and set the ee_w bit to enable writing. */
    Wire.beginTransmission(ADDRESS);
    Wire.send(0x0D);
    Wire.send(B0001);
    result = Wire.endTransmission();
    delay(10);
    Wire.beginTransmission(ADDRESS); /* set frequency values to 10 Hz*/
    Wire.send(0x20);
    Wire.send(B00001000);
    result = Wire.endTransmission();

    delay(10);
    Wire.beginTransmission(ADDRESS);
    Wire.send(0x35);
    Wire.send(B0100);                   /* set range of values to +-2g */
    result = Wire.endTransmission();

    delay(10);
  }
}

#endif

