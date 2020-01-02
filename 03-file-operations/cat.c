#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

int main(int argc, char** argv) {

  if( argc < 2 ) {
    fprintf(stderr, "%s", "Supply at least one argument to be read!\n");
    return EXIT_FAILURE;
  }

  FILE * _f;
  _f = fopen(argv[1], "r");
  if ( _f == NULL ) {
    fprintf(stderr, "%s", "Can not read file!\n");
    return EXIT_FAILURE;
  }

  char buffer[BUFFER_SIZE];
  while( fgets(buffer, BUFFER_SIZE, _f) != NULL ) {
    fprintf(stdout, "%s", buffer);
  }


  fclose(_f);  
    
  return 0;
}
