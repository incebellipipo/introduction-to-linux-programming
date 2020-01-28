#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/types.h>


int global_variable = 0;
pthread_mutex_t lock;


int is_prime(int n) {
	for(int i = 2 ; i <= n/2 ; i++) {
		if(n%i!=0)
			continue;
		else
			return 1;
	}
	return 0;;
}

void func() {
  pthread_mutex_lock(&lock);
  global_variable++;
  printf("Start func\t[%d]\n", global_variable);
  for(int i = 0 ; i < 100000 ; i++) {
    is_prime(i);
  }
  printf("End func\t[%d]\n", global_variable);
  pthread_mutex_unlock(&lock);
}

int main(int argc, char** argv) {

  if (pthread_mutex_init(&lock, NULL) != 0) { 
    printf("\n mutex init has failed\n"); 
    return EXIT_FAILURE; 
  } 

  int how_many = 2;
  pthread_t th[how_many];
  for(int i = 0 ; i < how_many; i++) {
    pthread_create(&(th[i]), NULL, (void*)func, 0);
  }
  for(int i = 0 ; i < how_many; i++) {
    pthread_join(th[i], NULL);
  }

  return 0;
} 