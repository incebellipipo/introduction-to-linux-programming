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

// Size of the payload: msgsnd's size argument excludes the leading mtype field
// NOTE: this adds sizeof(mtype) and drops the '\0'
ssize_t msglen(msg m) {
  return sizeof(m.mtype) + sizeof(char) * strlen(m.mtext);
}

int main(int argc, char** argv) {

  // Derive a System V IPC key from an existing path and a project id; sender and receiver must use the same pair
  // NOTE: the file "msq_example" must exist (relative to cwd) - note the spelling in the file name
  key_t k = ftok("msq_example", 42);

  // Open the queue for that key, creating it if needed (unrelated processes can now share it)
  int msgid = msgget(k, 0600 | IPC_CREAT);
  if( msgid < 0) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }

  msg m;
  int r;
  // Block until a message of type 42 arrives
  if ( ( r = msgrcv(msgid, &m, BUFSIZ, 42, 0) ) < 0) {
    perror("msgrcv");
    exit(EXIT_FAILURE);
  }

  printf("bytes[%d]: %ld, %s\n", r, m.mtype, m.mtext);

  // The receiver removes the queue after consuming the message
  if(msgctl(msgid, IPC_RMID, NULL) < 0) {
    perror("msgctl");
    exit(EXIT_FAILURE);
  } else {
    printf("Always...\n");
  }

  return 0;
}
