#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  // Standard error (fd 2): unbuffered, meant for diagnostics; can be redirected separately with 2>
  fprintf(stderr, "stderr\n");
  // Standard output (fd 1): line buffered on a terminal, so the prompt without '\n' may appear late unless flushed
  fprintf(stdout, "Now enter an integer: ");
  int i = 0;
  // Standard input (fd 0): reads an integer from the keyboard or a pipe
  fscanf(stdin, "%d", &i);
  // The number typed becomes the exit status (only the low 8 bits are kept); check with 'echo $?'
  return i;
}