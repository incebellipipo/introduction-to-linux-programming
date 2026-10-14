---
---
# 5. Multithreading

## Concepts

- Threads
- Joining and detaching
- Mutex locks

### Threads

A thread is an independent flow of execution inside a process. Unlike `fork`, threads share the address space: globals and the heap are common, each thread has its own stack. Link with `-pthread`. More: `man 7 pthreads`.

```c
#include <pthread.h>
void* worker(void* arg) { /* ... */ return NULL; }
...
pthread_t th;
pthread_create(&th, NULL, worker, &value); // handle, attributes, start routine, argument
pthread_join(th, NULL);                    // wait for it to finish
```
Example source code is located at [simple_multi_threading.c](src/simple_multi_threading.c).

A thread function has the signature `void* f(void*)`. The argument is a pointer, so make sure the pointed data outlives the thread, a local variable that gets overwritten (see [func_pointer_threading.c](src/func_pointer_threading.c)) is a common bug.

### Join or detach

Every thread must either be joined with `pthread_join` (the caller waits and can read the return value) or detached with `pthread_detach` (resources are released automatically). When `main` returns, the whole process ends, taking running threads with it.

### Race conditions and mutexes

Two threads changing the same variable without coordination produce unpredictable results, a data race. [func_pointer_threading.c](src/func_pointer_threading.c) does so on purpose.

A mutex lets only one thread at a time into a critical section:

```c
pthread_mutex_t lock;
pthread_mutex_init(&lock, NULL);
...
pthread_mutex_lock(&lock);
global_variable++;        // critical section
pthread_mutex_unlock(&lock);
```
Example source code is located at [mutex_example.c](src/mutex_example.c). Keep the critical section short, always unlock, and take multiple locks in the same order everywhere to avoid deadlocks.

> Debugging threads with GDB: see [debugging.md](../01-development-environment/debugging.md).
