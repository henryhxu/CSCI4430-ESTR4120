# Description and Usage of UDP Demo

## Implement UDP client and server
- `server.c`: The server is created to receive messages from the client, and then send back an acknowledgment to the client for the received messages.
- `client.c`: The client is created to send a single message to the server and receive an acknowledgment from the server for the message.

## Instructions
### Compile examples
The Makefile is capable of building the `client.c` and `server.c` programs into executables: 
```
# To build
$ cd code
$ make

# To clean
$ cd code
$ make clean
```

### Run the server and clients

In one terminal, run the server and specify the port:
```
$ ./server 8888
Waiting for data on port 8888 ...
```

In another terminal, run a client to send a message to the server:
```
$ ./client localhost 8888 "hello server"
```

The server should print the message it receives to the terminal:
```
Received packet 1 from 127.0.0.1:xxxxx
Data: hello server
```

Then, client gets an acknowledgment message upon the server's receipt of the message:
```
Acknowlege received from server 127.0.0.1:8888
Data: hello server (server has received!)
```