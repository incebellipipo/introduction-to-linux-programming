#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {

  // Print our own command line
  for(int i = 0; i < argc ; i++) {
    fprintf(stdout, "%s ", argv[i]);
  } fprintf(stdout, "\n");

  // Replace this process with the command given in argv[1]...
  if (argc > 1) {
    execvp(argv[1], argv+1);
  }

  // ...so this line runs only when exec failed or no command was given
  printf("You shouldn't see me!\n");

  return 0;   
}