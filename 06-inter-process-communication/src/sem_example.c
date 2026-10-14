#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>
#include <string.h>

// Placeholders, not implemented (the operations are done inline in main)
void aqcuire_sem() {

}

void release_sem() {

}

int main(int argc, char** argv){

  if(argc != 2) {
    fprintf(stderr, "Please pass semaphore operation\n");
    exit(EXIT_FAILURE);
  }

  // Semaphore operation from the command line: >0 release, <0 acquire (may block), 0 wait until the value is 0
  int op = atoi(argv[1]);

  /*
   *  Semaphore stuff
   */
  // Key derived from an existing file + project id so that every invocation reaches the same semaphore
  key_t k = ftok("sem_example", 42);

  // Create sem if not created or acquire semaphore
  // Get (or create) a set of 1 semaphore with rw-rw-rw- permissions
  int semid = semget(k,1, 0666 | IPC_CREAT);
  if(semid < 0) {
    perror("semget");
    exit(EXIT_FAILURE);
  }

// Disabled initialisation: SETVAL would set the semaphore's initial value (new semaphores start at 0)
#ifdef asdf
  int arg = 0;
  if (semctl(semid, 0, SETVAL,arg) < 0) {
    perror("semctl");
    exit(EXIT_FAILURE);
  }
#endif


  printf("Semaphore[%d] initialized\n", semid);


  /*
   *  Using semaphores for critical section problem
   */

  // One semaphore operation: which semaphore (sem_num), what to do (sem_op) and flags
  struct sembuf operations[1];
  int retval;
  operations[0].sem_num = 0;
  operations[0].sem_flg = 0;
  operations[0].sem_op = op;
  int semval;
  // Read the current value for display
  semval = semctl(semid,0, GETVAL);
  printf("[%s] %ld, before sem: %d\n", argv[0], time(NULL), semval);
  if(op == 0) {
    printf("Waiting semaphore to be 0\n");
  }
  // Atomically apply the operation; a negative op blocks until the value is large enough
  // Try running with -1 in one terminal and 1 in another
  retval = semop(semid, operations, 1);
  if(retval < 0) {
    perror("semop");
  }
  semval = semctl(semid,0, GETVAL);
  printf("[%s] %ld, after sem: %d\n", argv[0], time(NULL), semval);

  return 0;
}
