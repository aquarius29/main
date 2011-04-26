/***************************************************************************
 * @file read_mg.c
 * @brief Takes care of the communication with the gyroscope
 * @author Adam Debbiche  	       
 * @date 20/04/2011
 * @history
 *    20/04/2011: Initial version // Adam
 ****************************************************************************/
#include <Wire.h>
#include "WProgram.h"
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
void write_data(byte addr, byte value);
void init_magn_hardware();
void read_magn_data();
void read_stream(byte addr, int bytes_to_read, char buffer[]);


int main()
{
  init();
  Serial.begin(9600);
  Wire.begin();
  //write_data(0x02, 0x00);
  init_magn_hardware(); // sets mode to continuous
  while(1)
    {
      read_magn_data();
      delay(1000);
    }
}


/*
 * Abstcract function that writes the value to the address given
 */
void write_data(byte addr, byte value)
{
  Wire.beginTransmission(MAGN_ADDRESS);
  Wire.send(addr);
  Wire.send(value);
  Wire.endTransmission();
  
}

void init_magn_hardware()
{
  delay(5); //waiting before init
  write_data(MAGN_MODE, 0x00);
  delay(100);
}


void read_magn_data()
{
  //Serial.println("Before READING");
  char buffer[6];
  int addr = 0x03;
  read_stream(addr, 6, buffer);
  
  int x, y, z;
 
  x = ((buffer[0] << 8) | buffer[1]);
  y = ((buffer[2] << 8) | buffer[3]);
  z = ((buffer[4] << 8) | buffer[5]); 
 
  //x++;
  //y++;
  //z++;
  char m[6];
  char n[6];
  char p[6];
  sprintf(m, "%d", x);
  sprintf(n, "%d", y);
  sprintf(p, "%d", z);
  //Serial.println(m);
  //Serial.println(n);
  //Serial.println(p);
  
  Serial.print(m);
  Serial.print("    Y: ");
  Serial.print(n);
  Serial.print("    Z: ");
  Serial.println(p);
  
  float heading = (atan2(y,x)+M_PI)*180/M_PI;
  Serial.print("Heading:   ");
  Serial.println(heading);
  
}

/*
 * Reads the bytes from the I2C bus and saves it to 
 * the buffer
 */
void read_stream(byte addr, int bytes_to_read, char buffer[])
{
  Wire.beginTransmission(MAGN_ADDRESS);
  Wire.send(addr);
  int n = Wire.endTransmission();
  Serial.print("END VALUE   ");
  Serial.println(n);
    
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

  write_data(0x00, 0x010+1); // set dor pos bias
  write_data(0x01, 1 << 5);
  float x, y, z;
  float mx, my, mz;

  int i =0;
  write_data(MAGN_MODE, 0x01); // set mode to not continuous
  while(i<10)
    {
      
    }

}
