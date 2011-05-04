#define SLEEPT 500*1000

int init2();
int run2();

int init2(){
  printf("initialized module 2...\n");
  return 1;
}

int run2(){
  
  size_t sndlen;
  int i=0;
  int res;
  char buff[SHM_PROC_SIZE];

  while(1){
    printf("module 2: running...\n");
    usleep(SLEEPT);
    i++;
    if ( (i%4) == 0) { 
      /* send a message every 4 iterations */
            
      /* writing to UI process */
      strncpy(buff, "Hello UI", SHM_PROC_SIZE);
      res= proc_write_state(PROC_UI, buff);

      /* writing to NAV process */
      strncpy(buff, "Hello NAV", SHM_PROC_SIZE);
      res= proc_write_state(PROC_NAV, buff);

      printf("- Writing data to ui and nav...\n");

    }
  }
  
  return 1;
}
