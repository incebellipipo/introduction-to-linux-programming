---
---
# 6. Inter Process Communication

## Concepts

- System V IPC keys
- Shared memory
- Message queues
- Semaphores

### Keys and identifiers

Unrelated processes find the same System V object through a key. `ftok(path, id)` derives one from an existing file and a project number, both sides must use the same pair. `IPC_PRIVATE` creates an object only reachable by related processes (after `fork`). The kernel returns an identifier used for further calls.

These objects are not tied to a process and **survive exit**. Inspect them with `ipcs`, delete with `ipcrm`. Always remove them in code (`IPC_RMID`). More: `man 7 sysvipc`.

### Shared memory

A segment of memory mapped into several processes: the fastest IPC, but you must synchronise yourself.

```c
int shmid = shmget(key, size, 0666 | IPC_CREAT); // create/get
void *p = shmat(shmid, NULL, 0);                 // attach
...
shmdt(p);                                        // detach
shmctl(shmid, IPC_RMID, NULL);                   // remove
```
Example source code is located at [shm_example.c](src/shm_example.c).

### Message queues

A kernel list of typed messages. A receiver can ask for a specific type. The structure must start with a `long mtype`, followed by the payload.

```c
typedef struct msg { long mtype; char mtext[BUFSIZ]; } msg;

int msgid = msgget(key, 0600 | IPC_CREAT);
msgsnd(msgid, &m, strlen(m.mtext), 0);
msgrcv(msgid, &m, BUFSIZ, 42, 0);   // first message with type 42
msgctl(msgid, IPC_RMID, NULL);
```
Example source code is located at [msg_example.c](src/msg_example.c) (parent and child), or as two separate programs [msg_send.c](src/msg_send.c) and [msg_recv.c](src/msg_recv.c).

### Semaphores

A semaphore is a counter used to guard shared resources. `semop` applies an operation atomically:

| `sem_op` | Effect                                       |
|----------|----------------------------------------------|
| `> 0`    | release: add to the value                    |
| `< 0`    | acquire: block until value is large enough, then subtract |
| `0`      | block until the value becomes zero           |

```c
int semid = semget(key, 1, 0666 | IPC_CREAT);
struct sembuf op = { .sem_num = 0, .sem_op = -1, .sem_flg = 0 };
semop(semid, &op, 1);
```
Example source code is located at [sem_example.c](src/sem_example.c). Run it with `-1` in one terminal (it blocks) and `1` in another.
