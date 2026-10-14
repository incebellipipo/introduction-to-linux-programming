#include <stdio.h>

// main may take a third parameter, envp: a NULL-terminated array of "NAME=value" strings
// argc = number of arguments, argv = array of argument strings (argv[0] is the program name)
int main(int argc, char** argv, char **envp) {


  // envp is terminated by a NULL pointer, so iterate until we hit it
  fprintf(stdout, "Environment variables:\n");
  for(int i = 0; envp[i] != NULL; i++) {
    fprintf(stdout, "%s\n", envp[i]);
  }

  // argv has argc entries; argv[argc] is always NULL
  fprintf(stdout, "\nProgram arguments:\n");
  for(int i = 0; i < argc ; i++) {
    fprintf(stdout, "argv[%d]: %s\n", i, argv[i]);
  }

  // Exit status 0 means success; the shell sees it in $?
  return 0;
}