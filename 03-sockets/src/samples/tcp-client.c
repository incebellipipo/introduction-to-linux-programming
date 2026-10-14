#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// TCP client: connect to a server, send argv[1], print the reply
int main(int argc, char** argv) {

  if(argc < 2){
    fprintf(stderr, "This command requires argument");
    exit(EXIT_FAILURE);
  }

  // NOTE: unused, the port is hard coded again below
  int port = 8080;
  int fd = 0;
  // IPv4 socket address: family, port and IP address
  struct sockaddr_in serv_addr;
  char buf[BUFSIZ] = {0};
  // AF_INET = IPv4, SOCK_STREAM = reliable byte stream (TCP); returns a file descriptor
  if(( fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  
  // Fill the address; htons converts the port to network byte order (big endian)
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);
  // Convert dotted text to a binary address (loopback)
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Three way handshake with the server; the cast is needed because connect takes the generic struct sockaddr
  if(connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  // A connected socket is just a file descriptor: write sends bytes...
  write(fd, argv[1], strlen(argv[1]));
  // ...and read blocks until the server replies
  int ret = read(fd, buf, BUFSIZ);

  fprintf(stdout, "%s\n", buf);

  // Closing the socket terminates the connection (the server sees read() return 0)
  close(fd);

  return 0;
}