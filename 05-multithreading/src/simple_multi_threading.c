#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

// Flag telling the workers to stop (should be volatile/atomic in real code)
int run = 1;

// Worker 1: print the unix time every second
void print_date() {
  while(run) {
    fprintf(stdout, "[unix timestamp: %ld]\n", time(NULL));
    sleep(1);
  }
}

// Worker 2: receives its argument as a void* and prints it
void print_name(char *n) {
  while(run) {
    fprintf(stdout, "name: %s\n", n);
    sleep(1);
  }
}

int main(int argc, char** argv) {

  // Each pthread_create starts a thread running the given function with one argument
  pthread_t t;
  pthread_create(
      &t,
      NULL,
      (void*)print_date, NULL
  );

  pthread_t n;
  pthread_create(
      &n,
      NULL,
      (void*)print_name, argv[1] == NULL ? "george" : argv[1]
  );
 

  // Main thread lets the workers run for 10 seconds...
  sleep(10);
  // ...then asks them to stop
  run = 0;

  // Wait until each worker has returned
  pthread_join(t, NULL);
  pthread_join(n, NULL);

  return 0;
}
