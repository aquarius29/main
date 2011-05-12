#include "conn_ui_mask.h"

void controll_movement(int identifier){
 
  switch(identifier){

  case FORWARD:
  printf("Going forward\n");
  break;
  
case BACK:
  printf("Going back\n");
  break;
  
case LEFT:
  printf("Going left\n");
  break;
  
case RIGHT:
  printf("Going right\n");
  break;
  
case UP:
  printf("Going up\n");
  break;
  
case DOWN:
  printf("Going down\n");
  break;
  
case LAND:
  printf("land\n");
  break;
  
case TAKE_OFF:
  printf("taking off\n");
  break;

case KILL_INDOOR:
  printf("kill indoor\n");
  break;
  
case KILL_GPS:
  printf("kill gps\n");
  break;
  
case KILL_SERVER:
  printf("kill server\n");
  break;

case START_CAMERA:
  printf("starting camera\n");
  break;

case START_INDOOR_PATH:
  printf("start indoor path\n");
  break;

case START_OUTDOOR_PATH:
  printf("start outdoor path\n");
  break;

case INDOOR_POSITION:
  printf("indoor position\n");
  break;

case OUTDOOR_POSITION:
  printf("outdoor position\n");
  break;


  }
  
}

