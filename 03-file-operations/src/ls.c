#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


int main(int argc, char** argv) {

  DIR *_d;
  struct dirent *_dir;
  
  char* directory = ".";
  if ( argc < 2 ) {
    _d = opendir(directory);
  } else {
    _d = opendir(argv[1]);
  }

  if ( _d != NULL ) {
    while ((_dir = readdir(_d)) != NULL) {
      fprintf(stdout, "%s\n", _dir->d_name);
    }
    closedir(_d);
  }

  return 0;
}
