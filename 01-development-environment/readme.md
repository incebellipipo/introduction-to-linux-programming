---
---
# 1. Development Environment

## Tools of the trade

Everything in this course is built and debugged with a handful of standard UNIX tools.

### GCC

The GNU C compiler turns `.c` files into executables.

```sh
gcc -Wall -Wextra -g -o hello hello.c
```

- `-Wall -Wextra` enable most useful warnings.
- `-g` stores debug symbols (source lines, variable names) in the binary. Required for [debugging](debugging.md).
- `-o` names the output file.
- `-pthread` is needed for programs that use `pthread_*` functions.

### Make

`make` rebuilds only what changed, driven by a `Makefile`. A walk-through lives in [05-make-example](https://github.com/incebellipipo/introduction-to-linux-programming/tree/master/07-projects/05-make-example).

```make
hello: hello.c
	gcc -Wall -g -o hello hello.c
```

Run `make` in the directory containing the `Makefile`. `make clean` is a convention for removing build products.

### CMake

CMake generates the `Makefile` for you. This repository uses it, see the top level `CMakeLists.txt`.

```sh
mkdir build && cd build
cmake ..
make
```

Each chapter registers its programs with `add_executable(<name> src/<name>.c)`. Pass `-DCMAKE_BUILD_TYPE=Debug` to `cmake` to build with debug symbols.

### GDB

The GNU debugger lets you stop a running program, look at its variables and walk through it line by line. See [debugging.md](debugging.md) for a practical guide.
