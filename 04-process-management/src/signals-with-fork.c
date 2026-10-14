#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>

// Shared flag: the handler flips it, the main loop observes it
// Strictly it should be 'volatile sig_atomic_t'
int run = 1;
pid_t cpid;
int signal_to_handle;

// Runs in the child when the chosen signal arrives, and ends its loop
void child_signal_handler(int sig) {
  printf("[child] Signal[%d] recieved to pid: [%d]\n", sig, getpid());
  run = 0;
}

// Parent forwards the signal to the child with kill()
// NOTE: printf is not async-signal-safe; fine for a demo, avoid in real handlers
void parent_signal_handler(int sig) {
  kill(cpid, signal_to_handle);
  printf("[parent] Signal[%d] recieved to pid: [%d]\n", sig, getpid());
}


int main(int argc, char** argv) {
  
  if( argc != 2 ){
    fprintf(stderr, "I need args!\n");
    return EXIT_FAILURE;
  }

  // Signal number comes from the command line (e.g. 2 = SIGINT, 10 = SIGUSR1)
  signal_to_handle = atoi(argv[1]);  
  
  // Create the child
  cpid = fork();
  if(cpid < 0) {
    perror("error");
    exit(EXIT_FAILURE);
  }
  
  if(cpid == 0){
    // Install the handler in the child
    signal(signal_to_handle, child_signal_handler);
    // Work loop, runs until the signal arrives
    while(run) {
      printf("Epoch time: %lu\n", (unsigned long) time(NULL));
      sleep(1);
    }
    // After the handler fired, print the parent pid: if the parent died, this becomes 1 (adopted by init)
    for(int i = 0 ; i < 50 ; i++) {
      printf("ppid: %d\n", getppid());
      sleep(1);
    }
    printf("Child exits!\n");
    exit(EXIT_SUCCESS);
  }

  // Parent: Ctrl+C is intercepted and forwarded to the child instead of killing the parent
  signal(SIGINT, parent_signal_handler);
  wait(NULL);
  printf("Parent exits!\n");

  return 0;
}

