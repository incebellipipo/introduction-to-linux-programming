#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[]) {

  char* INBUF = (char*)malloc(BUFSIZ);

  do{
    fprintf(stdout, "$ ");
    fgets(INBUF, BUFSIZ, stdin);
    pid_t pid = fork();
    if(pid == 0) {
      system(INBUF);
      exit(EXIT_SUCCESS);
    }

    wait(NULL);

  } while(1);

  free(INBUF);

  return 0;
}