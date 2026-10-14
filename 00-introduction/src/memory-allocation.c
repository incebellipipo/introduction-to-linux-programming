#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

  // Pointer to a heap buffer, filled differently depending on whether an argument was given
  unsigned char *_p;
  if( argc < 2) {
    // No argument: 16 bytes = 15 characters + terminating '\0'
    _p = malloc(sizeof(unsigned char) * 16);
    strcpy(_p, "Hello world(?)\n");
  } else {
    // Argument given: size the buffer from the input (+1 for the '\0')
    long len = strlen(argv[1]);
    _p = malloc(sizeof(unsigned char) * (len + 1));
    // Print the address so it can be compared with the one after realloc
    fprintf(stdout, "[%p]: First pointer\n", _p);
    strcpy(_p, argv[1]);
    // Buffer is exactly len+1 bytes, so this append overflows by one byte (the '\n' and '\0' do not fit)
    // Counting the extra '\n' is why the realloc below is needed, and why sizes must be computed carefully
    strcat(_p, "\n");

    // Grow the block to hold the string three times; realloc may move it, so always assign the result
    // (address printed next may differ from the first one)
    _p = realloc(_p, (len + 1) * 3);
    fprintf(stdout, "[%p]: Pointer after realloc\n", _p);
    for(int i = 0 ; i < 2 ; i++) {
      strcat(_p, argv[1]);
      strcat(_p, "\n");
    }
  }
  // Walk the string byte by byte until the terminator
  for(unsigned char* p = _p ; *p != 0 ; p++) {
    fprintf(stdout, "%c", *p);
  }
  
  // Every malloc needs exactly one free; the pointer must not be used afterwards
  free(_p);

  return 0;
}