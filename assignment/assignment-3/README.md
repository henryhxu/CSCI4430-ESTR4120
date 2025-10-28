# Assignment 3: Reliable Transport & Static Router

> [!NOTE]
> Version: 1.0

> [!IMPORTANT]
>
> - Due: Nov. 30, 2025, 11:59 PM HKT
> - This is a group assignment with identical grouping information as Assignment 2.
> - Before beginning the assignment, it is advisable to thoroughly read through the entire document as subsequent sections may provide valuable insights for earlier ones.

## 0. Overview

### 0.1. Table of Contents

* [Overview](#ow)
* [Part 1:](#1) Reliable Transport Protocol: WTP (**Mandatory**)
  * [Part 1-1:](#1-1) WTP Specification
  * [Part 1-2:](#1-2) Implement `wSender`
  * [Part 1-3:](#1-3) Implement `wReceiver`
  * [Part 1-4:](#1-4) Test Cases Clarifications
* [Part 2:](#2) Questions on Reliable Transport (**Bonus**)
  * [Part 2-1:](#2-1) WTP Optimization
  * [Part 2-2:](#2-2) Bonus Questions
* [Part 3:](#3) Static Router (**Mandatory**)
  * [Part 3-1:](#3-1) Background: Routing
  * [Part 3-2:](#3-2) Artifacts
* [Submission Instructions](#subinstr)
* [Implementation Environment &amp; Autograder](#ag)

`<a name="ow"></a>`

### 0.2. Assignment Scope

This assignment project has two independent parts.

For the first part, the objective is to develop a simple reliable transport protocol,`WTP`, which operates **on top of UDP**.
Your implementation of `WTP` must ensure the sequential and reliable delivery of UDP datagrams, even in the face of challenges such as `packet loss, latency, corruption, duplication, and reordering`. Indeed, there are a variety of ways to ensure a message is reliably delivered from a sender to a receiver. Specifically, you are to implement a sender (`wSender`) and a receiver (`wReceiver`) that follows the following `WTP` specification in this assignment.
The second part has some bonus questions on WTP.

For the third part, you will be writing a simple router configured with a static routing table. Your router will receive raw Ethernet frames. It will process the packets just like a real router, then forward them to the correct outgoing interface. Your major task is to implement the forwarding logic so packets go to the correct interface.

Students are expected to have a deeper understanding of L4 transport protocols and L3 routing respectively by finishing Part 1 and Part 2 of this assignment.

`<a name="1"></a>`

## Part 1. Reliable Transport Protocol: WTP

> [!Note]
> This is the Part 1 of assignment 3 - reliable transport protocol. This part is independent from Part 3. Static Router, so you can finish them separately.

`<a name="1-1"></a>`

### 1.1. WTP Specification

The data transmission format used by `WTP` consists of a header and a data chunk (data in your transferred files). The header includes four types: `START`, `END`, `DATA`, and `ACK`, all of which adhere to the following format:

```
struct PacketHeader {
	unsigned int type;     // 0: START; 1: END; 2: DATA; 3: ACK
	unsigned int seqNum;   // Describe afterwards
	unsigned int length;   // Length of data; 0 for ACK, START and END packets
	unsigned int checksum; // 32-bit CRC
}
```

The `PacketHeader`'s `type` and `seqNum` fields can be explained as follows:

1. To establish a connection, `wSender` initiates a `START` message with a random `seqNum` value and awaits an ACK. In `wReceiver`, the ACK `seqNum` values for `START` messages should match the `seqNum` value sent by `wSender`. `wReceiver` then sends this ACK back to `wSender`.
2. Once the connection is established, data transfer may proceed using the `DATA` message type. To transmit packets consecutively, `wSender` sets the initial seqNum to **0** for the first packet after `START`. The `seqNum` of each subsequent transmitted data packet is incremented by one. `wReceiver` should only send back cumulative ACK, which represent the last acknowledged packet within current sliding window. (We will describe silding window afterward.)
3. After the entire file has been transferred, the connection should be terminated with `wSender` sending an `END` message with the same `seqNum` as the `START` message and awaiting the corresponding ACK. The `seqNum` value for the `END` message's ACK in `wReceiver` should match that of `wSender`.

#### Packet Size

We will employ Ethernet networks for data transfer, with a maximum frame size of 1500 bytes. When utilizing the implemented `WTP` for data transfer, it is advisable to observe the maximum data size that can be transferred in a single packet. Notably, **UDP**, as a transport layer protocol, has an 8-byte header, while the underlying IP protocol headers across the network, link, and physical layers have a total header size of 20 bytes. Consequently, the available transferred data in a single packet is **1472 bytes** (including the `WTP` header mentioned above).

`<a name="1-2"></a>`

### 1.2. Implement `wSender`

#### UDP based WTP

`wSender` should read an input file and transmit it to a specified receiver using **UDP** following the WTP protocol described above. The input file should be split into appropriately sized data chunks in each packet, and a `checksum` should be appended to each packet using the 32-bit `CRC` header provided in the starter_files directory. Also, please refer to the WTP specification above to transfer data with its `type` and `seqNum` in the `PacketHeader`.

#### Sliding Window and Timeout

This reliable transport will be implemented using a `sliding window` mechanism with a window size (`window-size`) specified in the command line. `wSender` sends all packets in the current sliding window, and `wReceiver` should receive these packets within the **same** window size. `wReceiver` drops packets that are not in sequential `seqNum` and only sends back **cumulative** `ACK`s indicating the last sequentially received packet. In the current implementation, there is no need to send an `ACK` for every individual packet.

To handle situations where data packets are failed to sent or `ACK` packets are not well received by `wSender`, a 500 milliseconds **retransmission timer** will be implemented to automatically retransmit unacknowledged packets. Specifically, when `wSender` transmits all packets in the current window, it starts the timer and waits for `ACK`s. If all `ACK`s are received within 500 milliseconds, we should move the window forward to the unsent packets, reset the timer, and send the new packets in the window. Otherwise, if the timer exceeds 500 milliseconds and `wSender` does not receive all `ACK`s from `wReceiver`, the window moves forward to the first packet that needs to be re-transmitted, then we reset the timer, and send all packets in the current window.

#### Reliable Transfer Situations

Under various network abnormal environments, `wSender` is required to ensure reliable data transfer. The tested conditions are outlined in the [Test Cases Clarifications](#1-4) section.

#### Running `wSender`

`wSender` should be invoked as follows:

`./wSender <receiver-IP> <receiver-port> <window-size> <input-file> <log>`

* `receiver-IP`: The IP address of the host on which `wReceiver` is running.
* `receiver-port`: The port number on which `wReceiver` is set to receive files.
* `window-size`: The maximum number of sent packets allowed in one sliding window.
* `input-file`: The path to the file that needs to be transferred, which can be either a text or binary file (e.g., image or video).
* `log`: The file path where the running messages should be logged, which will be described later.

Example: `./wSender 10.0.0.1 8888 10 input.in log.txt`

*Note: During testing and grading, the arguments in the command line exactly match the format shown above. It is crucial to ensure that your implementation can correctly parse the command line arguments in the specified format.*

#### Logging

`wSender` should generate a log of its activity, appending the following line to the log after sending or receiving each packet (everything excluding the `data` in the packet structure described earlier):

`<type> <seqNum> <length> <checksum>`

`<a name="1-3"></a>`

### 1.3. Implement `wReceiver`

#### Receiving Method

`wReceiver` should use an infinite loop to prepare to receive any file from `wSender` at any time, and for each new file, a new connection should be created. Furthermore, `wReceiver` can only handle one connection in `wSender` at a time and should ignore `START` messages while in the middle of an existing connection. It is responsible for receiving and storing the file sent by the `wSender` on disk completely and accurately, such as it can be played without any errors if we send a video. The stored file should be named `FILE-i.out`, where `i=0` for the file from the first connection, `i=1` for the second, and so on.

#### Packet Corruption Checking

`wReceiver` should also calculate the `checksum` value for the data in each packet it receives using the header mentioned in Part 1. If the calculated checksum value does not match the `checksum` provided in the header, the packet should be dropped, and no `ACK` for this packet should be sent back.

#### Manage `seqNum`

After receiving packets in the current window, `wReceiver` sends a cumulative ACK with the `seqNum` it expects to receive next. If it expects a packet of sequence number `N`, the following two scenarios may occur in the next time of receiving packets:

1. If it receives any packet with `seqNum=N` in the window, it sequentially checks the received packets afterwards in the window and obtains the highest in-order packet's `seqNum` (say `M`). The packets with seqNum between `N` and `M` will be received and stored by `wReceiver`, while other packets will be discarded. `wReceiver` then sends an ACK with `seqNum=M+1`.
2. If it does not receive any packet with `seqNum=N` in the window, it sends back an `ACK` with `seqNum=N`.

Additionally, `wReceiver` drops all packets with `seqNum` greater than or equal to `N + window-size` to maintain a `window-size` window. `wReceiver` should also log every single packet it sends and receives using the same format as the `wSender` log.

#### Running `wReceiver`

`wReceiver` should be invoked as follows:

`./wReceiver <port-num> <window-size> <output-dir> <log>`

* `port-num`: The port number on which `wReceiver` is set to receive data.
* `window-size`: The maximum number of received packets allowed in one sliding window.
* `output-dir`: The directory where `wReceiver` will store the output files, i.e., the `FILE-i.out` files.
* `log`: The file path where the running messages should be logged as described above.

Example:
`./wReceiver 8888 2 /tmp log.txt`

*Note: During testing and grading, the arguments in the command line exactly match the format shown above. It is crucial to ensure that your implementation can correctly parse the command line arguments in the specified format.*

> [!TIP]
>
> * If you are unsure of the usage of libc functions, please consult their respective `Man pages`. For example, to obtain the definition and usage of recvfrom, enter `man recvfrom` in the terminal.
> * Another valuable resource for UDP socket programming is [Beej&#39;s Guide to Network Programming Using Internet Sockets](https://beej.us/guide/bgnet/html/index.html).

`<a name="1-4"></a>`

### 1.4. Test Cases Clarifications

The program is required to ensure reliable data transfer in any network condition, and the autograder tests the following aspects of the base part of `WTP`:

1. Corruption of packet data (wrong checksum, etc.).
2. Various levels of packet loss.
3. Duplication of any packet for any amount.
4. Reordering of the packets.
5. Delayed arrival of the packets.
6. Mix of all unreliable conditions above.

> [!NOTE]
>
> * The testing of your program will involve only one `wSender` and one `wReceiver` for all sections.
> * You have the flexibility to select how to read from and write to files, but you may find the `std::ifstream.read()` and `std::ofstream.write()` functions, or `mmap` function especially useful.
> * You MUST NOT use TCP sockets (and the autograder can detect it).
> * If you use single thread, polling on a socket may be helpful for packet receiving and timer implementation. Refer to `MSG_DONTWAIT` in `recvfrom` or `recvmsg` for further information.
> * Stay up-to-date with the latest announcements by following Piazza closely. Further clarifications will be posted on Piazza via pinned Instructor Notes. Also those updates will be synchronized in this GitHub page.

`<a name="2"></a>`

## Part 2: Questions on Reliable Transport and WTP Optimizations

> [!NOTE]
> This part is a **bonus part**, containing background knowledge on WTP optimizations and two bonus questions.

`<a name="2-1"></a>`

### 2.1. WTP Optimization

Our current design of reliable transport protocol - WTP (refered to as `WTP base`) can be optimized in various ways. One possible optimization is selective repeat to avoid wasting bandwidth caused by go-back-N-style retransmissions.

Consider the behavior of current  in the given scenario, which employs a window size of 3:

<img src="base_case.PNG" title="Inefficient transfer of data" alt="" width="250" height="250"/>

In this scenario, previous (`WTP base`) `wReceiver `sends one ACK with the sequence number set to 0, indicating the next expected packet. Consequently, `wSender` experiences a timeout and retransmits packets 0, 1, and 2. However, since `wReceiver` has already received and buffered packets 1 and 2, there is an avoidable retransmission of these packets, which can be done via selective repeat.

Specifically, `wReceiver` and `wSender` can be modified as follows to implement selective repeat mechanism (the optimized version of WTP is refered to as `WTP optimization`):

* `wReceiver` will be modified to stop sending cumulative ACKs after the transmission of all data packets in the current window. Instead, it will send back an ACK with `seqNum` set to the same value as the received data packet immediately after receiving each packet. For instance, if the sender sends a data packet with `seqNum` set to 2, `wReceiver` will send back an ACK with `seqNum` set to 2 promptly. However, it will continue to discard all packets with `seqNum` greater than or equal to ` N + window_size`, where `N` represents the next expected `seqNum`.
* `wSender` is required to keep track of all the received ACKs within its current window. Consequently, a timeout for packet 0 would not automatically lead to the retransmission of packets 1 and 2. Only packet 0 need to be retransmitted after timeout.

For a better understanding, let us consider an example demonstrating the expected behavior of the optimized `wSender` and `wReceiver` programs in the scenario discussed at the start of this section:

<img src="improvement.PNG" title="only ACK necessary data" alt="" width="250" height="250"/>

`wReceiver` individually ACKs both packet 1 and 2.

<img src="improvement_2.PNG" title="only send unACKd data" alt="" width="250" height="250"/>

`wSender` receives these ACKs and marks packets 1 and 2 as received in the buffer. It then waits for the 500ms timeout of packet 0 and retransmits only packet 0.

`<a name="2-2"></a>`

### 2.2. Bonus Questions

> [!NOTE]
> This part has two bonus questions regarding both WTP base and optimization. You can use them as a warm-up exercise before officially starting to code, or answer them after you finish your implementation of WTP base. We provide two sample questions and answers first. You can skip them and directly go to [actual bonus questions](#actualbonus) if you like.

#### 2.2.1. Sample Questions

**Example Question 1 (sender side)**: Assume that the sliding window size of the sender and the receiver is now 5, and the packet seqNum starts from 1. Among them, packet 3 is lost when sending the first window; after receiving the ACK, the window starts to slide, and packet 7 is lost when sending a certain window. No other unreliable situations exist. Please write down the seqNum of the ACKs received by the sender in both `WTP` base and optimization programs until the 7th packet is received, and the window range after receiving the ACKs.

> [!TIP]
> For `WTP` base:
>
> * 1st ACK: 3; window: [3 4 5 6 7]
> * 2nd ACK: 7; window: [7 8 9 10 11]
>
> For `WTP` optimizations:
>
> * 1st ACK: 1 2 4 5; window: [3 4 5 6 7]
> * 2nd ACK: 3 6; window: [7 8 9 10 11]
> * 3rd ACK: 7; window: [7 8 9 10 11]

**Example Question 2 (receiver side)**: Assuming that the size of the sliding window of the receiver is 12, the next expected seqNum is 10, and the Packet seqNum currently received in turn is [8 9 11 10 11 12 13 14 18 15 17 19]. What are the packets that will be received/buffered in the receiver? Please write down their seqNum in turn for both `WTP` base and optimization programs.

> [!TIP]
>
> * For `WTP` base: 10 11 12 13 14 15
> * For `WTP` optimizations: 11 10 12 13 14 18 15 17 19

`<a name="actualbonus"></a>`

#### 2.2.2. Actual Bonus Questions

Please answer the following questions in the example format:

**Question 1**: Assume that the sliding window size of the sender and the receiver is now 7, and the packet seqNum starts from 1. Among them, packet 3 is lost when sending the first window. No other unreliable situations exist. Please write down the seqNum of the ACKs received by the sender in both `WTP` base and optimization programs until the 5th packet is received, and the window range after receiving the ACKs.

**Question 2**: Assuming that the size of the sliding window of the receiver is 10, the next expected seqNum is 5, and the Packet seqNum currently received in turn is [5 6 7 8 9 10 16 14 11 13]. What are the packets that will be received/buffered in the receiver? Please write down there seqNum in turn for both `WTP` base and optimization programs.

`<a name="3"></a>`

## Part 3: Static Router

> [!NOTE]
> This is the Part 3 of assignment 3 - Static Router. Note: this part is independent from Part 1 & 2, so you can finish them separately.

`<a name="3-1"></a>`

### 3.1. Background: Routing

> [!IMPORTANT]
>
> #### Clarifications & Scope
>
> This section has an outline of the forwarding logic for a router.
> The behavior of a router can be complex, which includes ARP handling, ICMP handling, IPv4 forwarding and other state-of-the-art extensions, e.g. IPv6.
>
> In this assignment, our goal is to implement a **simplified version** of a static router, focusing **solely on IPv4 routing**, including longest prefix match (LPM) and packet modifications. That is, we assume:
>
> * Lookups in ARP cache of the router always hits an entry so that we do not have to implement ARP query/response processing.
> * We do not implement ICMP-related processing logic. For cases where an ICMP message should be generated by the router, we omit them and drop the packet.
> * The router MUST correctly route IPv4 packets according to pre-loaded routing table and ARP caches.
>   * It MAY assume no IP options are used.
>   * It MUST correctly validate and generate checksums.
>   * It MUST decrement the TTL.
>   * It MUST forward packets using the forwarding table, selecting an entry with the longest prefix match algorithm.
>   * It MUST forward packets using the ARP cache, modifying destination MAC address using matched ARP cache entry.
>   * Note that an Ethernet frame payload may be larger than the encapsulated IP packet. That is, there may be some padding bytes after the IP packet. This can occur when an Ethernet interface tries to align frames on 4-byte boundaries.
>
> Below we provide background on the behavior of a "complete" version of router. It is suggested to read through following subsections to understand the difference in the behaviors of a complete router and the simplified one in this assignment.
>
> You are encouraged to try implementing ICMP handling and ARP handling of a router based on the background provided. However, considering the workload of other parts, these functionalities are out of the scope of this assignment and will not be graded.

#### IP Forwarding and ARPs

Given a raw Ethernet frame, if the frame contains an IP packet whose destination is not one of the router's interfaces:

1. Check that the packet is valid (has a correct checksum).
2. Decrement the TTL by 1, and recompute the packet checksum over the modified header.
3. Find out which entry in the routing table has the longest prefix match with the destination IP address.
4. Check the ARP cache for the next-hop MAC address corresponding to the next-hop IP. If it's there, send it. Otherwise, send an ARP request for the next-hop IP (if one hasn't been sent within the last second), and add the packet to the queue of packets waiting on this ARP request.

This is a high-level overview of the forwarding process. More low-level details are below. For example, if an error occurs in any of the above steps, you will have to send an ICMP message back to the sender notifying them of an error. You may also get an ARP request or reply, which has to interact with the ARP cache correctly.

#### Protocols to Understand

#### Ethernet

You are given a raw Ethernet frame and have to send raw Ethernet frames. You should understand source and destination MAC addresses and the idea that we forward a packet one hop by changing the destination MAC address of the forwarded packet to the MAC address of the next hop's incoming interface.

#### Internet Protocol

Before operating on an IP packet, you should verify its checksum. Packets with checksum mismatch are discarded. You should understand how to find the longest prefix match of a destination IP address. If you determine that a datagram should be forwarded, you should correctly decrement the TTL field of the header and recompute the checksum over the changed header before forwarding it to the next hop.

#### Internet Control Message Protocol

ICMP sends control information. A router will use ICMP to send messages back to a sending host. We list several conditions in which a router sends ICMP messages:

* **Echo reply (type 0):** Sent in response to an echo request (`ping`) to one of the router's interfaces. (This is only for echo requests to any of the router's IPs. An echo request sent elsewhere should be forwarded).
* **Destination net unreachable (type 3, code 0):** Sent if there is a non-existent route to the destination IP (no matching entry in routing table when forwarding an IP packet).
* **Destination host unreachable (type 3, code 1):** Sent after seven ARP requests were sent to the next-hop IP without a response.
* **Port unreachable (type 3, code 3):** Sent if an IP packet containing a UDP or TCP payload is sent to one of the router's interfaces.
* **Time exceeded (type 11, code 0):** Sent if an IP packet is discarded during processing because the TTL field is 0.

Some ICMP messages may come from the source address of any of the router interfaces, while others must come from a specific interface. Please refer to [RFC 792](https://tools.ietf.org/html/rfc792) for details.

#### Address Resolution Protocol

ARP is needed to determine the next-hop MAC address that corresponds to the next-hop IP address stored in the routing table. Without the ability to generate an ARP request and process ARP replies, a router would not be able to fill out the destination MAC address field of the raw Ethernet frame to be sent over the outgoing interface.

When forwarding a packet to a next-hop IP address, the router should first check the ARP cache for the corresponding MAC address before sending an ARP request. In the case of a cache miss, an ARP request should be sent to a target IP address about once every second until a reply comes in. If the ARP request is sent seven times with no reply, an ICMP destination host unreachable is sent back to the source IP as stated above.

In the case of an ARP request, a router should only send an ARP reply if the target IP address is one of the router's IP addresses. ARP requests are sent to the broadcast MAC address (`ff-ff-ff-ff-ff-ff`). ARP replies are sent directly to the requester's MAC address.

#### IP Packet Destinations

An incoming IP packet may be destined for one of a router's IP addresses, or it may be destined elsewhere. If it is sent to one of the router's IP addresses, the router should take the following actions, consistent with the section on protocols above:

* If the packet is an ICMP echo request and its checksum is valid, send an ICMP echo reply to the sending host.
* If the packet contains a TCP or UDP payload, send an ICMP port unreachable to the sending host.
* Otherwise, ignore the packet.

Packets destined elsewhere should be forwarded using normal forwarding logic.

`<a name="3-2"></a>`

### 3.2. Artifacts

#### TODO

Your router receives and sends Ethernet frames. The function to handle IPv4 forwarding is:

```c
const char* sr_handlepacket(struct sr_instance *sr, uint8_t* packet, int len, const char* recv_iface)
```

- This method, located in `sr_forward.c`, is called by the router each time a packet is received. The `packet` argument points to the packet buffer which contains the full packet including the Ethernet header. The name of the ingress interface is passed into the method in `recv_iface`.

> [!IMPORTANT]
>
> - Return value
>   - The name of the egress interface (obtained by LPM) if the packet hits a routing entry and should be forwarded (normal IPv4 forwarding).
>     - `packet` should be modified accordingly.
>   - `NULL` for any circumstance other than normal IPv4 forwarding.

#### Testing with Linux Network Interfaces and Namespaces

We provide a easy-to-use and easy-to-modify testing framework implemented with Linux network interfaces and namespaces.
Two pairs of virtual Ethernet interfaces `veth0`-`peer0` and `veth1`-`peer1` are created by `create_interface.sh`.
Virtual Ethernet pairs are considered as directly connected by a virtual wire.
Our configuration simulates the interfaces of the router and network topology as below.

```
            ------------------ 
            |                |
peer0 --- veth0   Router   veth1 --- peer1
            |                |   
            ------------------ 
```

> [!TIP]
> You are free to play with the testing framework. This means you can modify `create_interface.sh` and corresponding code pieces in the starter code to customize network configurations.
> For example, the starter code only creates two pairs of veth interfaces, but you can try three.
> You can also adjust the entries inside `rtable` and `arp_cache` to suit your configurations.
>
> Our Autograder will focus on your implementation of `sr_handlepacket`, e.g. by inputting certain parameters and checking the return value and `packet`, and may not use the exact same network configuration in the starter code. Please see "Caution" below.

> [!CAUTION]
>
> * Please ensure all your implementations are resided in `sr_forward.c`. Autograder will assume that `sr_handlepacket` is implemented within `sr_forward.c` and will test your implementation of the function.
> * Please DO NOT change the signature/prototype of `sr_handlepacket`, or it will lead to compilation failures.
>   * When you make your final submission, you should always assume definitions of all arguments of `sr_handlepacket` match the original definitions we provided in the starter code.

#### Routing Table File

An example routing table can be found in the `rtable` file.
Each line in the routing table (rtable) file is a routing entry and has the following format:

```
prefix        next_hop     netmask          interface
```

- prefix: target address.
- next_hop: gateway address for obtaining destination MAC (where ARP should be sent to).
- netmask: the mask that determines destination IP address together with prefix (using AND operation).
- interface: the physical interface to send the packet.

Below is an example of a routing table. The first entry is the default route that matches any packet. If a packet does not match other entries, it will be sent to 10.0.1.100 via eth3.

```
0.0.0.0       10.0.1.100   0.0.0.0          eth3
192.168.2.2   192.168.2.2  255.255.255.255  eth1
172.64.3.10   172.64.3.10  255.255.255.255  eth2
```

### Building and Running

You can build and run the starter code as follows:

```
make
bash run_router.sh
```

`<a name="subinstr"></a>`

## Submission Instructions

Your submission should contain:

* Part 1: a tarball named `p1.tar.gz`. It should contain:
  * `Makefile`(s) to compile all executables with one single `make` command.
  * The source code of all parts for `WTP`:
    * WTP Base part source code for `wSender` and `wReceiver`. (c or cpp code) All source files should be in the folder called `WTP-base`. Binary executables of `wSender` and `wReceiver` should be in the same directory after running `make`.
  * The submission tarball named `p1.tar.gz` can be created by running the command `tar acvf p1.tar.gz p1`, where `p1` is the name of your code directory.
  * Example final structure of `p1.tar.gz`
    * p1
      * Makefile
      * WTP-base
        * Makefile
        * [Your source codes]
      * starter_files
        * crc32.h
        * PacketHeader.h
* Part 2: a `p2.txt` that contains your answers.
* Part 3: `sr_forward.c`.

`<a name="ag"></a>`

## Autograder

Autograder for assginment 3 is at: [Autograder](http://projgw.cse.cuhk.edu.hk:2913/web/project/47).

It's advisable to create your own tests to verify the functionality of your sender and receiver to achieve complete and unaltered file transfers. Relying on autograder to debug your code is not recommended. Instead, you can try local debugging tools like gdb (e.g. `gdb --args ./wReceiver 8888 2 /tmp log.txt` for Part 1) to debug your code.

The autograder runs the following versions of gcc/g++, please make sure your code is compatible.

```
$ gcc --version
gcc (Ubuntu 11.2.0-16ubuntu1) 11.2.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ g++ --version
g++ (Ubuntu 11.2.0-16ubuntu1) 11.2.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

This assignment does not require specific environment dependencies, as long as you use `c` or `cpp` language to implement your code, and ensure that your `gcc` and `g++` versions are compatible with version `11.2.0` as the autograder shows. You can complete this assignment by using the same environment from Assignment 1's with virtual box if you like.

> [!Note]
>
> #### Reminder on possible contention in grading
>
> The grading procedure in autograder may be a bit slow, especially when many people submit it together. Please wait patiently for the grading procedure in autograder and reserve sufficient time before deadline. Also, your solution will timeout when there is a heavy burden in autograder, but that may not mean your code is wrong. Please re-submit it to see whether the same test case will have the same error, and do not wait until late near deadline to submit your code.

## Acknowledgements

This programming assignment is based on Assignment 3 and 4 from Umich EECS 489: Computer Networks, and Project 2 from UC Berkeley EE 122: Introduction to Communication Networks.
