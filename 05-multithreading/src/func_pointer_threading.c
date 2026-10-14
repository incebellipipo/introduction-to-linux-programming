#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
// Macro trick: for(EVER) expands to for(;;), an infinite loop
#define EVER ;;

void* f3(void*);
void* f2(void*);
void* f1(void*);
// Thread functions must have the signature void* f(void*); array of such pointers (unused here)
void* (*fcaller[3])(void*) = {f1, f2, f3};

// Global shared by all threads: no synchronisation, so this is a data race (on purpose, it is a demo)
int i = 0;

int main(int argc, char** argv) {

  pthread_t th1, th2, th3;

  // NOTE: the same variable's address is passed to all threads and then changed; threads may read the later value
  // Use separate variables to be safe
  int arg;
  arg = 1;
  // Starts f1 in a new thread: (thread handle, attributes, start routine, argument)
  pthread_create(&th1, NULL, &f1, &arg );
  arg = 2;
  pthread_create(&th2, NULL, &f2, &arg );
  arg = 3;
  pthread_create(&th3, NULL, &f3, &arg );

  // Detached threads free their resources on their own and cannot be joined
  pthread_detach(th1);
  pthread_detach(th2);
  pthread_detach(th3);
 
  // Main thread displays the shared counter once a second; when main returns the process (and all threads) end
  for(int k = 0; k < 10; k++) {
    printf("[.-`] ");
    for(int j = 0; j < i ; j++) {
      printf("-");
    } printf("\n");
    sleep(1);
  }

  return 0;
}


// Each worker modifies the shared counter at its own rate (sleep for *s seconds)
void* f3(void* s) {
  while(1) {
    i++;
    printf("[--+] hello from f3\n");
    sleep(*(int*)s);
  }
}

void* f2(void* s) {
  for(;;) {
    i = sqrt(i);
    printf("[-+-] hello from f2\n");
    sleep(*(int*)s);
  }
}

void* f1(void* s) {
  for(EVER) {
    i*=i;
    printf("[+--] hello from f1\n");
    sleep(*(int*)s);
  }
}
