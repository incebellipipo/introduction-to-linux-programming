#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

  char buf[BUFSIZ] = {0};
  pid_t pid;
  // pipefd[0] is the read end, pipefd[1] the write end
  int pipefd[2];

  // Create the pipe before fork so both processes inherit both ends
  if(pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // First child writes a message into the pipe
  pid = fork();
  if(pid == 0) {
    char* msg = "Read this[0]!\0";
    printf("Child[0]: %s\n", msg);
    // Data flows child -> kernel buffer -> parent
    write(pipefd[1], msg, strlen(msg));
    exit(EXIT_SUCCESS);
  }
  // Wait for the child; then the data is already in the pipe so read will not block
  wait(NULL);
  // NOTE: the buffer is not cleared and the read length is not used, so a shorter second message could print leftover bytes
  read(pipefd[0], buf, BUFSIZ);
  printf("Parent reads: %s\n", buf);
  
  // Same exchange repeated with a second child over the same pipe
  pid_t pid2 = fork();
  if(pid2 == 0) {
    char* msg = "Read this[1]!\0";
    printf("Child[1]: %s\n", msg);
    write(pipefd[1], msg, strlen(msg));
    exit(EXIT_SUCCESS);
  }
  wait(NULL);
  read(pipefd[0], buf, BUFSIZ);
  printf("Parent reads: %s\n", buf);

  return 0;
}
