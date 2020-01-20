#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

  pid_t pid;
  int pipefd[2];
  int ret;

  ret = pipe(pipefd);

  if(ret == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  char* msg = "Read this!\0";
  if(pid == 0) {
    printf("Child: %s\n", msg);
    write(pipefd[1], msg, strlen(msg));
    exit(EXIT_SUCCESS);
  }
  wait(NULL);
  char buf[1024] = {0};
  read(pipefd[0], buf, 1024);
  printf("Parent hears: %s\n", buf);



  return 0;
}