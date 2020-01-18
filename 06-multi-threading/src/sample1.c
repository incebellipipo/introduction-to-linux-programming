#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void print_date() {
  fprintf(stdout, "[unix timestamp: %ld]: you see?\n", time(NULL));
}


int main(int argc, char** argv) {

  print_date();

  return 0;
}