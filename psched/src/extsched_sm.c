/*! * * * * * * * * * * * * * * * * * *
 * @file extsched_sm.c
 * @brief Extended Sheduler shared \n
 *         memory library based on IPC.
 * @date 2011-05-04
 * @author Taher Odeh
 * @version 1.1
 * * * * * * * * * * * * * * * * * * * */

#include "extsched_sm.h"
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
void _shm_debug(char *txt){
  fprintf(stderr," --- %s --- \n", txt);
}
#else 
void _shm_debug(char *);
#endif 

/*
int main(void){
  int shmid ;
  shmid = sm_create();
  char *buff = malloc( SHM_PROC_SIZE );;
  int len; 

  sm_write(shmid, PROC_UI, "datas");
  
  len =sm_read(shmid, PROC_UI, buff);

  printf("Data read: %s\n", buff);
}
*/

/* creates the ipc shared memory space 
   return: (int) shmid - shared memory id.
 */
int sm_create()
{
  int shmid; /* shared memory id */
  
  if ((shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666)) < 0){
    perror("shmget");
    return -1;
  }
  
  _shm_debug("SHM Initialized..");
  
  return shmid;
}

/* writes data to the shared memory allocated 
   for a specific process.
   shmid: shared memory id.
   type: process id.
   data: data to write.
   return: length of data written (bytes).
*/
size_t sm_write(int shmid, enum proc_type type, char *data){
  char *shp, *shpt;
  int i;
  int len = strlen(data);

  printf("writing...\n");

  if (len > SHM_PROC_SIZE) { 
    /* data is too long  */
    return -1 ;
  }

  /* map shared memory. */
  if ((shp = shmat(shmid, NULL, 0)) == (char *) -1){
    perror("shmat");
    return -1;
  }

  shpt= shp; /* copy shp address to call shmdt on */

  for (i=0; i< SHM_PROC_SIZE* (((int)type)-1); i++) {
    /* skip to the specific process' area in memory */
    shp++;
  }

  printf("Data written to %p : ", shp);

  for (i=0; i< len; i++){
    /* write data to shared memory*/
    *shp++ = data[i];
  }
  
  printf("%s\n", data);

  /* unmap shared memory */
  if (shmdt(shpt) == -1){
    perror("shdmt");
    return -1;
  }

  return len;
}

/* reads data from the shared memory allocated 
   for a specific process and stores in the buffer passed.
   shmid: shared memory id
   type: process id
   buff: buffer
   return: length of data read.
*/
size_t sm_read(int shmid, enum proc_type type, char *buff){
  char *shp, *shpt;
  int i;

  printf("reading...\n");

  if ((shp = shmat(shmid, NULL, 0)) == (char *) -1){
    perror("shmat");
    return -1;
  }

  shpt= shp;

  for (i=0; i< SHM_PROC_SIZE*((int)type-1); i++) {
    shp++;
  }
  
  for (i=0; i< SHM_PROC_SIZE && shp!=(char *)NULL; i++){
    /* copy shared memory data into buff */
    *buff = *shp;
    shp++;
    buff++;
  }
  //*buff = '\0';

  if (shmdt(shpt) == -1){
    perror("shdmt");
    return -1;
  }

  
  return i;
}
