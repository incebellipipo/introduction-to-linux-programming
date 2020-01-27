#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#define EVER ;;

void* f3(void*);
void* f2(void*);
void* f1(void*);
void* (*fcaller[3])(void*) = {f1, f2, f3};

int i = 0;

int main(int argc, char** argv) {

  pthread_t th1, th2, th3;

  int arg;
  arg = 1;
  pthread_create(&th1, NULL, &f1, &arg );
  arg = 2;
  pthread_create(&th2, NULL, &f2, &arg );
  arg = 3;
  pthread_create(&th3, NULL, &f3, &arg );

  pthread_detach(th1);
  pthread_detach(th2);
  pthread_detach(th3);
 
  for(int k = 0; k < 10; k++) {
    printf("[.-`] ");
    for(int j = 0; j < i ; j++) {
      printf("-");
    } printf("\n");
    sleep(1);
  }

  return 0;
}


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
