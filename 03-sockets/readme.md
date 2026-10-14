---
---
# 3. Sockets

## Concepts

- Sockets as file descriptors
- TCP (stream) sockets
- UDP (datagram) sockets
- UNIX domain sockets

### Socket basics

A socket is an endpoint of communication. It is created by `socket(domain, type, protocol)` and, once connected, used with the ordinary `read` and `write` calls. More: `man 2 socket`, `man 7 socket`.

| Domain      | Meaning                         | Address struct        |
|-------------|---------------------------------|-----------------------|
| `AF_INET`   | IPv4 network                    | `struct sockaddr_in`  |
| `AF_UNIX`   | processes on the same machine   | `struct sockaddr_un`  |

| Type          | Meaning                                    |
|---------------|--------------------------------------------|
| `SOCK_STREAM` | reliable ordered byte stream (TCP)         |
| `SOCK_DGRAM`  | independent unreliable messages (UDP)      |

Multi-byte numbers on the wire are big endian. Use `htons()`/`htonl()` before storing a port or address and `ntohs()`/`ntohl()` after reading.

### TCP

Server side: `socket` -> `bind` -> `listen` -> `accept` -> `read`/`write` -> `close`.
Client side: `socket` -> `connect` -> `write`/`read` -> `close`.

```c
// server
int fd = socket(AF_INET, SOCK_STREAM, 0);
bind(fd, (struct sockaddr*)&addr, sizeof(addr));
listen(fd, 3);
int cfd = accept(fd, (struct sockaddr*)&addr, &len); // blocks, returns a new fd per client
read(cfd, buf, BUFSIZ);

// client
connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
write(fd, "hello", 5);
```
Example source code is located at [tcp-server.c](src/samples/tcp-server.c) and [tcp-client.c](src/samples/tcp-client.c). Try them: start the server in one terminal, then `./tcp-client hello` in another. `read` returns 0 when the peer closes.

### UDP

There is no connection. The server binds and waits with `recvfrom`, the client just `sendto`s. Each call carries the peer address. Example source code is located at [udp-server.c](src/samples/udp-server.c) and [udp-client.c](src/samples/udp-client.c). Datagrams may be lost or reordered, nothing tells you.

### UNIX domain sockets

Same API as TCP but the address is a path in the filesystem (here `/var/tmp/dsocket`). Faster, and access is controlled with file permissions. The server must `unlink` a stale socket file before `bind`. Example source code is located at [unix-server.c](src/samples/unix-server.c) and [unix-client.c](src/samples/unix-client.c).

### Handy tools

```sh
ss -tlnp            # listening TCP sockets and their processes
nc localhost 8080   # a ready made client
```
