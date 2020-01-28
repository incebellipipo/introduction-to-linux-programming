#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

  char buf[BUFSIZ] = {0};
  pid_t pid;
  int pipefd[2];

  if(pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if(pid == 0) {
    char* msg = "Read this[0]!\0";
    printf("Child[0]: %s\n", msg);
    write(pipefd[1], msg, strlen(msg));
    exit(EXIT_SUCCESS);
  }
  wait(NULL);
  read(pipefd[0], buf, BUFSIZ);
  printf("Parent reads: %s\n", buf);
  
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
