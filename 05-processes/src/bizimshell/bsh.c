#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <bizimshell/bsh.h>

int main(int argc, char* argv[], char* envp[]) {

  INBUF = (char*)malloc(INBUFSIZ);

  do{
    fprintf(stdout, "$ ");
    fgets(INBUF, INBUFSIZ, stdin);
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