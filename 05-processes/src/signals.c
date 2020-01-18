#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int caught_signal = 0;

void handle_sig(int sig) {
  if(sig == SIGINT) {
    fprintf(stdout, "[%lu]: cant stop me with: %d!\n", time(NULL), sig);
  } else if (sig == SIGQUIT) {
    fprintf(stdout, "[%lu]: cant stop me with: %d!\n", time(NULL), sig);
  } else {
    caught_signal = sig;
  }
}

int main(int argc, char* argv[]) {

  signal(SIGINT, handle_sig);
  signal(SIGQUIT, handle_sig);

  do {
    fprintf(stdout, "[%lu]: pid:%d\n", time(NULL), (int)getpid());
    sleep(1);
  } while(caught_signal == 0);
  
  fprintf(stdout, "[%lu]: you win, %d\n", time(NULL), caught_signal);


  return 0;
}