#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {

  for(int i = 0; i < argc ; i++) {
    fprintf(stdout, "%s ", argv[i]);
  } fprintf(stdout, "\n");

  if (argc > 1) {
    execvp(argv[1], argv+1);
  }

  printf("You shouldn't see me!\n");

  return 0;   
}