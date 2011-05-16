/***************************************************************************
 * @file read_mg.c
 * @brief Takes care of the communication with the gyroscope
 * @author Adam Debbiche  	       
 * @date 20/04/2011
 * @history
 *    20/04/2011: Initial version // Adam
 ****************************************************************************/
#ifdef ARDUINO
<<<<<<< HEAD
#include <Wire.h>
=======
#include "Wire.h"
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
#include "WProgram.h"
#include "stab.h"
#include <stdlib.h>
#include <stdio.h>
/*
 * Macros that define the address registers of the 
 * magnetometer used (full list in the spec)
 */
#define MAGN_ADDRESS 0x1E
#define MAGN_MODE 0x02
#define M_PI 3.14159265358979323846
/*
 *Function prototypes
 */

struct vector
{
  float x;
  float y;
  float z;
};

void read_stream_mg(byte addr, int bytes_to_read, byte buffer[]);

void init_magn_hardware()
{
  delay(5); //waiting before init
  write_data(MAGN_MODE, 0x00, MAGN_ADDRESS);
  delay(100);
}


struct vector read_magn_data()
{
  struct vector vect;
  byte buffer[6];
  int addr = 0x03;
  read_stream_mg(addr, 6, buffer);
  
  vect.x = -((buffer[0] << 8) | buffer[1]);
  vect.y = -((buffer[2] << 8) | buffer[3]);
  vect.z = ((buffer[4] << 8) | buffer[5]);

<<<<<<< HEAD
  //vect.x = ((vect.x*M_PI)/180.0) - 15;
  //vect.y = ((vect.y*M_PI)/180.0) + 4.5;
  //vect.z = ((vect.z*M_PI)/180.0) - 31;
  //Serial.println(vect.x);
  //Serial.println(vect.y);
  //Serial.println(vect.z);

=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
  return vect;
}

/*
 * Reads the bytes from the I2C bus and saves it to 
 * the buffer
 */
void read_stream_mg(byte addr, int bytes_to_read, byte buffer[])
{
  Wire.beginTransmission(MAGN_ADDRESS);
  Wire.send(addr);
  Wire.endTransmission();    
  Wire.beginTransmission(MAGN_ADDRESS);  
  Wire.requestFrom(MAGN_ADDRESS, bytes_to_read); 
  
  int i;
  while(Wire.available() && i < 6)
  {
    buffer[i] = Wire.receive();
    i++;    
  }
  Wire.endTransmission();
   
}


void calibrate_magn()
{
  float scaled_x = 1;
  float scaled_y = 2;
  float scaled_z = 3;

  write_data(0x00, 0x010+1, MAGN_ADDRESS); // set dor pos bias
  write_data(0x01, 1 << 5, MAGN_ADDRESS);
  float x, y, z;
  float mx, my, mz;

  int i =0;
  write_data(MAGN_MODE, 0x01, MAGN_ADDRESS); // set mode to not continuous
  while(i<10)
    {
      
    }

}

#endif
