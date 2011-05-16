#include <sys/ipc.h>
#include <sys/msg.h> 
#include <unistd.h>

#define MSGSIZE 5 /* 5 bytes messages allowed */

typedef struct msgbuf {
  long    mtype;
  char    mtext[MSGSIZE];
} message_buf;

int mq_init(key_t);
int mq_send(int, int, char *);
size_t mq_recv(int, int, char *);
