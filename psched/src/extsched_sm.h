/*! * * * * * * * * * * * * * * * * * *
 * @file sched_sm.c
 * @brief Extended Sheduler shared \n
 *         memory library based on IPC.
 * @date 2011-05-04
 * @author Taher Odeh
 * @version 1.1
 * * * * * * * * * * * * * * * * * * * */

#include "proc_types.h"
#include <unistd.h>

#define SHM_KEY 1234 /* semaphore key id */
#define NUM_PROCS 2 /* number of processes in the poll */
#define SHM_PROC_SIZE 10 /* bytes to allocate for each process in the shred memory area */
#define SHM_SIZE SHM_PROC_SIZE*NUM_PROCS /* shared memory allocated in bytes */

/* creates the ipc shared memory space 
   return: (int) shmid - shared memory id.
 */
int sm_create(void);

/* reads data from the shared memory allocated 
   for a specific process and stores in the buffer passed.
   return: length of data read.
*/
size_t sm_read(int, enum proc_type, char *);

/* writes data to the shared memory allocated 
   for a specific process 
   return: length of data written (bytes).
*/
size_t sm_write(int, enum proc_type, char *);
