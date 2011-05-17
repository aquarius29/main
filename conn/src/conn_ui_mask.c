/*!
 *  @file conn_mask_ui.c
 *
 *  @brief tcpclient file
 *
 *  @author Michal Musialik
 *  @date 2011-05-07
 *  @history    2011-04-15 - first outcast of conn_tcpclient.c file
 *  @history    2011-05-07 - changing to switch
 *  @history    2011-04-13 - adding nav functions
 *  
 */



#include "conn_ui_mask.h"
#include "conn_tcpserver.h"
#include "nav_corelogic.h"

/*
to nav
nav_SetMovmentIdentifier(int id); - send movment command from mask
nav_RunGPSSystem(double lat, double lon); - send lon lat to ui
nav_RunIndoorSystem(double startX,doublr,startY,double stopX, double, stopY); - 
from nav

nav_SendCurrentIndoorPosistionToGUI();
nav_SendCurrentOutdoorPositionToGUI();
nav_SendOutdoorPathToGUI();
nav_SendIdoorPathToGUI();


*/

#include <stdio.h>
#define DEBUG(x) printf("%s",x);

void controll_movement(int identifier){
  
  switch(identifier){
    
  case FORWARD:
    DEBUG("Going forward\n")
      nav_setMovementIdentifier(FORWARD);
    break;
    
  case BACK:
    DEBUG("Going back\n")
      nav_setMovementIdentifier(BACK);
    break;
    
  case LEFT:
    DEBUG("Going left\n")
      nav_setMovementIdentifier(LEFT);
    break;
    
  case RIGHT:
    DEBUG("Going right\n")
      nav_setMovementIdentifier(RIGHT);
    break;
    
  case UP:
    DEBUG("Going up\n")
      nav_setMovementIdentifier(UP);
    break;
    
  case DOWN:
    DEBUG("Going down\n")
      nav_setMovementIdentifier(DOWN);
    break;
    
  case LAND:
    DEBUG("land\n")
      nav_setMovementIdentifier(LAND);
    break;
    
  case TAKE_OFF:
    DEBUG("taking off\n")
      nav_setMovementIdentifier(TAKE_OFF);
    break;
    
  case KILL_INDOOR:
    DEBUG("kill indoor\n")
      //nav_killGPSSystem();
      break;
    
  case KILL_GPS:
    DEBUG("kill gps\n")
      // nav_killGPSSystem();
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

