/*!
 * @file  panda_main.c 
 * @brief  Extended Scheduler Main file
 * @author Taher Odeh 
 */ 

#include <stdio.h>
#include "sched_ext_mngr.h"
#include <string.h>
#include "conn_tcpserver_main.h"
#include "cam_interface.h"
#include "nav_corelogic.h"

//#include "sched_proc_test.c" /* module 1 */
//#include "sched_proc_test2.c" /* module 2 */

int main(void){

  init_pool(&pool);
  
  /* create processes */
  struct extsched_proc p1 = create_proc(PROC_CONN, &conn_init, &conn_run); 
  struct extsched_proc p2 = create_proc(PROC_CAM, &cam_init, &cam_run);
  struct extsched_proc p3 = create_proc(PROC_NAV, &nav_init, &nav_run);

  /* initializes them and adds them to the poll */
  init_proc(&p1);
  init_proc(&p2);
  init_proc(&p3);
  
  printf("pool holds %d processes\n", pool->num_procs);
  
  /* run processes */
  run_pool(pool);

  /* free poll */
  free_pool(pool);

  return 0;
}
