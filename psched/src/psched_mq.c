
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <psched_mq.h>

#define KEY_DIR "/tmp"
#define PERM_FLAGS (IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int mq_init(key_t key){
  int id ;
  id = msgget(ftok(KEY_DIR, key), PERM_FLAGS );
  if ( id == -1){
    perror("msgget");
    return -1;
  }

  return id;
}

int mq_send(int qid, int type, char *msg){
  message_buf buf;
  buf.mtype= type;
  memcpy(&buf.mtext, msg, MSGSIZE);

  size_t len,buf_len = MSGSIZE; //sizeof(buf);
  //printf("trying to send: type=%d, size=%d, qid=%d\n", type, MSGSIZE, qid);
  len= msgsnd(qid, &buf, buf_len, IPC_NOWAIT);
  
  if (len == -1){
    perror("msgsnd");
    return -1;
  }

  //printf("Message sent...\n");
  return len;
}

size_t mq_recv(int qid, int type, char *msg){
  size_t len;
  message_buf *buf = malloc( MSGSIZE + sizeof(int));;
  //printf("trying to receive:: type=%d, size=%d, qid=%d\n", type, MSGSIZE, qid);
  len = msgrcv(qid, &buf, MSGSIZE, type, (MSG_NOERROR | IPC_NOWAIT ));
  printf("len received is %ld\n", len);
  if (len  == -1){ 
    perror("msgrcv");
    return -1;
  }

  memcpy(msg, buf->mtext, MSGSIZE);

  //printf("Message received (%ld): %s\n", len, msg);

  return len;
}

