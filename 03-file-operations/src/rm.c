#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv) {

  if(argc == 2) {
    if(remove(argv[1]) != 0) {
      perror("remove");
    }
  } else {
    fprintf(stderr, "I need args!\n");
  }
  
  return 0;
}
