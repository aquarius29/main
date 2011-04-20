/***************************************************************************
 * @file read_rb.c
 * @brief Takes care of the communication with the barometer
 * @author Adam Debbiche   	       
 * @date 18/04/2011
 * @history
 *    18/04/2011: Initial version // Adam
 ***************************************************************************/
#ifdef ARDUINO
#include <Wire.h>
#include "WProgram.h"
#include "stab.h"

#define BARO_ADDRESS 0xEF
void read_baro_data();


void read_baro_data()
{
  //struct vector vect;
  byte buffer[22];
  int addr = 0xAA;
  read_stream(addr, 22, buffer);
  int i = 22;
  while (i<22)
    {
      Serial.println(buffer[i]);
      i++;
    }
  
}

#endif
