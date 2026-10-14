#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Reference material: man 7 inode (file types and mode bits), man 2 stat (struct stat)
// man 7 inode
// man 2 stat

int main(int argc, char** argv) {

  // DIR is an opaque directory stream; struct dirent describes one entry (name, inode...)
  DIR *_d;
  struct dirent *_dir;
  
  // Default to the current directory when no argument is given
  char* directory = ".";
  if ( argc < 2 ) {
    _d = opendir(directory);
  } else {
    _d = opendir(argv[1]);
  }


  // Filled by stat() with metadata read from the inode: mode, size, owner, timestamps...
  struct stat _s;
  if ( _d != NULL ) {
    // readdir returns the next entry, or NULL at the end of the directory
    while ((_dir = readdir(_d)) != NULL) {
      // NOTE: d_name is relative to the opened directory, so with an argument this stats the wrong path
      // The return value should also be checked
      stat(_dir->d_name, &_s);
      
      // Print mode in hex (type + permission bits), size in bytes, then the name
      fprintf(stdout, "%x, %ld, %s\n", _s.st_mode, _s.st_size, _dir->d_name);
    }
    // Always close the directory stream
    closedir(_d);
  }

  return 0;
}
