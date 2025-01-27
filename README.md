# CSCI4430 Computer Networks, Spring 2025

## Administrivia

### Schedule

- Lectures: 
  * Mon 4:30pm – 6:15pm, Y.C. Liang Hall 103
  * Wed 12:30pm – 1:15pm, LSB LT2
- Tutorials:
  * Wed 1:30pm – 2:15pm, LSB LT2

### Team
| Member | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Xu, Hong (Henry)](https://henryhxu.github.io/) | Prof | Tue 10-12 pm, SHB 914. **By appointments only.** |
| [Wu, Shaofeng](mailto:sfwu22@cse.cuhk.edu.hk) | Head TA | Thu 12:30-2:30 pm, SHB 117. |
| [Yang, Yitao](mailto:ytyang@cse.cuhk.edu.hk) | TA | Fri 2:30-4:30 pm, SHB 117 | 
| [Feng, Yicheng](mailto:yichengfeng@link.cuhk.edu.hk) | TA | Wed 2:30-4:30 pm, SHB 904. |

### Piazza
- The Piazza page for this course is: [https://piazza.com/cuhk.edu.hk/spring2025/csci4430](https://piazza.com/cuhk.edu.hk/spring2025/csci4430).
- The self-signup code is "cuhk_networking". You may associate your account with multiple emails, so you can receive notifications from all of them.
- All communication about this course is done over Piazza. This includes questions, discussions, announcements, as well as private messages, about all matters of this course. 
- Please use Piazza for all communication and do NOT email the teaching team directly.
- No announcements will be made from Blackboard.

## Course outline
CSCI 4430 takes a top-down approach to explore how networks operate and how network applications work. We study how popular distributed systems such as video streaming, content distribution networks (CDNs), and cloud computing systems work in the application layer. We explore how these applications transfer data between their components and end users over the Internet using transport layer protocols such as TCP and UDP. We go deeper to understand what keeps the transport layer running; specifically, we look at how packets are routed and how routers work. Finally, we dive one more layer down to understand how the link layer transfer packets using Ethernet. In addition to cutting through the layers and covering the basics, we learn about the state-of-the-art topics in networking such as datacenter networks, software-defined networking (SDN), and (time permits) programmable networks.

From a practical point of view, we learn what sockets are and how to use them. And we write code. We write code to implement various protocols, to build client-server applications, video streaming applications, and transport protocols.

### Textbook (optional)
The course materials are based upon the following classic textbook of Kurose and Ross. In addition, many materials are also borrowed heavily from [Mosharaf Chowdhury](http://www.mosharaf.com/)'s [computer networks](https://github.com/mosharaf/eecs489) course with his permission. Credit is given whenever possible to Mosharaf and a lot of other folks, especially for the ESTR lecture notes.
- Computer Networking: A Top-Down Approach, 7th. (or earlier editions), by Jim Kurose and Keith Ross, 2016. ISBN 978-0133594140.

You may also want to check out this online book:
- [Computer Networks: A Systems Approach](https://book.systemsapproach.org/index.html), by Larry Peterson and Bruce Davie.

### Grading
| Assessment item | CSCI Weight | 
| :---------------- | :--- | 
| Assignments | 45% | 
| Tutorial Quizzes* | 5% |
| Final Exam | 50% | 

\*: To encourage tutorial participation, quiz will be conducted at the tutorials randomly. We will randomly pick 5 tutorials and perform a quiz at the end of the tutorial. Each quiz is worth one mark.

## Schedules
<!--  Click on the topic to access the slides, and on the date to view the recording. -->

### Lectures
\*: Zoom recording is provided for Jan 27 lecture due to CNY holiday
| Week | Date | Topic(s) |  Textbook Readings  | Additional Readings
| :---: |:----------- | :-----------------: |  :------------: | :------------: |
|1| Jan 6; 8 | [Intro and Overview](lectures/lec1.pptx) |  1.1, 1.3, 1.4 |
|2| Jan 13; 15 | [Layering](lectures/lec2.pptx); <br>[Sockets and HTTP](lectures/lec3.pptx) | 1.5, 2.2, 2.4 | [End-to-end arguments <br>in system design](https://web.mit.edu/Saltzer/www/publications/endtoend/endtoend.pdf)
|3| Jan 20; 22 | [CDN, DNS](lectures/lec4.pptx) | 2.2, 2.4
|4| [Jan 27](https://cuhk.zoom.us/rec/share/YWUR_7PZ3Dt5F7VDbfluub58wMF21uAnup5RGDPNhe1YDYuaE1DBPZ6aHhNqreSp.P5r8k4rkzYQijJoP) | [Video, datacenters](lectures/lec5.pptx) |  2.6


### Tutorials and Assignments
<!--  ~~11:59:59 p.m., Sat, Jan 29th~~ 18:00:00 p.m., Mon, Jan 31st -->
<!-- assignment-1 -->
<!-- []() -->
| Week | Date | Topic | TA | Assignment | Due |
| :---: | :------------------ | :-----: | :-------------: | :-----: | :-------------: |
| 1 | Jan 8  | [Socket programming](tutorial/T01/) | Yicheng | [Assignment 1](assignment/assignment-1) | 11:59:59 p.m., Sat, Feb. 1st |
| 2 | Jan 15 |[Performance metrics](tutorial/T02/) | Yicheng |||
| 3 | Jan 22 | [HTTP](tutorial/T03/) | Yicheng |||


## Course policies
- Assignments:
  * We use Autograder as the only submission entry of all assignments by default. Please refer to annoucements on Piazza for any special scenario.
  * No late submission. Late submissions result in zero marks.
  * "Make-up" submissions after deadline are considered as late submissions and we do not accept any of these submissions to ensure fairness. "Make-up" submissions include but are not limited to the following scenarios:
      * Forget to submit assignment to Autograder and attempt to submit the assignment via email after deadline. 
      * Attempt to submit a newer version of the assignment via email after deadline.
      * ...
  * Grace tokens: You have **2** grace tokens, each can be used to give you a 24-hr extension on one assignment. You can apply at most 1 grace token on each assignment at your own discretion. This gives you some flexibility to cope with your own schedule.
  * According to the University’s regulation, every assignment must be accompanied by a signed declaration of originality; submissions without it will receive zero marks.
  * The declaration form is available [here](https://www.cuhk.edu.hk/policy/academichonesty/Eng_htm_files_(2013-14)/declaration_en.doc).
  * Each assignment may have its own specific submission instructions. Failing to follow those instructions will prevent us from locating your submission and grading it, leading to zero marks.
  * Each assignment, after the mark is released, comes with a one-week "consoling" period when students can approach the [marking TAs](#tutorials-and-assignments) to clarify their mistakes or any other reasons that may justify re-marking their solution. After the consoling period, the corresponding assignment marks are regarded as final and will not be changed. No further "appeal" requests are allowed after the consoling period.
- Lecture and tutorial:
  * Be on time. Set your mobile device to vibration/silient mode.
  * Be respectiful and considerate to other partipants of the class, including all students, and members of the teaching team.
  * Feel free to ask questions and raise comments during the lecture.
  * Longer and deeper discussion and questions can happen in tutorials.
  * Follow University's regulations on COVID, including use of masks, hand sanitization, seating with social distance, etc.
