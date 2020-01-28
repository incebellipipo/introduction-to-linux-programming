#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>
#include <string.h>

void aqcuire_sem() {

}

void release_sem() {

}

int main(int argc, char** argv){

  if(argc != 2) {
    fprintf(stderr, "Please pass semaphore operation\n");
    exit(EXIT_FAILURE);
  }

  int op = atoi(argv[1]);

  /*
   *  Semaphore stuff
   */
  key_t k = ftok("sem_example", 42);

  // Create sem if not created or acquire semaphore
  int semid = semget(k,1, 0666 | IPC_CREAT);
  if(semid < 0) {
    perror("semget");
    exit(EXIT_FAILURE);
  }

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

  struct sembuf operations[1];
  int retval;
  operations[0].sem_num = 0;
  operations[0].sem_flg = 0;
  operations[0].sem_op = op;
  int semval;
  semval = semctl(semid,0, GETVAL);
  printf("[%s] %ld, before sem: %d\n", argv[0], time(NULL), semval);
  if(op == 0) {
    printf("Waiting semaphore to be 0\n");
  }
  retval = semop(semid, operations, 1);
  if(retval < 0) {
    perror("semop");
  }
  semval = semctl(semid,0, GETVAL);
  printf("[%s] %ld, after sem: %d\n", argv[0], time(NULL), semval);

  return 0;
}
