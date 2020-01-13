#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

  unsigned char *_p;
  if( argc < 2) {
    _p = malloc(sizeof(unsigned char) * 16);
    strcpy(_p, "Hello world(?)\n");
  } else {
    long len = strlen(argv[1]);
    _p = malloc(sizeof(unsigned char) * (len + 1));
    fprintf(stdout, "[%p]: First pointer\n", _p);
    strcpy(_p, argv[1]);
    strcat(_p, "\n");

    _p = realloc(_p, (len + 1) * 3);
    fprintf(stdout, "[%p]: Pointer after realloc\n", _p);
    for(int i = 0 ; i < 2 ; i++) {
      strcat(_p, argv[1]);
      strcat(_p, "\n");
    }
  }
  for(unsigned char* p = _p ; *p != 0 ; p++) {
    fprintf(stdout, "%c", *p);
  }
  
  free(_p);

  return 0;
}