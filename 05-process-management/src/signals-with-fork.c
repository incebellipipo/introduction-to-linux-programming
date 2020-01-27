#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>

int run = 1;
pid_t cpid;
int signal_to_handle;

void child_signal_handler(int sig) {
  printf("[child] Signal[%d] recieved to pid: [%d]\n", sig, getpid());
  run = 0;
}

void parent_signal_handler(int sig) {
  kill(cpid, signal_to_handle);
  printf("[parent] Signal[%d] recieved to pid: [%d]\n", sig, getpid());
}


int main(int argc, char** argv) {
  
  if( argc != 2 ){
    fprintf(stderr, "I need args!\n");
    return EXIT_FAILURE;
  }

  signal_to_handle = atoi(argv[1]);  
  
  cpid = fork();
  if(cpid < 0) {
    perror("error");
    exit(EXIT_FAILURE);
  }
  
  if(cpid == 0){
    signal(signal_to_handle, child_signal_handler);
    while(run) {
      printf("Epoch time: %lu\n", (unsigned long) time(NULL));
      sleep(1);
    }
    for(int i = 0 ; i < 50 ; i++) {
      printf("ppid: %d\n", getppid());
      sleep(1);
    }
    printf("Child exits!\n");
    exit(EXIT_SUCCESS);
  }

  signal(SIGINT, parent_signal_handler);
  wait(NULL);
  printf("Parent exits!\n");

  return 0;
}

