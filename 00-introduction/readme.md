## Recap on dusty shelves

### Passing args to a C program

Every C program is capable of reading command line arguments if appropriate arguments specified for main function, that is:

```c
int main(int argc, char** argv) { ... }
```
Example source code located is [arguments.c](src/arguments.c).

### Gathering more information about errors

If errno.h header file included in C program, errors will be written to `errno` global variable. For more information please refer to `man 2 errno`.

```c
#include <errno.h>
#include <string.h>

void func() {
  fprintf(stderr, "error: %s", strerror(errno));
}
```
Example source code located is [errno.c](src/errno.c).

### Standart input output, as always

We can write to stdout and stderr and read from stdin. Those are special file descriptors available in any program even if not specified.

```c
void func() {
  write(stdin->_fileno, "Hello world!", 13);
  char in[13];
  read(stdin->_fileno, in, 13);
}
```
Example source code located is [std-descriptors.c](src/std-descriptors.c).

### Memory allocation

We can request additional memory in run-time from OS. This is done by calls like `malloc` `calloc` `realloc` and `free`. Example source code located is [memory-allocation.c](src/memory-allocation.c).
