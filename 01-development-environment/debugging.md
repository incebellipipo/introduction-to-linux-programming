
# Debugging with GDB

`printf` debugging works, but a debugger lets you stop the program anywhere and inspect it without recompiling. GDB is the standard one on Linux.

### Build with debug symbols

Without `-g` GDB can only show raw addresses. Also disable optimisation, otherwise variables are optimised away and lines jump around.

```sh
gcc -g -O0 -o arguments 00-introduction/src/arguments.c
```

With CMake: `cmake -DCMAKE_BUILD_TYPE=Debug ..`

### Starting

```sh
gdb ./arguments               # load the program
gdb --args ./arguments a b c  # load it with command line arguments
gdb -p <pid>                  # attach to an already running process
gdb ./prog core               # post-mortem: inspect a core dump
```

Inside GDB, `run` (or `r`) starts the program. Arguments can also be given with `run a b c`. `quit` (or `q`) leaves GDB. Pressing Enter repeats the last command.

> `gdb -tui` shows the source code in a split window. Toggle at any time with `Ctrl+x a`.

### Breakpoints

A breakpoint stops execution before a line or function is executed.

| Command                    | Meaning                                     |
|----------------------------|---------------------------------------------|
| `break main`               | stop at the start of function `main`        |
| `break arguments.c:12`     | stop at line 12 of a file                   |
| `break 12 if i == 2`       | conditional breakpoint                      |
| `info breakpoints`         | list breakpoints                            |
| `delete 1` / `disable 1`   | remove / disable breakpoint number 1        |
| `watch global_variable`    | stop whenever the variable changes          |

### Stepping

| Command            | Meaning                                                   |
|--------------------|-----------------------------------------------------------|
| `next` (`n`)       | run the current line, do not enter called functions       |
| `step` (`s`)       | run the current line, enter called functions              |
| `continue` (`c`)   | run until the next breakpoint                             |
| `finish`           | run until the current function returns                    |
| `until` / `advance 30` | run until a line, e.g. to leave a loop                |

### Inspecting

| Command                | Meaning                                         |
|------------------------|-------------------------------------------------|
| `print var`            | show a variable, `print *node`, `print arr[1]@3`|
| `print/x var`          | show in hexadecimal                             |
| `x/s argv[1]`          | examine memory as a string (`x/8xb ptr` bytes)  |
| `display var`          | print the variable after every stop             |
| `info locals`          | all local variables                             |
| `info args`            | arguments of the current function               |
| `backtrace` (`bt`)     | the call stack                                  |
| `frame 1` / `up` / `down` | move between stack frames                    |
| `list`                 | show source around the current line             |
| `set var i = 5`        | change a variable while running                 |

### A sample session

Debugging [memory-allocation.c](../00-introduction/src/memory-allocation.c):

```
$ gcc -g -O0 -o memory-allocation 00-introduction/src/memory-allocation.c
$ gdb --args ./memory-allocation hello
(gdb) break 17
(gdb) run
(gdb) print len
(gdb) print _p
(gdb) next
(gdb) display _p
(gdb) continue
```

### Crashes

When a program dies with `Segmentation fault`, just run it under GDB. It stops at the faulting line and `backtrace` shows how it got there.

```
(gdb) run
Program received signal SIGSEGV, Segmentation fault.
(gdb) backtrace
(gdb) info locals
```

To get a core file in the shell first run `ulimit -c unlimited`. For memory errors, `gcc -g -fsanitize=address` or `valgrind ./prog` are good companions.

### Processes, signals and threads

Chapters 04 to 06 need a few extra settings.

- **fork**: GDB follows the parent by default. Use `set follow-fork-mode child` to follow the child, and `set detach-on-fork off` to keep both under control (`info inferiors`, `inferior 2` to switch).
- **exec**: `set follow-exec-mode new` debugs the program started by `exec`.
- **signals**: GDB intercepts signals. `handle SIGINT nostop pass` lets your handler receive Ctrl+C without GDB stopping, see [signals.c](../04-process-management/src/signals.c). `info signals` lists the table.
- **threads**: `info threads` lists them, `thread 2` switches, `thread apply all bt` shows every stack. Useful for finding a deadlock in [mutex_example.c](../05-multithreading/src/mutex_example.c).
- **sockets and IPC**: run the server in one terminal, attach to the client with `gdb -p $(pidof client)`. You may need `sudo` or `echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope`.

### Cheat sheet

```
r / c / n / s / finish    run / continue / next / step / finish
b <where> / info b        breakpoint / list
p <expr> / x / display    inspect
bt / up / down            stack
q                         quit
```

More: `man gdb`, or `help <command>` inside GDB.
