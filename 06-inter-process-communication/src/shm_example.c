#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <sys/wait.h>

pid_t cpid;
// Loop flag cleared by the SIGINT handler (Ctrl+C reaches both parent and child)
int stop = 1;

void sighandle(int sig) {
  stop = 0;
}

int main(int argc, char** argv) { 

  // Install before fork so the child inherits it too
  signal(SIGINT, sighandle);

  // IPC key derived from a file + project id (the file "shmfile" must exist)
  key_t k = ftok("shmfile", 42);
  // Child writes into shared memory, parent reads
  pid_t pid = fork();

  if(pid == 0) {
    // Get/create a shared memory segment of BUFSIZ bytes
    int shmid = shmget(k, BUFSIZ, 0666 | IPC_CREAT);
    // Attach the segment into this process' address space; writes are visible to all attached processes
    int *t = shmat(shmid, NULL, 0);
    do {
      // Publish the current time (stored as int, read back as time_t by the parent)
      *t = time(NULL);
      sleep(1);
    } while(stop);
    fprintf(stdout, "\nCHILD EXITS!\n");
    // Detach the segment from this process (does not destroy it)
    shmdt(t);
    exit(EXIT_SUCCESS);
  }
  // Parent: remember the child pid
  cpid = pid;

  int shmid = shmget(k, BUFSIZ, 0666 | IPC_CREAT);
  // Parent attaches the same segment
  time_t *tp = shmat(shmid, NULL, 0);
  char buf[128];
  do {
    struct tm ts;
    // Read the child's timestamp and format it
    ts = *localtime(tp);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    fprintf(stdout, "%s\n", buf);
    sleep(1);
  } while(stop);
  // Tell the child to stop, then wait for it
  kill(cpid, SIGINT);
  wait(NULL);
  fprintf(stdout, "PARENT EXITS!\n");

  fprintf(stdout, "Removing shared memory for clean exit\n");

  // Mark the segment for removal; otherwise it leaks until reboot or 'ipcrm'
  shmctl(shmid, IPC_RMID, 0);

  return 0;
} 