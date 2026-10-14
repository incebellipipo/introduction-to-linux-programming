#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Code that only the child runs; it terminates the child with exit()
void do_what_a_child_will_do(char* a) {
  fprintf(stdout, "%s[%d]: Hi mother!\n", a, (int)getpid());
  exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {

  // fork duplicates the process. It returns twice:
  //   < 0 in the parent on error, 0 in the child, the child's pid in the parent
  pid_t pid = fork();
  if( pid < 0 ) {
    perror("Fork");
    exit(EXIT_FAILURE);
  }

  // Child branch
  if(pid == 0) {
    do_what_a_child_will_do(argv[0]); 
  }

  // Parent only: block until the child terminates (prevents a zombie)
  wait(NULL);
  fprintf(stdout, "%s[%d]: Hello son!\n", argv[0], (int)getpid());

  return 0;
}