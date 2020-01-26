#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// man 7 inode
// man 2 stat

int main(int argc, char** argv) {

  DIR *_d;
  struct dirent *_dir;
  
  char* directory = ".";
  if ( argc < 2 ) {
    _d = opendir(directory);
  } else {
    _d = opendir(argv[1]);
  }


  struct stat _s;
  if ( _d != NULL ) {
    while ((_dir = readdir(_d)) != NULL) {
      stat(_dir->d_name, &_s);
      
      fprintf(stdout, "%x, %ld, %s\n", _s.st_mode, _s.st_size, _dir->d_name);
    }
    closedir(_d);
  }

  return 0;
}
