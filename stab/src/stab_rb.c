/***************************************************************************
* @file read_rg.c
* @brief Takes care of the communication with the barometer
* @author Siyang Suo
* @date 14/04/2011
* @history
* 14/04/2011: Initial version // Siyang
* 18/04/2011: Code now reflects coding standards and add comment //Siyang
****************************************************************************/
#ifdef ARDUINO
#include <inttypes.h>
#include <Wire.h>
#include "WProgram.h"

/* From the datasheet the BMP module address LSB distinguishes
 * between read (1) and write (0) operations, corresponding to 
 * address 0xEF (read) and 0xEE (write).
 * shift the address 1 bit right (0xEF or 0xEE), the Wire library only   needs the 7 most significant bits for the address 
 * 0xEF >> 1 = 0x77, 0xEE >> 1 = 0x77
 */
#define BARO_ADDRESS 0x77
#define TO_READ 22

/*sensor registers from the BOSCH BMP085 datasheet*/
int ac1, ac2, ac3, b1, b2, mb, mc, md;
unsigned int ac4, ac5, ac6; 

/*oversampling for measurement*/
uint8_t osrs = 3;
/*delays for oversampling settings 0, 1, 2 and 3*/
uint8_t pwait_time[4] = { 5, 8, 14, 26 };

/*function prototype*/
long read_press();
unsigned int read_temp();
void calculate();
void read_data();
void baro_init();
void write_register(unsigned char r, unsigned char v);
char read_register(unsigned char r);

/*initialize temp and press*/
int Temp = 0;
long Press = 0;

  
/*=========functions=========*/

/*
*initialize baro
*/
void baro_init() {

  byte buff[TO_READ];
  int i=0;
  
  Wire.beginTransmission(BARO_ADDRESS);
  Wire.send(0xAA);
  Wire.endTransmission();

  Wire.beginTransmission(BARO_ADDRESS);
  Wire.requestFrom(BARO_ADDRESS, TO_READ);
  while(Wire.available()) {
      buff[i] = Wire.receive();
      i++;
  }

  ac1 = (buff[0]<<8) | buff[1];
  ac2 = (buff[2]<<8) | buff[3];
  ac3 = (buff[4]<<8) | buff[5];
  ac4 = (buff[6]<<8) | buff[7];
  ac5 = (buff[8]<<8) | buff[9];
  ac6 = (buff[10]<<8) | buff[11];
  b1 = (buff[12]<<8) | buff[13];
  b2 = (buff[14]<<8) | buff[15];
  mb = (buff[16]<<8) | buff[17];
  mc = (buff[18]<<8) | buff[19];
  md = (buff[20]<<8) | buff[21];

  Serial.println("Reading calibrating data: ");
  Serial.println(ac1);
  Serial.println(ac2);
  Serial.println(ac3);
  Serial.println(ac4);
  Serial.println(ac5);
  Serial.println(ac6);
  Serial.println(b1);
  Serial.println(b2);
  Serial.println(mb);
  Serial.println(mc);
  Serial.println(md);
}
/*
*
*/
void read_baro_data() {
  
  calculate();
  Serial.print("Temp: ");
  Serial.print(Temp, DEC);
  Serial.print("\tPress: ");
  Serial.println(Press, DEC);
  Serial.println("=================");
}
/*
*write register
*/
void write_register(unsigned char r, unsigned char v) {
  Wire.beginTransmission(BARO_ADDRESS);
  Wire.send(r);
  Wire.send(v);
  Wire.endTransmission();
}
/*
*read uncompensated temperature value
*/ 
unsigned int read_temp() {
  
  write_register(0xF4,0x2E);
  delay(5);

  unsigned char T_msb, T_lsb;
  Wire.beginTransmission(BARO_ADDRESS);
  /*register to read*/
  Wire.send(0xF6);
  Wire.endTransmission();

  /*request 2 bytes*/
  Wire.requestFrom(BARO_ADDRESS, 2);
  /*wait until data available*/
  while(!Wire.available());
  T_msb = Wire.receive();
  while(!Wire.available());
  T_lsb = Wire.receive();
  return (((int)T_msb<<8) | ((int)T_lsb));

}
/*
*read uncompensated pressure value
*/
long read_press() {
  write_register(0xF4,0x34+(osrs<<6));
  delay(pwait_time[osrs]);
  
  unsigned char P_msb, P_lsb, P_xlsb;

  Wire.beginTransmission(BARO_ADDRESS);
  /*register to read*/
  Wire.send(0xF6);
  Wire.endTransmission();

  /*request 3 bytes*/
  Wire.requestFrom(BARO_ADDRESS, 3);
  /*wait until data available*/
  while(!Wire.available());
  P_msb = Wire.receive();
  while(!Wire.available());
  P_lsb = Wire.receive();
  while(!Wire.available());
  P_xlsb = Wire.receive();
  return (((long)P_msb<<16) | ((long)P_lsb<<8) | ((long)P_xlsb))>>(8-osrs);
}
/*
*calculate the both true values of temp and press
*/
void calculate() {
  long x1, x2, x3, b3, b5, b6, p;
  unsigned long b4, b7;

  int UT = read_temp();
  long UP = read_press();
  
  /*calculate the true temperature value*/
  x1 = ((long)UT - ac6) * ac5 >> 15;
  x2 = ((long)mc << 11) / (x1 + md);
  b5 = x1 + x2;
  Temp = (b5 + 8) >> 4;

  /*calculate the true pressure value*/
  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11;
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;
  b3 = (((int32_t) ac1 * 4 + x3) << osrs + 2) >> 2;
  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 *b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (uint32_t)(x3 + 32768)) >> 15;
  b7 = ((uint32_t)UP - b3) * (50000 >> osrs);
  if(b7 < 0x80000000) {
    p = (b7 * 2) / b4;
  }
  else {
    p = (b7 / b4) * 2;
  }
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  Press = p + ((x1 + x2 + 3791) >> 4);

}
/*

int main(void) {
  init();
  Serial.begin(9600);
  Serial.println("Setting up BARO");
  
  Wire.begin();
  baro_init();
  while(1) {
      read_data();
      delay(500);
  }

  return 0;
}*/
#endif

    
