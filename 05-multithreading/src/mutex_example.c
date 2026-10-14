#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/types.h>


// Shared state touched by every thread
int global_variable = 0;
// Mutex protecting the critical section in func()
pthread_mutex_t lock;


// Busy work to make the critical section take noticeable time
// NOTE: returns 1 when n is NOT prime (inverted) - the result is ignored anyway
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
  // Enter the critical section: other threads calling lock block here until it is released
  pthread_mutex_lock(&lock);
  global_variable++;
  printf("Start func\t[%d]\n", global_variable);
  for(int i = 0 ; i < 100000 ; i++) {
    is_prime(i);
  }
  printf("End func\t[%d]\n", global_variable);
  // Leave the critical section; always unlock on every path
  pthread_mutex_unlock(&lock);
}

int main(int argc, char** argv) {

  // Initialise the mutex with default attributes
  if (pthread_mutex_init(&lock, NULL) != 0) { 
    printf("\n mutex init has failed\n"); 
    return EXIT_FAILURE; 
  } 

  int how_many = 2;
  // Variable length array holding the thread handles
  pthread_t th[how_many];
  for(int i = 0 ; i < how_many; i++) {
    // Start the workers; with the mutex their Start/End lines never interleave
    pthread_create(&(th[i]), NULL, (void*)func, 0);
  }
  for(int i = 0 ; i < how_many; i++) {
    // Wait for each thread to finish before exiting
    pthread_join(th[i], NULL);
  }

  return 0;
} 