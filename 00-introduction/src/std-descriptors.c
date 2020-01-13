#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  fprintf(stderr, "stderr\n");
  fprintf(stdout, "Now enter an integer: ");
  int i = 0;
  fscanf(stdin, "%d", &i);
  return i;
}