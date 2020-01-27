#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>

/*
 * This struct must be in form of msgbuf referenced
 * in man msgget
 */
typedef struct msg {
  long mtype;
  char mtext[BUFSIZ];
} msg;

ssize_t msglen(msg m) {
  return sizeof(m.mtype) + sizeof(char) * strlen(m.mtext);
}

int main(int argc, char** argv) {

  key_t k = ftok("msq_example", 42);

  int msgid = msgget(k, 0600 | IPC_CREAT);
  if( msgid < 0) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }

  msg m;
  m.mtype = 42;
  strcpy(m.mtext, "All this time?\0");
  if (msgsnd( msgid, &m, msglen(m), 0) < 0) {
    perror("msgsnd");
    exit(EXIT_FAILURE);
  }
  printf("sizeof: %lu\n",msglen(m));
  
  return 0;
}
