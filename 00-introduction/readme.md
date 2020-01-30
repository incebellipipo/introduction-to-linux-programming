## Recap on dusty shelves

### Passing args to a C program

Every C program is capable of reading command line arguments if appropriate arguments specified for main function, that is:

```c
int main(int argc, char** argv) { ... }
```
Example source code located is [arguments.c](src/arguments.c).

### Gathering more information about errors

Most system calls return the value -1 when something goes wrong in UNIX. In addition, the kernel stores an error code in the global variable errno that all processes can access.

If errno.h header file included in C program, the variable `errno` is in the namespace. For more information please refer to `man 3 errno`.

```c
#include <errno.h>
#include <string.h>

void func() {
  fprintf(stderr, "error: %s", strerror(errno));
}
```
Example source code located is [errno.c](src/errno.c).

> It is much easier to use the UNIX library function perror() to do this for you. The perror() function, has a single string as a parameter, and looks up the value of `errno` and displays the string followed by an appropriate message based on the value of errno. It is declared in stdio.h, so you do not need to include errno.h if you use it [[1]](#1).

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

## References

<a id="1">[1]</a> 
S. Weiss, “Chapter 2: Login Records, File I/O, and Performance,” _UNIX Lecture Notes_. [Online]. Available: http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/unix_lecture_notes/chapter_02.pdf. [Accessed: Jan. 30, 2020].
