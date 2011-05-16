/*!
 * @file  schedext_example_usage.c
 * @brief  Example usage of the extended scheduler library\n
 *  and IPC shared memory.
 * @author Taher Odeh 
 */ 

#include <stdio.h>
#include "sched_ext_mngr.h"
#include <string.h>

#include "sched_proc_test.c" /* module 1 */
#include "sched_proc_test2.c" /* module 2 */

int main(void){

  init_pool(&pool);
  
  /* create processes */
  struct extsched_proc p1 = create_proc(1, &init1, &run1); 
  struct extsched_proc p2 = create_proc(2, &init2, &run2);

  /* initializes them and adds them to the poll */
  init_proc(&p1);
  init_proc(&p2);
  
  printf("pool holds %d processes\n", pool->num_procs);
  
  /* run processes */
  run_pool(pool);

  /* free poll */
  free_pool(pool);

  return 0;
}
