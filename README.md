# CSCI4430 Computer Networks, Fall 2023

## Administrivia

### Schedule
**Lectures and tutorials on Wednesdays are swapped and different from CUSIS, so tutorials happen after all lectures of the week.**
- Lectures: 
  * Mon 2:30pm – 4:15pm, MMW LT2
  * Wed 3:30pm – 4:15pm, LSB LT6
- Tutorials:
  * Wed 4:30pm – 5:15pm, LSB LT6

### Team
| Member | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Xu, Hong (Henry)](https://henryhxu.github.io/) | Prof | Mon 10-12 pm, SHB 914. **By appointments only.** |
| [Ding, Wenlong](mailto:wlding@link.cuhk.edu.hk) | Head TA | Thu 1-3 pm, SHB 117. |
| [Wu, Shaofeng](mailto:sfwu22@cse.cuhk.edu.hk) | TA |  Tue 2-4 pm, SHB 117. |
| [Yang, Yitao](mailto:ytyang@cse.cuhk.edu.hk) | TA | Thu 10-12 am, SHB 117. |

### Piazza
The Piazza page for this course is [here](https://piazza.com/cuhk.edu.hk/fall2023/csci4430estr4120).
All communication about this course is done over Piazza. This includes questions, discussions, announcements, as well as private messages. 
The self-signup code is "4430 rocks!".

## Course outline
CSCI 4430 takes a top-down approach to explore how networks operate and how network applications work. We study how popular distributed systems such as video streaming, content distribution networks (CDNs), and cloud computing systems work in the application layer. We explore how these applications transfer data between their components and end users over the Internet using transport layer protocols such as TCP and UDP. We go deeper to understand what keeps the transport layer running; specifically, we look at how packets are routed and how routers work. Finally, we dive one more layer down to understand how the link layer transfer packets using Ethernet. In addition to cutting through the layers and covering the basics, we learn about the state-of-the-art topics in networking such as datacenter networks, software-defined networking (SDN), and (time permits) programmable networks.

From a practical point of view, we learn what sockets are and how to use them. And we write code. We write code to implement various protocols, to build client-server applications, video streaming applications, and transport protocols.

### Textbook (optional)
The course materials are based upon the following classic textbook of Kurose and Ross. In addition, many materials are also borrowed heavily from [Mosharaf Chowdhury](http://www.mosharaf.com/)'s [computer networks](https://github.com/mosharaf/eecs489) course with his permission. Credit is given whenever possible to Mosharaf and a lot of other folks, especially for the ESTR lecture notes.
- Computer Networking: A Top-Down Approach, 7th. (or earlier editions), by Jim Kurose and Keith Ross, 2016. ISBN 978-0133594140.

You may also want to check out this online book:
- [Computer Networks: A Systems Approach](https://book.systemsapproach.org/index.html), by Larry Peterson and Bruce Davie.

### Grading
| Assessment item | CSCI Weight | ESTR Weight
| :---------------- | :--- | :--- | 
| Assignments | 55% | 55%
| Tutorial Quizzes* | 5% | 0%
| Final Exam | 40% | 40%
| Project | 0% | 5%

\*: To encourage tutorial participation, quiz will be conducted at the tutorials randomly. We will randomly pick 5 tutorials and perform a quiz at the end of the tutorial. Each quiz is worth one mark.

## Schedules
<!--  Click on the topic to access the slides, and on the date to view the recording. -->

### Lectures
| Week | Date | Topic(s) |  Textbook Readings  | Additional Readings
| :---: |:----------- | :-----------------: |  :------------: | :------------: |
|1| Sep 4; 6 | [Intro and Overview](lec/lec1.pptx) |  1.1, 1.3, 1.4 |
|2| Sep 11; 13 | [Layering](lec/lec2.pptx); <br>[Sockets and HTTP](lec/lec3.pptx) | 1.5, 2.2, 2.4 | [End-to-end arguments <br>in system design](https://web.mit.edu/Saltzer/www/publications/endtoend/endtoend.pdf)
|3| Sep 18; 20 | [CDN, DNS](lec/lec4.pptx) | 2.2, 2.4
|4| Sep 25; 27 | [Video, datacenters](lec/lec5.pptx) |  2.6
|5| ~~Oct 2~~; Oct 4 | *National day*; [Video, datacenters](lec/lec5.pptx) | 2.6
|6| Oct 9; 11 | [Transport layer](lec/lec6.pptx) | 3.1–3.4
|7| Oct 16; 18 | [TCP Basics]; [Congestion control]
|8| ~~Oct 23~~; Oct 25 | [More on CC]
|9| Oct 30; Nov 1 | [Network layer and IP]
|10| Nov 6; 8 | [Routing basics]; [Intra-domain routing]
|11| Nov 13; 15 | [Inter-domain routing]
|12| Nov 20; 22 | [SDN]; [Link layer]
|13| Nov 27; ~~29~~ | [Advanced topics TBD], [Final review]; <br>*Travel to HotNets*

### Tutorials and Assignments
<!--  ~~11:59:59 p.m., Sat, Jan 29th~~ 18:00:00 p.m., Mon, Jan 31st -->
<!-- assignment-1 -->
<!-- []() -->
| Week | Date | Topic | TA | Assignment | Due |
| :---: | :------------------ | :-----: | :-------------: | :-----: | :-------------: |
| 1 | Sep 6  | [Socket programming](tutorial/T01/) | Shaofeng | [Assignment 1](assignment/assignment-1) | 11:59:59 p.m., Fri, Oct. 6th |
| 2 | Sep 13 |[Performance metrics](tutorial/T02/) | Shaofeng|||
| 3 | Sep 20 | [HTTP](tutorial/T03/) | Shaofeng|||
| 4 | Sep 27 | [Select programming](tutorial/T04/) | Yitao |||
| 5 | Oct 4  | HTTP Streaming and TCP | Yitao | Assignment 2| TBA |
| 6 | Oct 11 | HTTP Proxy and TCP | Yitao |||
| 7 | Oct 18 | TCP Congestion Control | Yitao |||
| 8 | Oct 25 |  UDP Socket programming | Wenlong |||
| 9 | Nov 1 | IP and Network | Shaofeng |||
| 10 | Nov 8 | WTP Introduction | Wenlong | Assignment 3 | TBA |
| 11 | Nov 15 | Intra-Domain Routing | Wenlong |||
| 12 | Nov 22 | Inter-Domain Routing | Wenlong |||
| 13 | Nov 29 | Link Layer | Wenlong |||


## Course policies
- Homework and project: 
  * No late submission.
  * Grace tokens: You have **2** grace tokens, each can be used to give you a 24-hr extension on one assignment. You can apply at most 1 grace token on each assignment at your own discretion. This gives you some flexibility to cope with your own schedule.
  * According to the University’s regulation, every assignment must be accompanied by a signed declaration of originality; submissions without it will receive zero mark.
  * The declaration form is available [here](https://www.cuhk.edu.hk/policy/academichonesty/Eng_htm_files_(2013-14)/declaration_en.doc).
- Lecture and tutorial:
  * Be on time. Set your mobile device to vibration/silient mode.
  * Feel free to ask questions and raise comments during the lecture, but we can only entertain short questions and discussions in-class.
  * Longer and deeper discussion and questions can happen in tutorials.
  * Follow University's regulations on COVID, including use of masks, hand sanitization, seating with social distance, etc.
