/*!
 *  @file main.c
 *
 *  @brief main for server
 *
 *  @author Michal Musialik
 *  @date 2011-05-07
 * 
 */
#include "conn_tcpserver_main.h"

int main(void){
  conn_init();
  conn_run();
  return 0;
}
