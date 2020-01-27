#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

int run = 1;

void print_date() {
  while(run) {
    fprintf(stdout, "[unix timestamp: %ld]\n", time(NULL));
    sleep(1);
  }
}

void print_name(char *n) {
  while(run) {
    fprintf(stdout, "name: %s\n", n);
    sleep(1);
  }
}

int main(int argc, char** argv) {

  pthread_t t;
  pthread_create(&t, NULL, (void*)print_date, NULL);


  pthread_t n;
  pthread_create(&n, NULL, (void*)print_name, argv[1] == NULL ? "george" : argv[1]);


  sleep(10);
  run = 0;

  pthread_join(t, NULL);
  pthread_join(n, NULL);

  return 0;
}