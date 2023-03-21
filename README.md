# CSCI4430/ESTR4120, Computer Networks (Spring 2023)

## Administrivia

### Schedule
- Lectures: 
  * Mon 12:30pm – 2:15pm, Basic Med Sci Building G18
  * Tue 4:30pm – 5:15pm, MMW LT1
  * ESTR4120: Tue 5:30pm - 6:15pm, MMW LT1
- Tutorials:
  * Thu 8:30am – 9:15am, MMW LT2
  * Thu 12:30pm – 1:15pm, Basic Med Sci Building G18

### Team
| Member | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Xu, Hong (Henry)](https://henryhxu.github.io/) | Prof | Mon 3-5 pm, SHB 914. **By appointments only.** |
| [Song, Qingyu](mailto:qysong21@cse.cuhk.edu.hk) | Head TA | Wed 9:30-11:30 am, SHB 117. |
| [Zhang, Jingze](mailto:zhang_jing_ze@link.cuhk.edu.hk) | TA | Tue 2:30-4:30 pm, SHB 117. |
| [Ding, Wenlong](mailto:wlding@link.cuhk.edu.hk) | TA | Wed 1:30 - 3:30 pm, SHB 117. |

### Piazza
The Piazza page for this course is [here](https://piazza.com/cuhk.edu.hk/spring2023/csci4430estr4120).
All communication about this course is done over Piazza. This includes questions, discussions, announcements, as well as private messages. 
The self-signup code is "4430 rocks!".

## Course outline
CSCI 4430 takes a top-down approach to explore how networks operate and how network applications work. We study how popular distributed systems such as video streaming, content distribution networks (CDNs), and cloud computing systems work in the application layer. We explore how these applications transfer data between their components and end users over the Internet using transport layer protocols such as TCP and UDP. We go deeper to understand what keeps the transport layer running; specifically, we look at how packets are routed and how routers work. Finally, we dive one more layer down to understand how the link layer transfer packets using Ethernet. In addition to cutting through the layers and covering the basics, we learn about the state-of-the-art topics in networking such as datacenter networks, software-defined networking (SDN), and (time permits) programmable networks.

From a practical point of view, we learn what sockets are and how to use them. And we write code. We write code to implement various protocols, to build client-server applications, video streaming applications, and transport protocols.

### Textbook (optional)
The course materials are based upon the following classic textbook of Kurose and Ross. In addition, many materials are also borrowed heavily from [Mosharaf Chowdhury](http://www.mosharaf.com/)'s [computer networks](https://github.com/mosharaf/eecs489) course with his permission. Credit is given whenever possible to Mosharaf and a lot of other folks.
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

### ESTR students
ESTR 4120 follows the same format as CSCI 4430, but with an additional project to be presented in the second half of the semester. The exams and quizzes will be the same as CSCI 4430.

Projects details ~~will be announced in a later time~~ can be found on [this page](project.md).

## Schedules
<!--  Click on the topic to access the slides, and on the date to view the recording. -->

### Lectures
| Week | Date | Topic(s) | ESTR  <br>Topic | Optional Readings  <br>from Textbook |
| :---: |:----------- | :-----------------: | :------------: | :------------: | 
|1| Jan 9-10 | [Intro and Overview](lec/lec1.pptx) | [Internet](lec/estr1.pptx) | 1.1, 1.3, 1.4
|2| Jan 16-17| [Layering](lec/lec2.pptx);  <br>[Sockets and HTTP](lec/lec3.pptx) | [HTTP, HTTPS, P2P](lec/estr2.pptx)  | 1.5, 2.2, 2.4
|3| Jan 30-31| [CDN, DNS](lec/lec4.pptx) | [CDN, Anycast](lec/estr3.pptx) | 2.2, 2.4
|4| Feb 6-7| [Video, cloud & datacenters](lec/lec5.pptx),  <br>[Transport layer](lec/lec6.pptx) | [ABR I](lec/estr4.pptx), [ABR II](lec/estr4-puffer.pdf) | 2.6, 3.1, 3.2, 3.3, 3.4
|5| Feb 13-14| [Transport layer](lec/lec6.pptx) | [RDMA](lec/estr5-rdma.ppt) | 3.1, 3.2, 3.3, 3.4
|6| Feb 20-21| [TCP basics](lec/lec7.pptx),  <br>[Congestion control](lec/lec8.pptx) | [RPC](lec/estr6-rpc.pdf) | 3.5, 3.6
|7| Feb 27-28| [Congestion control](lec/lec8.pptx), [More on CC](lec/lec9.pptx) | [DCTCP](lec/estr7.pptx) | 3.5, 3.6
|8| Mar 13-14| [More on CC](lec/lec9.pptx),  <br>[Network layer and IP](lec/lec10.pptx) | [NAT, Tunneling](lec/estr8.ppt) | 3.7; 4.1, 4.3.1, 4.3.2, 4.3.5
|9| Mar 20-21| [Network layer: IP routers](lec/lec11.pptx) | Network function virtualization | 4.2
|10| Mar 27-28 | [Routing fundamentals](lec/lec12.pptx),  <br>[Intra-domain routing](lecture/) | Programmable data plane | 5.1, 5.2, 5.3
|11| **Apr 3, 11** | [Inter-domain routing](lecture/),  <br>[SDN](lecture/) | Project presentations | 4.3.3, 5.4
|12| Apr 17, 18 | [Link layer](lecture/),  <br>[Final exam](lecture/) | Project presentations | 6.1, 6.3, 6.4
| | | [Course review](lecture/)

### Tutorials and Assignments
<!--  ~~11:59:59 p.m., Sat, Jan 29th~~ 18:00:00 p.m., Mon, Jan 31st -->
<!-- assignment-1 -->
<!-- []() -->
| Week | Date | Topic | Assignment | Due |
| :---: | :------------------ | :-----: | :-------------: | :-------------: |
| 1 | ~~Jan 12~~ | *No tutorial* | | |
| 2 | Jan 19 | [Socket programming](tutorial/T01/) | [Assignment 1](assignment/assignment-1) | 11:59:59 p.m., Mon, Feb. 13th |
| 3 | Feb 2 | [Performance metrics](tutorial/T02/) | ||
| 4 | Feb 9 | [HTTP](tutorial/T03/) | ||
| 5 | Feb 16 | [Select programming](tutorial/T04/) | [Assignment 2](assignment/assignment-2) | 11:59:59 p.m., Fri, Mar. 17th |
| 6 | Feb 23 |[HTTP Streaming and TCP](tutorial/T05/)|||
| 7 | Mar 2 |[HTTP Proxy and TCP](tutorial/T06/)|||
| 8 | Mar 16 |[TCP Congestion Control](tutorial/T07/)|||
| 9 | Mar 23 |[UDP Socket programming](tutorial/T08/)|[Assignment 3]()| |
| 10 | Mar 30 |[IP and Network](tutorial/T09/)|||
| 11 | ~~Apr 6~~ | *No tutorial* |||
| 12 | Apr 13 |[WTP assignemnt](tutorial/T10/)|||
| 13 | Apr 20 |[Routing](tutorial/T11/)|||


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
