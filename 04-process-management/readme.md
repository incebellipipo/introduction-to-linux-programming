---
---
# 4. Process Management

## Concepts

- Forks
- Exec
- Pipes
- Signals

### Forks

`fork()` clones the calling process. Both continue from the same point; the return value tells them apart: `0` in the child, the child's pid in the parent, `-1` on error. The child gets a copy of the memory, so changing a variable in one does not affect the other. `wait()` blocks the parent until a child exits and prevents zombies. More: `man 2 fork`, `man 2 wait`.

```c
pid_t pid = fork();
if (pid == 0) {
  /* child */
  exit(EXIT_SUCCESS);
}
wait(NULL); /* parent */
```
Example source code is located at [family.c](src/family.c).

### Exec

The `exec` family replaces the current program image with another one, keeping the pid. It only returns on error. Combined with `fork` it is how a shell starts commands. `execvp(file, argv)` searches `PATH` and takes the argument vector.

```c
if (fork() == 0) {
  execvp(argv[1], argv + 1);
  perror("execvp"); /* only reached on failure */
  exit(EXIT_FAILURE);
}
```
Example source code is located at [master-slave.c](src/master-slave.c) which runs a command in a child and shows a global variable is not shared, and [servant.c](src/servant.c).

### Pipes

`pipe(int fd[2])` creates a kernel buffer with a read end `fd[0]` and a write end `fd[1]`. Create it before `fork` so both processes inherit the ends. More: `man 2 pipe`, `man 7 pipe`.

```c
int pipefd[2];
pipe(pipefd);
if (fork() == 0) {
  write(pipefd[1], "hi", 2);
  exit(EXIT_SUCCESS);
}
read(pipefd[0], buf, BUFSIZ);
```
Example source code is located at [piping.c](src/piping.c).

### Signals

Signals are asynchronous notifications sent by the kernel or by other processes (`kill <pid>`, Ctrl+C). A handler is installed with `signal()` (or the more robust `sigaction()`). `SIGKILL` and `SIGSTOP` cannot be caught. More: `man 7 signal`.

| Signal    | Number | Default         | Typical source |
|-----------|--------|-----------------|----------------|
| `SIGINT`  | 2      | terminate       | Ctrl+C         |
| `SIGQUIT` | 3      | core dump       | Ctrl+\\        |
| `SIGKILL` | 9      | terminate (fixed)| `kill -9`     |
| `SIGSEGV` | 11     | core dump       | bad memory access |
| `SIGTERM` | 15     | terminate       | `kill`         |
| `SIGCHLD` | 17     | ignore          | child exited   |

```c
void handle_sig(int sig) { caught = sig; }
...
signal(SIGINT, handle_sig);
```

Keep handlers short: set a flag and return, since most library functions (including `printf`) are not async-signal-safe.

Example source code is located at [signals.c](src/signals.c) and [signals-with-fork.c](src/signals-with-fork.c), where the parent forwards a signal to its child with `kill()`.
