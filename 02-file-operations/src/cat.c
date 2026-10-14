#include <stdio.h>
#include <stdlib.h>

// Size of the line buffer; longer lines are read in several chunks
#define BUFFER_SIZE 128

int main(int argc, char** argv) {

  // Need a file name: argv[1]
  if( argc < 2 ) {
    fprintf(stderr, "%s", "Supply at least one argument to be read!\n");
    return EXIT_FAILURE;
  }

  FILE * _f;
  // Open for reading; returns NULL on failure (missing file, permission denied...)
  _f = fopen(argv[1], "r");
  if ( _f == NULL ) {
    fprintf(stderr, "%s", "Can not read file!\n");
    return EXIT_FAILURE;
  }

  // fgets reads at most BUFFER_SIZE-1 bytes and always null terminates
  char buffer[BUFFER_SIZE];
  while( fgets(buffer, BUFFER_SIZE, _f) != NULL ) {
    fprintf(stdout, "%s", buffer);
  }


  // Release the FILE and its underlying file descriptor
  fclose(_f);  
    
  return 0;
}
