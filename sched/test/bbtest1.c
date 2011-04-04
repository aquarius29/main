#include "CUnit/Basic.h"

#include "../src/scheduler.h"


/* Set up and clean up test suite */

int init_suite(void) {
  pp = createProcess(name); 
  return calc == NULL;
}

int clean_suite(void) {
  freeCalcState(calc);
  calc=NULL;
  return 0;
}

void testSched1(void) {

  char name = "Justin";

  
  CU_ASSERT(pp->name, name);
}
