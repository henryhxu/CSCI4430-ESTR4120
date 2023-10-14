# Assignment 2: Video Streaming via CDN

### Due: Nov. 5th, 2023 at 11:59 PM

## Table of contents
* [Overview](#overview)
* [Clarifications](#clarifications)
* [Environment Setup](#environment)
* [Task1](#task1): Bitrate Adaptation in HTTP Proxy
* [Task2](#task2): Load Balance in HTTP Proxy
* [Bonus Task](#bonus_task): DNS Load Balancing
* [Development and Testing Advice](#testing)
* [Submission Instructions](#submission-instr)
* [Autograder](#autograder)

<a name="overview"></a>

## Overview

Video traffic dominates the Internet. In this project, you will explore how video content distribution networks (CDNs) work. In particular, you will implement adaptive bitrate selection and an HTTP proxy server to stream video from the closest server to a given client at high bit rates.

<img src="real-CDN.png" title="Video CDN in the wild" alt="" width="350" height="256"/>

### Video CDNs in the Real World
The figure above depicts a high-level view of what this system looks like in the real world. Clients trying to stream a video first issue a DNS query to resolve the service's domain name to an IP address for one of the CDN's content servers. The CDN's authoritative DNS server selects each client's “best” content server. (To simplify our assignment, we do not need to implement the DNS server except for the bonus part.)

Once the client has the IP address for one of the content servers, it begins requesting chunks of the video the user requested. The video is encoded at multiple bitrates; as the client player receives video data, it calculates the throughput of the transfer and requests the highest bitrate the connection can support.

### Video CDN in this Assignment
Implementing an entire CDN is difficult; instead, you'll focus on a simplified version. First, your entire system will run on one host and rely on mininet to run several processes with arbitrary IP addresses on one machine. Mininet will also allow you to assign arbitrary link characteristics (bandwidth and latency) to each pair of “end hosts” (processes).

<img src="our-CDN-noDNS.png" title="Video CDN in assignment 2" alt="" width="330" height="111"/>

In the figure above, you'll write the gray-shaded components (the proxy).

**Browser.** You'll use an off-the-shelf web browser (Firefox) to play videos served by your CDN (via your proxy).

**Proxy.** Rather than modify the video player itself, you will implement adaptive bitrate selection in an HTTP proxy. The player requests chunks with standard HTTP GET requests; your proxy will intercept these and modify them to retrieve whichever bitrate your algorithm deems appropriate.

**Web Server.** Video content will be served from an off-the-shelf web server (Apache). As with the proxy, you will run multiple instances of Apache on different IP addresses to simulate a CDN with several content servers.

To summarize, in this assignment, you will implement the "Bitrate Adaptation in HTTP Proxy" which will determine bitrate for the played video.

## Learning Outcomes

After completing this programming assignment, students should be able to:

* Explain how HTTP proxies and video CDNs work
* Create topologies and change network characteristics in Mininet to test networked systems

<a name="clarifications"></a>
## Clarifications

* For the proxy, you will need to parse some HTTP traffic. To make your life easier for this project, you don't need to be concerned about parsing all the information in these HTTP messages. There are only two things that you need to care about searching for: `\r\n\r\n` and `Content-Length`. The former is used to denote the end of an HTTP header, and the latter is used to signify the size of the HTTP body in bytes.
* The proxy should be able to support multiple browsers playing videos simultaneously. This means you should test with multiple browsers all connecting to the same proxy. In addition you should also test with multiple proxies each serve some number of browser(s), in order to make sure that each proxy instance does not interfere with others. 
* While testing the proxy, you may notice that one browser may sometimes open multiple connections to your proxy server. Your proxy should still continue to function as expected in this case. In order to account for these multiple connections, you may use the browser IP address to uniquely identify each connection (this implies that while testing your proxy server, each browser will have a unique IP address. For example, only one browser will have an IP address of 10.0.0.2).
* Throughput should be measured on each fragment. For example, throughput should be calculated separately for both Seg1-Frag1 and Seg1-Frag2.
* You are recommended to test your code with Mininet. But testing with Mininet is not necessary in the final grading process.

<a name="environment"></a>

## Environment Setup
[We will provide a VM](https://drive.google.com/file/d/19ZYz86GZf1qx27KOkGRwY1gwem2eCH9E/view?usp=sharing) that has all the components you need to get started on the assignment. While we tried to make the base VM work for all the projects, unfortunately, this didn't come to fruition. Starting fresh also ensures a working environment free from accidental changes that may have been made in the first project.

**We encourage you to use VMware instead of Virtual Box for this and the following projects, which is more compatible with different OS and is free with a personal license.** For Windows and Linux users, we recommend [VMware Workstation Player](https://www.vmware.com/products/workstation-player/workstation-player-evaluation.html). For Mac users, we recommend [VMware Fusion Player](https://customerconnect.vmware.com/web/vmware/evalcenter?p=fusion-player-personal).

You may install tools that suit your workflow. **But DO NOT update the software in the VM.** You can find a guide on [how to troubleshoot the VM here](https://eecs388.org/vmguide.html#troubleshooting).

This VM includes mininet, Apache, and all the files we will be streaming in this project. Both the username and password for this VM are `csci4430`. To start the Apache server, simply run the python script we provide by doing the following:

`python start_server.py <host_number>`

Here `<host_number>` is a required command line argument that specifies what host you are running on Mininet. This is important as if you're running on h1 in Mininet (which is given the IP address 10.0.0.1), passing in `1` into the `<host_number>` argument will help ensure that the Apache server instance will be bound to the 10.0.0.1 IP address. The `<host_number>` argument must be between 1 and 8.

The Apache servers would not automatically stop after mininet is closed. You MUST manually stop the server. To stop the Apache server, run:

`sudo killall httpd`


Like any HTTP web server (not HTTPS) these instances of Apache will be reachable on TCP port `80`. For simplicity, all of our web traffic for this assignment will be unencrypted and be done over HTTP.

For this project, we will be using an off the shelf browser (in this case, Firefox). To launch Firefox for this project, run the following command:

`python launch_firefox.py <profile_num>`

Here `<profile_num>` is a required command line argument that specifies the instance of Firefox you are launching. We support launching profiles 1-8, however, should you feel the need to test more thoroughly, you can launch it with a different number and simply create a new profile as needed. To ensure a separate connection for each instance of Firefox, we recommend that you launch Firefox with a different profile number (otherwise you might notice that different Firefox instances will sometimes share a connection with your proxy server).

Also make sure you don't modify the firefox profiles we set up as well as the configuration files inside the current firefox build directory.

You are highly recommended to test your code in Mininet. To be clear, you launch the web server, the firefox browser, and the proxy server all inside Mininet. 

You may create your own Mininet topology script for testing the package as a whole. A simple Starfish topology (all hosts connected to one switch in the middle) should suffice for testing.

> *NOTE: For this project, we are disabling caching in the browser. If you do choose to create a new profile, please double check if caching is disabled by going to the `about:config` page and setting both `browser.cache.disk.enable` and `browser.cache.memory.enable` to `false`.*

<a name="task1"></a>

## Task1: Bitrate Adaptation in HTTP Proxy (Mandatory Part)

Many video players monitor how quickly they receive data from the server and use this throughput value to request better or lower quality encodings of the video, aiming to stream the highest quality encoding that the connection can handle. Instead of modifying an existing video client to perform bitrate adaptation, you will implement this functionality in an HTTP proxy through which your browser will direct requests.

You are to implement a simple HTTP proxy, `miProxy`. It accepts connections from web browsers, modifies video chunk requests as described below, opens a connection with the resulting IP address, and forwards the modified request to the server. Any data (the video chunks) returned by the server should be forwarded, *unmodified*, to the browser.

`miProxy` should listen for browser connections on `INADDR_ANY` on the port specified on the command line. It should then connect to a web server specified on the command line. 

<img src="proxy-overview.png" title="Video CDN in the wild" alt="" width="534" height="171"/>

`(assign ephemeral)` is referring to the fact that the kernel will pick the proxy's TCP port when it connects to the web server's port `80`. Nothing more than the proxy calling `connect()` is happening here.

`miProxy` should accept multiple concurrent connections from clients (Firefox web browser) using `select()` and be able to handle the required HTTP 1.1 requests for this assignment (e.g., HTTP `GET`).

The picture above shows `miProxy` connected to multiple web servers. However, in our assignment, each proxy will be connected only one server which is specified in the running command.

We have cover the basic usage of `select()` in the tutorial.

> *Note: A good resource for socket programming is [Beej's Guide to Network Programming Using Internet Sockets](https://beej.us/guide/bgnet/html/).*

### Throughput Calculation

Your proxy measure the the throughput between the server and ifself to determine the bitrate. Your proxy should estimate each stream's throughput once per chunk. Note the start time of each chunk when your proxy started receiving the chunk from the server and save another timestamp when you have finished receiving the chunk from the server. Given the size of the chunk, you can now compute the throughput by dividing chunk size by time window.

Each video is a sequence of chunks. To smooth your throughput estimation, you should use an exponentially-weighted moving average (EWMA). Every time you make a new measurement (as outlined above), update your current throughput estimate as follows:

`T_cur = alpha * T_new + (1 - alpha) * T_cur`

The constant `0 ≤ alpha ≤ 1` controls the tradeoff between a smooth throughput estimate (`alpha` closer to 0) and one that reacts quickly to changes (`alpha` closer to 1). You will control `alpha` via a command line argument. When a new stream starts, set `T_cur` to the lowest available bitrate for that video.

### Choosing a Bitrate

Once your proxy has calculated the connection's current throughput, it should select the highest offered bitrate the connection can support. For this project, we say a connection can support a bitrate if the average throughput is at least 1.5 times the bitrate. For example, before your proxy should request chunks encoded at 1000 Kbps, its current throughput estimate should be at least 1.5 Mbps.

Your proxy should learn which bitrates are available for a given video by parsing the manifest file (the ".f4m" initially requested at the beginning of the stream). The manifest is encoded in XML; each encoding of the video is described by a `<media>` element, whose bitrate attribute you should find.

Your proxy replaces each chunk request with a request for the same chunk at the selected bitrate (in Kbps) by modifying the HTTP request’s `Request-URI`. Video chunk URIs are structured as follows:

`/path/to/video/<bitrate>Seg<num>-Frag<num>`

For example, suppose the player requests fragment 3 of chunk 2 of the video `big_buck_bunny.f4m` at 500 Kbps:

`/path/to/video/500Seg2-Frag3`

To switch to a higher bitrate, e.g., 1000 Kbps, the proxy should modify the URI like this:

`/path/to/video/1000Seg2-Frag3`

> **IMPORTANT:** When the video player requests `big_buck_bunny.f4m`, you should instead return `big_buck_bunny_nolist.f4m`. This file does not list the available bitrates, preventing the video player from attempting its own bitrate adaptation. Your proxy should, however, fetch `big_buck_bunny.f4m` for itself (i.e., don’t return it to the client) so you can parse the list of available encodings as described above. Your proxy should keep this list of available bitrates in a global container (not on a connection by connection basis).
> 
> *Note: In Assignment 2, you can find the files that will be transferred by the server in the directory `/var/www`. The `f4m` files for the video `big_buck_bunny.f4m` and `big_buck_bunny_nolist.f4m` are located in the directory `/var/www/vod`. You can check their content if you find it useful.*

<a name="task2"></a>

## Task2: Load Balance in HTTP Proxy (Mandatory Part)
To spread the load of serving videos among a group of servers, most CDNs perform some kind of load balancing. In this task, you will implement load balancing for our HTTP proxy server using a simple **round-robin**. 

It takes a configuration file as input containing a list of video server IP addresses. You need to assign these IP addresses to each video streaming request round-robin and cycle back to the beginning when all the IP addresses have been exhausted.

Example text file format in `server.txt`:

```
10.0.0.1
10.0.0.2
10.0.0.3
```

Assuming we have three clients request video streaming through the proxy. The IP addresses of three clients are `10.0.0.5`, `10.0.0.6`, `10.0.0.7`. Your proxy needs to set up connections from client1 (`10.0.0.5`) to server1 (`10.0.0.1`), client2 (`10.0.0.6`) to server2 (`10.0.0.2`), and client3 (`10.0.0.7`) to server3 (`10.0.0.3`).

<a name="bonus_task"></a>

## Bonus Task: DNS Load Balancing (Optional Part)

This part is **optional**, but you will receive some bonus marks after finishing this part. 

Although DNS resolution can be done by a proxy server (just like what we do in [Task2](#task2)). However, decoupling the Proxy server from a dedicated DNS server is a more common and recommended practice to suit the scale of today's system better and provide greater performance and security guarantee.

A common technique is configuring the CDN's authoritative DNS server to resolve a single domain name to one out of a set of IP addresses belonging to replicated content servers. The DNS server can use various strategies to spread the load, e.g., round-robin, shortest geographic distance, or current server load (which requires servers to report their statuses to the DNS server periodically). 

In this part, you will write a simple DNS server that implements load balancing in **round-robin** method. 

### DNS query

1. Each time `miProxy` receives a connection from browser, it will query the DNS `nameserver` for the IP address of the server. 
1. The format of DNS quesy message can be determined by yourself. (**Remember to use `htonl` and `ntohl` when sending/receiving integers over the network!**)
1. Your `nameserver` should record each query based on the log format specified in "nameserver logging".

### Round-Robin Load Balancer

You will implement `nameserver` as a simple round-robin based DNS load balancer. It should take as input a list of video server IP addresses on the command line; it responds to each request by returning the next IP address in the list, cycling back to the beginning when the list is exhausted.

`nameserver` will bind to an IP address and port specified as command line arguments. 

Example text file format in `sample_round_robin.txt`:

```
10.0.0.1
10.0.0.2
10.0.0.3
```


## Running `miProxy`

### Manadatory part

For **MANDATORY** part (Task1 and Task2), to run the miProxy, please use with the following command. 

`./miProxy --nodns <listen-port> <servers-config> <alpha> <log>`

* `--nodns` Do not use DNS server.
* `listen-port` The TCP port your proxy should listen on for accepting connections from your browser.
* `servers-config` A text file containing one Apache server IP per line. This argument specifies where the proxy should request video chunks. Each server is reachable at TCP port `80`.
* `alpha` A float in the range [0, 1]. Use this as the coefficient in your EWMA throughput estimate.
* `log` The file path to which you should log the messages as described below.

#### miProxy Logging

`miProxy` must create a log of its activity in a very particular format. If the log file already exists, `miProxy` overwrites the log. *After each chunk-file response from the web server*, it should append the following line to the log:

`<browser-ip> <chunkname> <server-ip> <duration> <tput> <avg-tput> <bitrate>`

* `broswer-ip` IP address of the browser issuing the request to the proxy.
* `chunkname` The name of the file your proxy requested from the web server (that is, the modified file name in the modified HTTP GET message).
* `server-ip` The IP address of the server to which the proxy forwarded this request.
* `duration` A floating point number representing the number of seconds it took to download this chunk from the web server to the proxy.
* `tput` The throughput you measured for the current chunk in Kbps.
* `avg-tput` Your current EWMA throughput estimate in Kbps.
* `bitrate` The bitrate your proxy requested for this chunk in Kbps.

> *Note: for simplicity, arguments will appear exactly as shown above during testing and grading. Error handling with the arguments is not explicitly tested but is highly recommended. At least printing the correct usage if something goes wrong is worthwhile.*
> 
> *Also note: both Mandatory and Bouns part have the same logging format!*
> 
### Bouns part

For **BOUNS** part, you need to write a DNS server and modify the miProxy. Your proxy should obtain the web server's IP address by querying your DNS server for the IP address of the web server. Please use the following command.

`./miProxy --dns <listen-port> <dns-ip> <dns-port> <alpha> <log>`

* `--dns` This flag indicates the proxy will use DNS to obtain the web server IP.
* `listen-port` The TCP port your proxy should listen on for accepting connections from your browser.
* `dns-ip` IP address of the DNS server.
* `dns-port` Port number DNS server listens on.
* `alpha` A float in the range [0, 1]. Use this as the coefficient in your EWMA throughput estimate.
* `log` The file path to which you should log the messages as described below.


> 
> *Note: we are using our own implementation of DNS on top of TCP, not UDP.*

#### Nameserver

To operate `nameserver`, it should be invoked as follows:

`./nameserver --rr <port> <servers> <log>`

* `--rr` This flag specifies that `nameserver` will operate in the round-robin based load balancing scheme.
* `port` The port on which your server should listen.
* `servers` A text file containing a list of IP addresses, one per line, belonging to content servers if `--rr` is specified. 
* `log` The file path to which you should log the messages as described below.

> *Note: for simplicity, arguments will appear exactly as shown above during testing and grading. Error handling with the arguments is not explicitly tested but is highly recommended. At least printing the correct usage if something went wrong is worthwhile.*





<a name="testing"></a>

## Development and Testing Advice

Assignment 2 is group projects for 2 people. Please be sure to submit your team information on the [AutoGrader](http://projgw.cse.cuhk.edu.hk:2913/web/) website.


### Getting Started

We present a brief framework for [miProxy implementation in C](./starter_files/miProxy/miProxy.c). This framework supports parsing basic command line arguments, along with some helper functions and variables.

However, if desired, you may choose to implement miProxy using CPP from scratch.


### Test miProxy

To play a video through your proxy, you launch an instance of the Apache server, launch Firefox (see above), and point the browser on your VM to the URL `http://<proxy_ip_addr>:<listen-port>/index.html`.

To test your `miPorxy` implementation, you can try the following commands (for reference only).

``` shell
# compile
make 
# launch Apache server
sudo python start_server.py 1
# launch miProxy
sudo ./miProxy --nodns 8888 server.txt 0.5 test.log
# launch multiple firefox clients (manually type localhost:8888)
sudo python launch_firefox.py 1 
sudo python launch_firefox.py 2 
# you can see the video are playing on different firefox clients
```
> *Note: Remember to reset the time in the VM using `sudo sudo date +%Y%m%d -s 20180101` before testing!*

### Test Cases

The detailed test case will be released halfway through the assignment.

<a name="submission-instr"></a>

## Submission Instructions

The submission instructions will be released along with the test cases.

> **IMPORTANT**: Any form of plagiarism, including code that resembles previous years' or others' work, will result in a score of 0.

<a name="autograder"></a>

## Autograder

The autograder will be released roughly halfway through the assignment. You are encouraged to design tests by yourselves to fully test your proxy server. You should *NEVER* rely on the autograder to debug your code. Clarifications on the autograder will be added in this section:

Our autograder runs the following versions of gcc/g++, please make sure your code is compatible.
```
$ gcc --version
gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions. There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ g++ --version
g++ (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions. There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## Acknowledgements

This programming assignment is based on Peter Steenkiste's Project 3 from CMU CS 15-441: Computer Networks.
