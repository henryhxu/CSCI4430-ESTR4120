#include <arpa/inet.h> //close
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO, FD_SETSIZE macros
#include <sys/types.h>
#include <unistd.h> //close

#define MAXCLIENTS 30
#define BUF_SIZE 2048
#define MAX_BITRATE_NUM 64
#define MAX_CHUNKNAME_LEN 256
#define MAX_SERVER_LINE 100

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

int get_listen_socket(struct sockaddr_in *address, int port)
{
    int yes = 1;
    int server_socket;
    // create a master socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket <= 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set master socket to allow multiple connections ,
    // this is just a good habit, it will work without this
    int success =
        setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    if (success < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // type of socket created
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons((u_short)port);

    // bind the socket to localhost port 8888
    success = bind(server_socket, (struct sockaddr *)address, sizeof(*address));
    if (success < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("---Listening on port %d---\n", port);

    // try to specify maximum of 3 pending connections for the server socket
    if (listen(server_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    return server_socket;
}

int main(int argc, char *argv[])
{
    int use_dns = 0;

    int send_idx = 0, recv_idx = 0; // for debugging only, you can ignore it

    int serverPort = 80; // the port for server, 80 as the default HTTP port

    int listen_port;
    char *server_file;
    char *log_file;
    double alpha;

    // for --nodns load balance
    unsigned long server_addrs[MAX_SERVER_LINE]; // sockaddr_in.in_addr.s_addr
    int server_num = 0;
    int request_cnt = 0;

    // process the args
    if (argc == 6)
    {
        // used in mandatory part
        // no-dns case
        use_dns = 0;
        // listen port for connection
        listen_port = atoi(argv[2]);
        // server ip
        server_file = argv[3];
        // value for <alpha>
        alpha = atof(argv[4]);
        // log file path
        log_file = argv[5];

        // =========== extract server ips from txt file ==========
        FILE *fp = fopen(server_file, "r");
        if (fp == NULL)
        {
            perror("open server file error");
            exit(1);
        }
        int file_read_len;
        size_t line_len = 64;
        char *line_buf = NULL; // (char *)malloc(100 * sizeof(char));
        while ((file_read_len = getline(&line_buf, &line_len, fp)) != -1)
        {
            if (line_buf[file_read_len - 1] == '\n')
            {
                line_buf[file_read_len - 1] = '\0';
            }
            printf("server ip:[%s] cnt: %d\n", line_buf, server_num + 1);
            server_addrs[server_num] = ntohl(inet_addr(line_buf));
            server_num++;
        }
        fclose(fp);
        if (server_num <= 0)
        {
            printf("%s is empty", server_file);
            exit(1);
        }
        // ============= end of extract server ips ===============

        FILE *fp_log = fopen(log_file, "w"); // clear up the log file
        if (fp_log == NULL)
        {
            perror("open log file");
            exit(1);
        }
        fclose(fp_log);
    }
    else if (argc == 7)
    {
        // reserved for bonus part
    }
    else
    {
        // exit for other args cases
        fprintf(stderr, "Argc as %d wrong\n", argc);
        exit(0);
    }

    int proxy_listen_socket, addrlen, activity, valread;
    // define the para for each server-client pair
    int client_sockets[MAXCLIENTS] = {0}; // client socket for each streaming
    int server_sockets[MAXCLIENTS] = {0}; // server sockets for each streaming

    int bitrates[MAXCLIENTS][MAX_BITRATE_NUM]; // bitrate values for the parsed bitrates from f4m file
    int bitrate_num[MAXCLIENTS] = {0};         // bitrate number for the paresed bitrates from f4m file

    int is_chunk[MAXCLIENTS];                       // is_chunk flag for indicating whether chunk is tranferred in the streaming
    double T_curN[MAXCLIENTS];                      // the current throughtput
    char chunknames[MAXCLIENTS][MAX_CHUNKNAME_LEN]; // the chunk name for current streaming (used in the log)
    int cur_bitrate[MAXCLIENTS] = {0};              // the current bitrate for the video streaming
    int chunk_length[MAXCLIENTS] = {0};             // the length for this chunk (include the HTTP header)

    struct timeval chunk_start_time[MAXCLIENTS];   // the start time for each chunk
    int chunk_sent_length[MAXCLIENTS] = {0};       // the sent length for current chunk (include the HTTP header)
    int chunk_http_header_recvd[MAXCLIENTS] = {0}; // the http header for the chunk is recvd or not
    struct in_addr server_ips[MAXCLIENTS];

    // initialize the arrays
    for (int _i = 0; _i < MAXCLIENTS; _i++)
    {
        T_curN[_i] = 0.0;
        for (int _j = 0; _j < MAX_BITRATE_NUM; _j++)
        {
            bitrates[_i][_j] = 0;
        }
        memset(chunknames[_i], 0, MAX_CHUNKNAME_LEN);
    }
    // end of initialization

    struct sockaddr_in address;
    proxy_listen_socket = get_listen_socket(&address, listen_port);
    char buffer[BUF_SIZE];

    // accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");
    // set of socket descriptors
    fd_set readfds;
    while (1)
    {
        // clear the socket set
        FD_ZERO(&readfds);

        // add listen socket to set
        FD_SET(proxy_listen_socket, &readfds);
        // add all the client sockets to the set
        for (int i = 0; i < MAXCLIENTS; i++)
        {
            int client_sock = client_sockets[i];
            if (client_sock != 0)
            {
                FD_SET(client_sock, &readfds);
            }
        }
        // add all the server sockets to the set
        for (int i = 0; i < MAXCLIENTS; i++)
        {
            int server_sock = server_sockets[i];
            if (server_sock != 0)
            {
                FD_SET(server_sock, &readfds);
            }
        }

        // wait for an activity on one of the sockets , timeout is NULL ,
        // so wait indefinitely
        activity = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR))
        {
            perror("select error");
        }

        // ====================================================
        // ==============START OF listen socket================
        // If something happened on the listen socket ,
        // then its an incoming connection, call accept()
        if (FD_ISSET(proxy_listen_socket, &readfds))
        {
            // TODO: write your code here
        }
        // ===================END OF listen socket========================
        // ===============================================================

        // ===============================================================
        // ===================START OF client socket======================
        // "for recving HTTP GET request from client only"
        // 1. Intercept HTTP GET requests from client
        // 2. Handle f4m data GET request
        // 3. Handle chunk data GET request
        // 4. Handle other request
        for (int i = 0; i < MAXCLIENTS; i++)
        {
            // TODO: write your code here
        }
        // ==================END OF client socket=======================
        // =============================================================

        // =============================================================
        // ==================START OF server socket=====================
        // 1. Handle server disconnection
        // 2. Intercept HTTP reply from server
        // 3. Analyze the reply and calculate the bitrate
        // 4. Send the HTTP reply to the corresponding client
        // 5. Write out the log
        for (int i = 0; i < MAXCLIENTS; i++)
        {
            // TODO: write your code here
        }
        // =============END OF server socket======================
        // =======================================================
    }
    return 0;
}
