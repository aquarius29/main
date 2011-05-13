#include "sched_ext_mngr.h"
#include "sched_proc_test.c"
#include "sched_proc_test2.c"

/* Set up and clean up test suite */

int init_suite(void) {
  return pool;
}

int clean_suite(void) {
  free_pool(pool);
  pool=NULL;
  return 0;
}

void test_psched_initpool()
{
  init_pool(&pool);
  CU_ASSERT(pool!=NULL);
}

void test_psched_addproc()
{
  init_pool(&pool);

  struct extsched_proc proc = create_proc(1, &init, &run);
  struct extsched_proc proc2 = create_proc(2, &init, &run);
  
  init_proc(&proc);
  CU_ASSERT(pool->num_procs==1);
  init_proc(&proc2);
  CU_ASSERT(pool->num_procs==2);  
}

void test_psched_run()
{
  init_pool(&pool);  

  struct extsched_proc *p;
  struct sched_pool *tp = pool;

  struct extsched_proc proc = create_proc(1, &init, &run);
  struct extsched_proc proc2 = create_proc(2, &init2, &run2);
  
  init_proc(&proc);
  init_proc(&proc2);

  while (tp !=NULL){
    p = pool->p;
    CU_ASSERT(p->running==0);
    tp = pool->next_proc;
  }
}
