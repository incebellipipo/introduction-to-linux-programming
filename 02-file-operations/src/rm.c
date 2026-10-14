#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv) {

  // Exactly one path is expected
  if(argc == 2) {
    // remove(3) calls unlink for files and rmdir for empty directories; returns 0 on success
    if(remove(argv[1]) != 0) {
      // Report why it failed (ENOENT, EACCES, ENOTEMPTY...)
      perror("remove");
    }
  } else {
    fprintf(stderr, "I need args!\n");
  }
  
  return 0;
}
