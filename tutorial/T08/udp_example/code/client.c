/*
    Simple udp client
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

// #define SERVER "localhost"
#define BUFLEN 512

int send_message(const char *server, unsigned short port, const char *message)
{
    struct sockaddr_in addr_server;
    int s;
    socklen_t slen = sizeof(addr_server);
    char buf[BUFLEN];

    // create socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("fail to create socket.\n");
        exit(1);
    }

    // clear the memory for address structure
    memset((char *) &addr_server, 0, sizeof(addr_server));
    addr_server.sin_family = AF_INET;
    struct hostent* sp = gethostbyname(server); // get hostname
    memcpy(&addr_server.sin_addr, sp->h_addr, sp->h_length); // ip address
    addr_server.sin_port = htons(port); //port

    //send the message
    if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &addr_server, slen)==-1)
    {
        perror("error with sendto().\n");
        exit(1);
    }

    // recieve a reply from the server.
    // recvfrom is blocked, until it receives data from the server.
    memset(buf,'\0', BUFLEN);
    if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &addr_server, &slen) == -1)
    {
        perror("error with recvfrom().\n");
        exit(1);
    }

    // print received information and content
    printf("Acknowlege received from server %s:%d\n", inet_ntoa(addr_server.sin_addr), ntohs(addr_server.sin_port));
    printf("Data: %s\n" , buf);

    close(s); // close socket
    return 0;
}

int main(int argc, const char **argv) {
    // Parse command line arguments
    if (argc != 4) {
        printf("Usage: ./client hostname port message\n");
        return 1;
    }
    const char *hostname = argv[1];
    unsigned short port = strtoul(argv[2],NULL,10);
    const char *message = argv[3];

    int send_client = send_message(hostname, port, message);
    return 0;
}
