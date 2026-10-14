#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

// Set from the handler, polled from main
int caught_signal = 0;

// Signal handler: called asynchronously when a registered signal is delivered
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

  // Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT) no longer terminate the process
  // SIGKILL and SIGSTOP can never be caught
  signal(SIGINT, handle_sig);
  signal(SIGQUIT, handle_sig);

  // Print the pid so it can be signalled from another terminal (kill -TERM <pid>)
  do {
    fprintf(stdout, "[%lu]: pid:%d\n", time(NULL), (int)getpid());
    sleep(1);
  // Any signal other than INT/QUIT recorded in caught_signal ends the loop
  } while(caught_signal == 0);
  
  fprintf(stdout, "[%lu]: you win, %d\n", time(NULL), caught_signal);


  return 0;
}