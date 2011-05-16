<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
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

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
struct vector
{
  float x;
  float y;
  float z;
};

<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
/* 
 *address of the accelerometer on the board 
 */
#define ADDRESS 0x40   

/*
 *Function prototypes
 */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
struct vector readAccel();

void init_accel();

/*Read data from accelerometer memory*/
struct vector readAccel()
{
  struct vector vect;
  int x,y,z;
  int temp;
  
  Wire.beginTransmission(ADDRESS);
  Wire.send(0x02); /*start of x LSB for reading data*/
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
void init_accel();
void readAccel();



/*int main()*/
/*//void setup()*/
/*{*/
/*  init();*/
/*  Wire.begin();*/
/*  Serial.begin(9600);*/
/*// initBMA180() should be done once, it will write appropriate adjustments for range and mode. */
/*//  init_accel();*/
/*//  delay(2000);*/
/*	while(1){*/
/*  readAccel();*/
/*  delay(300);*/
/*	}*/
/*  return 0;*/
/*}*/
=======
struct vector readAccel();
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93

void init_accel();

/*Read data from accelerometer memory*/
struct vector readAccel()
{
  struct vector vect;
  int x,y,z;
  int temp;
  
  Wire.beginTransmission(ADDRESS);
<<<<<<< HEAD
  Wire.send(0x02);  							/*start of x LSB for reading data*/
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
  Wire.send(0x02); /*start of x LSB for reading data*/
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
  Wire.endTransmission();
  Wire.requestFrom((int)ADDRESS, 7);
  
  if(Wire.available()==7)
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
    {
      int lsb = Wire.receive()>>2;
      int msb = Wire.receive();
      /* Since values are 14 bits we need to add 2 bits to fit 2s complement value */
      /* that is why we check for the sign by checking 14th bit and add corresponding value to 16th bit */
      x =(msb<<6)+lsb; 
      if (x&0x2000) x|=0xc000;
      /* shift 2 unused bits */
      lsb = Wire.receive()>>2;
      msb = Wire.receive();
      y =(msb<<6)+lsb;
      if (y&0x2000) y|=0xc000;
      lsb = Wire.receive()>>2;
      msb = Wire.receive();
      z =(msb<<6)+lsb;
      if (z&0x2000) z|=0xc000;
      /* Temperature values if we need them to use */
      temp = Wire.receive();
      if (temp&0x80) temp|=0xff00;
    }
  vect.x = x;
  vect.y = y;
  vect.z = z;   
  return vect;
<<<<<<< HEAD
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
  {
    int lsb = Wire.receive()>>2;
    int msb = Wire.receive();
    x=(msb<<6)+lsb; 
    if (x&0x2000) x|=0xc000;
/* shift 2 unused bits */
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
/*  result = Wire.endTransmission();*/
/*  Serial.print("raw data: ");*/
/*  Serial.print("X=");*/
/*  Serial.print(x);*/
/*  Serial.print(" Y=");*/
/*  Serial.print(y);*/
/*  Serial.print(" Z=");*/
/*  Serial.print(z);*/
/*  Serial.println();*/
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
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

<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "stab.h"




float read_accel()
{
  
  


  
  return 0;

}
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
