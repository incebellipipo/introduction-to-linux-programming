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
int stop = 1;

void sighandle(int sig) {
  stop = 0;
}

int main(int argc, char** argv) { 

  signal(SIGINT, sighandle);

  key_t k = ftok("shmfile", 42);
  pid_t pid = fork();

  if(pid == 0) {
    int shmid = shmget(k, BUFSIZ, 0666 | IPC_CREAT);
    int *t = shmat(shmid, NULL, 0);
    do {
      *t = time(NULL);
      sleep(1);
    } while(stop);
    fprintf(stdout, "\nCHILD EXITS!\n");
    shmdt(t);
    exit(EXIT_SUCCESS);
  }
  cpid = pid;

  int shmid = shmget(k, BUFSIZ, 0666 | IPC_CREAT);
  time_t *tp = shmat(shmid, NULL, 0);
  char buf[128];
  do {
    struct tm ts;
    ts = *localtime(tp);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    fprintf(stdout, "%s\n", buf);
    sleep(1);
  } while(stop);
  kill(cpid, SIGINT);
  wait(NULL);
  fprintf(stdout, "\nPARENT EXITS!\n");
  return 0;
} 