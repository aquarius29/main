/***************************************************************************
 * @file read_rg.c
 * @brief Takes care of the communication with the gyroscope
 * @author Adam Debbiche & Yuwen He  	       
 * @date 05/04/2011
 * @history
 *    11/04/2011: Initial version // Adam
 *    14/04/2011: Added comments //Adam
 *    18/04/2011: Code now reflects coding standards
 ****************************************************************************/
#ifdef ARDUINO
#include <Wire.h>
#include "WProgram.h"

/*
 * Macros that define the address registers of the 
 * gyroscope used (full list in the spec)
 */
#define	SMPL	0x15
#define DLPF	0x16
#define INT_C	0x17
#define PWR_M	0x3E
#define GYRO_ADDRESS 0x69

/*
 *Function prototypes
 */
void write_data(byte addr, byte value);
void init_gyro_hardware();
void read_gyro_data();
void read_stream(byte addr, int bytes_to_read, byte buffer[]);


/*
 * Abstcract function that writes the value to the address given
 */
void write_data(byte addr, byte value)
{
  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.send(addr);
  Wire.send(value);
  Wire.endTransmission();
  
}

/*
 * Initializeses the gyroscope hardware and sets options 
 * for the power management...
 */
void init_gyro_hardware()
{
  write_data(PWR_M, 0x00);
  write_data(SMPL, 0x07);
  write_data(DLPF, 0x1E);
  write_data(INT_C, 0x00);  
}

/*
 * Reads the raw data from the gyroscope:
 * Each axis's data is stored in 2 bytes so
 * 6 bytes are read at one then each pair 
 * are merged together using the bitwise 
 * operation shift(<<) and or (|)
 */
void read_gyro_data()
{
  byte buffer[6];
  int addr = 0x1D;
  read_stream(addr, 6, buffer);
  
  int x, y, z;
  
  x = ((buffer[0] << 8) | buffer[1]);
  y = ((buffer[2] << 8) | buffer[3]);
  z = ((buffer[4] << 8) | buffer[5]); 
 

  Serial.println(x);
  Serial.println(y);
  Serial.println(z);

}

/*
 * Reads the bytes from the I2C bus and saves it to 
 * the buffer
 */
void read_stream(byte addr, int bytes_to_read, byte buffer[])
{
  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.send(addr);
  Wire.endTransmission();
    
  Wire.beginTransmission(GYRO_ADDRESS);  
  Wire.requestFrom(GYRO_ADDRESS, bytes_to_read); 
  
  int i;
  while(Wire.available())
  {
    buffer[i] = Wire.receive();
    i++;    
  }
  Wire.endTransmission();
   
}
#endif 
