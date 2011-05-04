
/*! @author Elnaz Shahmehr
 * @file proto_interface.c
 * @version v0.01
 * @date 2011-04-20
 * @brief Contains the implementations of proto_init and proto_run
 */



#include "proto_lib.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef ARDUINO
//************************************************************
// ARDUINO
// All proto preperation goes here.
//************************************************************
int proto_init()
{
  

  return 1;
}


//************************************************************
// ARDUINO
// proto is started here
//************************************************************
int proto_run()
{
  

  return 1;

}
#endif



#ifdef PC
//************************************************************
// PC
//  All proto preperation goes here.
//************************************************************
int proto_init()
{
  

  return 1;

}

//************************************************************
// PC
// proto is started here
//************************************************************
int proto_run()
{


  return 1;
}
#endif
