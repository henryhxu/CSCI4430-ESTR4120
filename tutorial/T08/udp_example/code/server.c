/*
    Simple udp server
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 512

int recieve_messgae(unsigned short port) {
    struct sockaddr_in add_server, add_client;
    int receive_num = 0;
    int s, recv_len;
    socklen_t slen = sizeof(add_client);
    char buf[BUFLEN];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("Fail to create socket.\n");
        exit(1);
    }

    // clear the memory for address structure 
    memset((char *) &add_server, 0, sizeof(add_server));

    add_server.sin_family = AF_INET;
    add_server.sin_addr.s_addr = htonl(INADDR_ANY); // ip address
    add_server.sin_port = htons(port); // port adress

    //bind socket to port
    if(bind(s, (struct sockaddr*)&add_server, sizeof(add_server)) == -1)
    {
        perror("Fail to bind.\n");
        exit(1);
    }

    //keep listening for data
    while(1)
    {
        printf("Waiting for data on port %d ...\n", port);
        fflush(stdout); // clear stdout stream

        // recvfrom is blocked, until it receives data from the bind port.
        memset(buf,'\0', BUFLEN);
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &add_client, &slen)) == -1)
        {
            perror("error with recvfrom().\n");
            exit(1);
        }

        // print received information and content
        receive_num++;
        printf("Received packet %d from %s:%d\n", receive_num, inet_ntoa(add_client.sin_addr), ntohs(add_client.sin_port));
        printf("Data: %s\n" , buf);

        //now reply the client
        char *recv_info = " (server has received!)";
        strcat(buf, recv_info);
        if (sendto(s, buf, recv_len + strlen(recv_info), 0, (struct sockaddr*) &add_client, slen) == -1)
        {
            perror("error with sendto().\n");
            exit(1);
        }
    }

    close(s); // close the socket.
    return 0;
}

int main(int argc, const char **argv) {
    // Parse command line arguments
    if (argc != 2){
        printf("Usage: ./client port\n");
        return 1;
    }
    unsigned short port = strtoul(argv[1],NULL,10);

    int recv_server = recieve_messgae(port);
    return 0;
}
