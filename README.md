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

Projects details will be announced in a later time.

## Schedules
Click on the topic to access the slides, and on the date to view the recording. 

### Lectures
| Week | Topic(s) | ESTR Topic | Optional Readings from Textbook |
| :-----------: | :-----------------: | :------------: | :------------: | 
| 1 | [Intro and Overview](lecture/) |  | 1.1, 1.3, 1.4
| 2 | [Layering](lecture/); [Sockets and HTTP](lecture/) |  | 1.5, 2.2, 2.4
| 3 | [CDN, DNS](lecture/) |  | 2.2, 2.4
| 4 | [Video, cloud & datacenters](lecture/), [Transport layer](lecture/) |  | 2.6, 3.1, 3.2, 3.3, 3.4
| 5 | [Transport layer](lecture/) |  | 3.1, 3.2, 3.3, 3.4
| 6 | [TCP basics](lecture/), [Congestion control](lecture/) |  | 3.5, 3.6
| 7 | [Congestion control](lecture/) |  | 3.5, 3.6
| 8 | [More on CC](lecture/), [Network layer and IP](lecture/) |  | 3.7; 4.1, 4.3.1, 4.3.2, 4.3.5
| 9 | [Network layer: IP routers](lecture/) |  | 4.2
| 10 | [Routing fundamentals](lecture/), [Intra-AS routing](lecture/) |  | 5.1, 5.2, 5.3
| 11 | [Inter-domain routing](lecture/), [BGP](lecture/) |  | 4.3.3, 5.4
| 12 | [Link layer](lecture/) |  | 6.1, 6.3
| 13 | [Link layer wrap-up](lecture/), [Final exam](lecture/) |  | 6.4
| | [Course review](lecture/)

### Tutorials and Assignments
<!--  ~~11:59:59 p.m., Sat, Jan 29th~~ 18:00:00 p.m., Mon, Jan 31st -->
<!-- assignment-1 -->
<!-- []() -->
| Week | Topic | Schedule | Assignment | Due |
| :---: | :------------------: | :-----: | :-------------: | :-------------: |
| 1 | *No tutorial* | ~~Jan 12~~ | | |
| 2 | [Socket programming](tutorial/T01/) | Jan 19 | [Assignment 1]() |  |
| 3 | [Performance metrics](tutorial/T02/) | Feb 2 | ||
| 4 | [HTTP](tutorial/T03/) | Feb 9 | ||
| 5 | [Select programming](tutorial/T04/) | Feb 16 | [Assignment 2]() |  |
| 6 |[HTTP Streaming and TCP](tutorial/T05/)| Feb 23 |||
| 7 |[HTTP Proxy and TCP](tutorial/T06/)| Mar 2 |||
| 8 |[TCP Congestion Control](tutorial/T07/)| Mar 16 |||
| 9 |[UDP Socket programming](tutorial/T08/)| Mar 23 |[Assignment 3]()| |
| 10 |[IP and Network](tutorial/T09/)| Mar 30 |||
| 11 | *No tutorial* | ~~Apr 6~~ |||
| 12 |[WTP assignemnt](tutorial/T10/)| Apr 13 |||
| 13 |[Routing](tutorial/T11/)| Apr 20 |||


## Course policies
- Homework and project: 
  * No late submission.
  * Grace tokens: You have **2** grace tokens, each can be used to give you a 24-hr extension on one assignment. You can apply at most 1 grace token on each assignment at your own discretion. This gives you some flexibility to cope with your own schedule.
  * According to the University’s regulation, every assignment must be accompanied by a signed declaration of originality; submissions without it will receive zero mark.
  * The declaration form is available [here](declaration_en.doc).
- Lecture and tutorial:
  * Be on time. Set your mobile device to vibration/silient mode.
  * Feel free to ask questions and raise comments during the lecture, but we can only entertain short questions and discussions in-class.
  * Longer and deeper discussion and questions can happen in tutorials.
  * Follow University's regulations on COVID, including use of masks, hand sanitization, seating with social distance, etc.
