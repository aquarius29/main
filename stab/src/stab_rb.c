/***************************************************************************
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
 * @file stab_rb.c
 * @brief Takes care of the communication with the barometer
 * @author Siyang Suo
 * @date 14/04/2011
 * @history
 * 14/04/2011: Initial version // Siyang
 * 18/04/2011: Code now reflects coding standards and add comment //Siyang
 * 27/04/2011: Renamed some functions and integrated code with the rest //Adam
 * 06/05/2011: Fix bug with temperature and get absolute height via pressure  //Siyang
 * 07/05/2011: Formatting code... //Adam
 ****************************************************************************/
<<<<<<< HEAD
#ifdef ARDUINO
#include <inttypes.h>
#include <Wire.h>
#include <math.h>
#include "WProgram.h"
#include "stab.h"
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
* @file read_rg.c
* @brief Takes care of the communication with the barometer
* @author Siyang Suo
* @date 14/04/2011
* @history
* 14/04/2011: Initial version // Siyang
* 18/04/2011: Code now reflects coding standards and add comment //Siyang
****************************************************************************/
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
#ifdef ARDUINO
#include <inttypes.h>
#include <Wire.h>
#include <math.h>
#include "WProgram.h"
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
#include "stab.h"
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93

/* From the datasheet the BMP module address LSB distinguishes
 * between read (1) and write (0) operations, corresponding to 
 * address 0xEF (read) and 0xEE (write).
 * shift the address 1 bit right (0xEF or 0xEE), the Wire library only   needs the 7 most significant bits for the address 
 * 0xEF >> 1 = 0x77, 0xEE >> 1 = 0x77
 */
#define BARO_ADDRESS 0x77
#define TO_READ 22

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
struct baro_data
{
  int temp;
  long pressure;
  float height;
}barom;

<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
/*sensor registers from the BOSCH BMP085 datasheet*/
int ac1, ac2, ac3, b1, b2, mb, mc, md;
unsigned int ac4, ac5, ac6; 

/*oversampling for measurement*/
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
const uint8_t osrs = 3;
/*delays for oversampling settings 0, 1, 2 and 3*/
const uint8_t pwait_time[4] = { 5, 8, 14, 26 };
=======
uint8_t osrs = 3;
/*delays for oversampling settings 0, 1, 2 and 3*/
uint8_t pwait_time[4] = { 5, 8, 14, 26 };
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
uint8_t osrs = 3;
/*delays for oversampling settings 0, 1, 2 and 3*/
uint8_t pwait_time[4] = { 5, 8, 14, 26 };
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
const uint8_t osrs = 3;
/*delays for oversampling settings 0, 1, 2 and 3*/
const uint8_t pwait_time[4] = { 5, 8, 14, 26 };
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93

/*function prototype*/
long read_press();
unsigned int read_temp();
void calculate();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
void write_register(unsigned char r, unsigned char v);
char read_register(unsigned char r);

/*initialize temp, press and height*/
int Temp = 0;
long Press = 0;
float Height = 0;


/*=========functions=========*/
/*
 *initialize baro device
 */
void init_baro_hardware() {
  
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
void read_data();
void baro_init();
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
void write_register(unsigned char r, unsigned char v);
char read_register(unsigned char r);

/*initialize temp, press and height*/
int Temp = 0;
long Press = 0;
float Height = 0;


/*=========functions=========*/
/*
<<<<<<< HEAD
*initialize baro
*/
void baro_init() {

<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
 *initialize baro device
 */
void init_baro_hardware() {
  
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
  byte buff[TO_READ];
  int i=0;
  
  Wire.beginTransmission(BARO_ADDRESS);
  Wire.send(0xAA);
  Wire.endTransmission();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  
  Wire.beginTransmission(BARO_ADDRESS);
  Wire.requestFrom(BARO_ADDRESS, TO_READ);
  while(Wire.available()) {
    buff[i] = Wire.receive();
    i++;
  }
  
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

=======
  
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
  Wire.beginTransmission(BARO_ADDRESS);
  Wire.requestFrom(BARO_ADDRESS, TO_READ);
  while(Wire.available()) {
    buff[i] = Wire.receive();
    i++;
  }
<<<<<<< HEAD

<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
  
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
}

/*
 *
 */
struct baro_data read_baro_data() {
  
  calculate();
  barom.temp = Temp;
  barom.pressure = Press;
  barom.height = Height;
  
  return barom;
}

/*
 *write register
 */
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

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
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
}

/*
 *
 */
struct baro_data read_baro_data() {
  
  calculate();
  barom.temp = Temp;
  barom.pressure = Press;
  barom.height = Height;
  
  return barom;
}

/*
<<<<<<< HEAD
*write register
*/
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
 *write register
 */
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
void write_register(unsigned char r, unsigned char v) {
  Wire.beginTransmission(BARO_ADDRESS);
  Wire.send(r);
  Wire.send(v);
  Wire.endTransmission();
}
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

/*
 *read uncompensated temperature value
 */ 
=======
/*
*read uncompensated temperature value
*/ 
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
/*
*read uncompensated temperature value
*/ 
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======

/*
 *read uncompensated temperature value
 */ 
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
unsigned int read_temp() {
  
  write_register(0xF4,0x2E);
  delay(5);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  
=======

>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
  
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  
}

/*
 *read uncompensated pressure value
 */
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

=======
  
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
}

