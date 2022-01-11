# Sockets Discussion Starter Code

Implement the TODOs in server.cpp and client.cpp.

## During Class: Implement together

- `server.cpp`: Runs a server that listens for messages from clients.
- `client.cpp`: Creates a client that sends a single message to the server.

## Helper function

The file `helpers.h` contains functions to help you set up the `sockaddr_in` structs for your sockets.

## Instructions

### Download code

```
$ git clone https://github.com/eecs482/bgreeves-socket-example.git
```

### Compile examples

The Makefile has recipes to build the client and server programs on CAEN or Mac OS using:

```
# To build
$ cd starter-code
$ make client
$ make server

# To clean
$ make clean
```

### Run the server and clients

In one terminal, run the server and specify a port to listen on:

```
$ ./server 8888
Server listening on port 8888...
```

In another terminal, spawn a client to send a message to the server:

```
$ ./client localhost 8888 "hello server"
Sending message hello server to localhost:8888
```

The server should print the message it receives to the terminal:

```
$ ./server 8888
Server listening on port 8888...
New connection 4
Client 4 says "hello server"
```

<!-- ### Tip: SSH-ing into the same CAEN machine from different terminals

In order to run a server and a client in two separate terminals over SSH, you have to be connected to the same CAEN machine.

To do this, first, from one terminal, SSH into CAEN normally and determine the hostname of the machine you logged into:

```
$ ssh you@oncampus-course.engin.umich.edu
$ hostname
caen-vnc-vmXX.engin.umich.edu
```

Then you can SSH directly into this machine from another terminal:

```
$ ssh you@caen-vnc-vmXX.engin.umich.edu 
``` -->
