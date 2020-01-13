#include <stdio.h>

int main(int argc, char** argv, char **envp) {


  fprintf(stdout, "Environment variables:\n");
  for(int i = 0; envp[i] != NULL; i++) {
    fprintf(stdout, "%s\n", envp[i]);
  }

  fprintf(stdout, "\nProgram arguments:\n");
  for(int i = 0; i < argc ; i++) {
    fprintf(stdout, "argv[%d]: %s\n", i, argv[i]);
  }

  return 0;
}