/*
<<<<<<< HEAD
*read uncompensated pressure value
*/
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
 *read uncompensated pressure value
 */
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
long read_press() {
  write_register(0xF4,0x34+(osrs<<6));
  delay(pwait_time[osrs]);
  
  unsigned char P_msb, P_lsb, P_xlsb;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  
=======

>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
  
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
  Wire.beginTransmission(BARO_ADDRESS);
  /*register to read*/
  Wire.send(0xF6);
  Wire.endTransmission();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  
=======

>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
  
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

/*
 *calculate the both true values of temp and pressure,
 *and get absolute height via pressure
 */
void calculate() {
  long x1, x2, x3, b3, b5, b6, p;
  unsigned long b4, b7;
  
  /*Standard atmospher in pascal*/
  const float p0 = 101325; 
  
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======

>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
/*
 *calculate the both true values of temp and pressure,
 *and get absolute height via pressure
 */
void calculate() {
  long x1, x2, x3, b3, b5, b6, p;
  unsigned long b4, b7;
<<<<<<< HEAD

<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
  
  /*Standard atmospher in pascal*/
  const float p0 = 101325; 
  
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
  int UT = read_temp();
  long UP = read_press();
  
  /*calculate the true temperature value*/
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  x1 = ((unsigned long)UT - ac6) * ac5 >> 15;
  x2 = ((long)mc << 11) / (x1 + md);
  b5 = x1 + x2;
  Temp = (b5 + 8) >> 4;  /*unit in 0.1 ℃*/
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
  x1 = ((long)UT - ac6) * ac5 >> 15;
  x2 = ((long)mc << 11) / (x1 + md);
  b5 = x1 + x2;
  Temp = (b5 + 8) >> 4;

<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
  x1 = ((unsigned long)UT - ac6) * ac5 >> 15;
  x2 = ((long)mc << 11) / (x1 + md);
  b5 = x1 + x2;
  Temp = (b5 + 8) >> 4;  /*unit in 0.1 ℃*/
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
  /*calculate the true pressure value*/
  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11;
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
  
  if (osrs == 3) {
    b3 = ((int32_t) ac1 * 4 + x3 + 2) << 1;
  }
  if (osrs == 2) {
    b3 = ((int32_t) ac1 * 4 + x3 + 2);
  }
  if (osrs == 1) {
    b3 = ((int32_t) ac1 * 4 + x3 + 2) >> 1;
  }
  if (osrs == 0) {
    b3 = ((int32_t) ac1 * 4 + x3 + 2) >> 2;
  }
  
<<<<<<< HEAD
=======
  b3 = (((int32_t) ac1 * 4 + x3) << osrs + 2) >> 2;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
  b3 = (((int32_t) ac1 * 4 + x3) << osrs + 2) >> 2;
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
  Press = p + ((x1 + x2 + 3791) >> 4);  /*unit in Pa*/
  
  /*Calculate the absolute height by read pressure */
  Height = -(44330 * (1-pow(Press/p0, 1.0/5.255)));  /*unit in meter*/
  
<<<<<<< HEAD
}
#endif
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
  Press = p + ((x1 + x2 + 3791) >> 4);

=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
}
#endif
<<<<<<< HEAD

    
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
