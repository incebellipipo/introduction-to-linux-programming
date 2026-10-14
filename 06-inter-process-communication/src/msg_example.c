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
// NOTE: this adds sizeof(mtype) (so sends a little more than needed) and uses strlen so the '\0' is dropped
ssize_t msglen(msg m) {
  return sizeof(m.mtype) + sizeof(char) * strlen(m.mtext);
}

int main(int argc, char** argv) {

  // Create a System V message queue; IPC_PRIVATE = anonymous queue only reachable by related processes
  // 0600 = permissions
  int msgid = msgget(IPC_PRIVATE, 0600 | IPC_CREAT);
  if( msgid < 0) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }

  // Child is the sender; parent receives
  pid_t cpid = fork();
  if(cpid == 0) {
    msg m;
    // Message type: lets a receiver select messages (must be > 0)
    m.mtype = 42;
    strcpy(m.mtext, "All this time?\0");
    // Put the message in the queue; blocks if the queue is full
    if (msgsnd( msgid, &m, msglen(m), 0) < 0) {
      perror("msgsnd");
      exit(EXIT_FAILURE);
    }
    printf("sizeof: %lu\n",msglen(m));
    exit(EXIT_SUCCESS);
  }
  // Parent waits for the child so the message is surely queued
  wait(NULL);
  msg m;
  int r;
  // Receive the first message of type 42; returns the number of bytes in mtext
  // It blocks when no matching message exists
  if ( ( r = msgrcv(msgid, &m, BUFSIZ, 42, 0) ) < 0) {
    perror("msgrcv");
    exit(EXIT_FAILURE);
  }

  printf("bytes[%d]: %ld, %s\n", r, m.mtype, m.mtext);

  // Remove the queue; otherwise it persists in the kernel after the program exits (see 'ipcs -q' / 'ipcrm')
  if(msgctl(msgid, IPC_RMID, NULL) < 0) {
    perror("msgctl");
    exit(EXIT_FAILURE);
  } else {
    printf("Always...\n");
  }

  return 0;
}
