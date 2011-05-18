/*!
 *  @file conn_mask_ui.c
 *
 *  @brief tcpclient file
 *
 *  @author Michal Musialik
 *  @date 2011-05-07
 *  @history    2011-05-07 - changing to switch
 *  @history    2011-05-13 - adding nav functions
 *  
 *
 *  Description:
 *  This a mask that after receiving a value from the server,
 *  do a selection by using a switch.
 */

#include "conn_ui_mask.h"
#include <stdio.h>
#include "conn_tcpserver.h"
/*

#include "port_test.c"
#include "proto_serial_port.h"
#include "proto_serial_comm.h"

static int32_t portHandle;

uint8_t alt_up  = 0x01;
uint8_t alt_down = 0x02;
uint8_t back  = 0x03;
uint8_t forward  = 0x04;
uint8_t left  = 0x05;
uint8_t right  = 0x06;
uint8_t hover = 0x07;
uint8_t land  = 0x08;
*/

void controll_movement(int identifier){
  // portHandle = proto_serialOpen();
  switch(identifier){

  case FORWARD:
  DEBUG("Going forward\n")
    // proto_serialSendUICommandMsg(portHandle, forward);
  break;
  
case BACK:
  DEBUG("Going back\n")
    // proto_serialSendUICommandMsg(portHandle, back);
  break;
  
case LEFT:
  DEBUG("Going left\n")
    // proto_serialSendUICommandMsg(portHandle, left);
  break;
  
case RIGHT:
  DEBUG("Going right\n")
    //proto_serialSendUICommandMsg(portHandle,right);
  break;
  
case UP:
  DEBUG("Going up\n")
    //proto_serialSendUICommandMsg(portHandle,alt_up);
  break;
  
case DOWN:
  DEBUG("Going down\n")
    //proto_serialSendUICommandMsg(portHandle,alt_down);
  break;
  
case LAND:
  DEBUG("land\n")
    //proto_serialSendUICommandMsg(portHandle,land);
  break;
  
case TAKE_OFF:
  DEBUG("taking off\n")
    //proto_serialSendUICommandMsg(portHandle,hover);
  break;

case KILL_INDOOR:
  DEBUG("kill indoor\n")
 
  break;
  
case KILL_GPS:
  DEBUG("kill gps\n")
 
  break;
  
  case KILL_SERVER:
  DEBUG("kill server\n")
    break;
  
  case START_CAMERA:
    DEBUG("starting camera\n")
   
    break;
  
case START_INDOOR_PATH:
  DEBUG("start indoor path\n")
  
  break;

case START_OUTDOOR_PATH:
  DEBUG("start outdoor path\n")
  break;

case INDOOR_POSITION:
  DEBUG("indoor position\n")
  break;

case OUTDOOR_POSITION:
  DEBUG("outdoor position\n")
  break;


  }
  
}

