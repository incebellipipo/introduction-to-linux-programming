---
---
# 2. File Operations

## Concepts

- Everything is a file
- File descriptors vs. `FILE*`
- Metadata and directories
- Permissions

### Everything is a file

Regular files, directories, devices (`/dev/random`), pipes and sockets are all accessed with the same calls. Two layers exist:

- **System calls** (`open`, `read`, `write`, `close`) work on integer file descriptors. The kernel hands out the lowest free number; 0, 1 and 2 are stdin, stdout and stderr.
- **C library streams** (`fopen`, `fgets`, `fprintf`, `fclose`) wrap a descriptor in a buffered `FILE*`.

```c
#include <fcntl.h>
#include <unistd.h>
// int open(const char *pathname, int flags, mode_t mode);
// ssize_t read(int fd, void *buf, size_t count);
int fd = open("/dev/random", O_RDONLY);
float data;
read(fd, &data, sizeof(data));
close(fd);
```
Example source code is located at [random.c](src/random.c).

### Reading and writing

[cat.c](src/cat.c) reads a file line by line with `fopen` and `fgets`. [tee.c](src/tee.c) copies standard input both to a file and to standard output using `read` and `write`. [touch.c](src/touch.c) creates an empty file with `open(..., O_CREAT, mode)`.

Common `open` flags (see `man 2 open`):

| Flag       | Meaning                          |
|------------|----------------------------------|
| `O_RDONLY` | read only                        |
| `O_WRONLY` | write only                       |
| `O_RDWR`   | read and write                   |
| `O_CREAT`  | create when missing, needs mode  |
| `O_TRUNC`  | empty the file on open           |
| `O_APPEND` | writes go to the end             |

### File size

`fseek` moves the position in the file and `ftell` reports it, so seeking to the end gives the size. Example source code is located at [size.c](src/size.c). `fstat` is the other way, see below.

### Metadata and directories

Every file has an inode holding its type, permissions, owner, size and timestamps. `stat` reads it into a `struct stat`. Directories are listed with `opendir`, `readdir` and `closedir`. More: `man 7 inode`, `man 2 stat`.

```c
#include <dirent.h>
#include <sys/stat.h>
DIR *d = opendir(".");
struct dirent *e;
struct stat s;
while ((e = readdir(d)) != NULL) {
  stat(e->d_name, &s);
  printf("%o %ld %s\n", s.st_mode, s.st_size, e->d_name);
}
closedir(d);
```
Example source code is located at [ls.c](src/ls.c).

### Creating and removing

`mkdir(path, mode)` creates a directory, see [mkdir.c](src/mkdir.c). `remove(path)` deletes a file or an empty directory, see [rm.c](src/rm.c). Failures are reported through `errno`, `perror` prints it, see [00-introduction](../00-introduction).

### Permissions

Mode `0644` means owner read/write, group read, others read. The mode passed to `open` and `mkdir` is filtered by the process `umask`, so `0666` with umask `022` produces `0644`.

| Digit | Bits | Meaning       |
|-------|------|---------------|
| 4     | r    | read          |
| 2     | w    | write         |
| 1     | x    | execute/enter |

> `chmod.c` and `find.c` are placeholders, they are exercises for the reader.
