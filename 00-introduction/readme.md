---
---
# 0. Introduction
## Recap on dusty shelves

### Passing args to a C program

Every C program is capable of reading command line arguments if the appropriate parameters are specified for the `main` function, that is:

```c
int main(int argc, char** argv) { ... }
```
Example source code is located at [arguments.c](src/arguments.c).

### Gathering more information about errors

Most system calls return the value -1 when something goes wrong in UNIX. In addition, the kernel stores an error code in the global variable errno that all processes can access.

If the `errno.h` header file is included in a C program, the variable `errno` is in the namespace. For more information please refer to `man 3 errno`.

```c
#include <errno.h>
#include <string.h>

void func() {
  fprintf(stderr, "error: %s", strerror(errno));
}
```
Example source code is located at [errno.c](src/errno.c).

> It is much easier to use the UNIX library function perror() to do this for you. The perror() function, has a single string as a parameter, and looks up the value of `errno` and displays the string followed by an appropriate message based on the value of errno. It is declared in stdio.h, so you do not need to include errno.h if you use it [[1]](#1).

### Standard input and output, as always

We can write to stdout and stderr and read from stdin. Those are special file descriptors that are available in any program without being opened explicitly.

```c
void func() {
  write(stdout->_fileno, "Hello world!", 13);
  char in[13];
  read(stdin->_fileno, in, 13);
}
```
Example source code is located at [std-descriptors.c](src/std-descriptors.c).

### Memory allocation

We can request additional memory at run time from the OS. This is done by calls like `malloc`, `calloc`, `realloc` and `free`. Example source code is located at [memory-allocation.c](src/memory-allocation.c).

`calloc()` takes two arguments, which are the number of elements and the size in bytes of each element. It attempts to allocate space for an array of `nmemb` elements, each of size `size`, and fills the allocated memory with zeros. More: `man 3 calloc`
```c
#include <stdlib.h>
// void *calloc(size_t nmemb, size_t size);
...
char* buf;
buf = (char *) calloc(5, sizeof(char));
free(buf);
...
```

`malloc()` is used to dynamically allocate a single large block of memory with a given size `size` containing garbage values. More: `man 3 malloc`

```c
#include <stdlib.h> /* Required for malloc */
#include <string.h> /* Required for memset */
// void *malloc(size_t size);
...
int* num;
num = (int*) malloc(5 * sizeof(int));

// If we want, we can achieve same calloc() functionality by using memset() after malloc()
memset(num, 0, 5 * sizeof(int)); //optional
free(num);
...
```

`free()` is used to deallocate the dynamically allocated memory. Generally, the OS will reclaim the memory, but it is good practice to use `free()` as soon as you're finished using allocated memory so you can keep your program's memory footprint to a minimum and avoid memory leaks. More: `man 3 free`

If previously allocated memory is insufficient, we can use `realloc()` to change the size of a previously allocated block.

```c
#include <stdlib.h>
// void *realloc(void *ptr, size_t size);
...
int* num;
num = (int*) calloc(5, sizeof(int));
num = realloc(num, 10 * sizeof(int));
...
```

## References

<a id="1">[1]</a> 
S. Weiss, "Chapter 2: Login Records, File I/O, and Performance," _UNIX Lecture Notes_. [Online]. Available: http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/unix_lecture_notes/chapter_02.pdf. [Accessed: Jan. 30, 2020].
