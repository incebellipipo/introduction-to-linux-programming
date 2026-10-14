#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Global variable: after fork each process has its own copy (copy-on-write), not shared memory
int common_ground = 0;

int main(int argc, char** argv) {

  // Create the child ('slave')
  pid_t pid = fork();
  if( pid < 0 ) {
    perror("Fork");
    exit(EXIT_FAILURE);
  }

  if(pid == 0) {
    // Only the child's copy changes; the parent will still print 0
    common_ground++;
    fprintf(stderr, "slave[%d]: common_ground: %d\n", (int)getpid(), common_ground);
    // exec replaces the child's program image with argv[1], keeping the pid; v = argument vector, p = search PATH
    // It only returns on failure
    if(execvp(argv[1], argv+1)) {
      fprintf(stderr, "slave[%d]: no can do!: %s\n", (int)getpid(), strerror(errno));
    }
    // Reached only if exec failed
    exit(EXIT_FAILURE);
  }

  // Parent waits for the slave to finish
  wait(NULL);
  fprintf(stdout, "master[%d]: common ground: %d\n", (int)getpid(), common_ground);
  fprintf(stdout, "master[%d]: i did nothing!\n", (int)getpid());

  return 0;
}