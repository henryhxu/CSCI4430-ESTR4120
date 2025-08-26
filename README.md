# CSCI4430/ESTR4120 Computer Networks, Fall 2025 (term 1)

## Administrivia

### Schedule

- Lectures: 
  * Mon 3:30pm – 5:15pm, Y.C. Liang Hall 103
  * Tue 10:30am – 11:15am, Lee Shau Kee LT3
  * Tue 9:30am - 10:15am, Lee Shau Kee LT3 (ESTR)
- Tutorials:
  * Tue 11:30am – 12:15pm, Lee Shau Kee LT3

### Team
| Member | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Xu, Hong (Henry)](https://henryhxu.github.io/) | Prof | Mon 9-10am, Tue 1-2 pm, SHB 914. **By appointments only.** |
| [Feng, Yicheng](mailto:yichengfeng@link.cuhk.edu.hk)  | Head TA | , SHB 904. |
| [Wu, Shaofeng](mailto:sfwu22@cse.cuhk.edu.hk) | TA | , SHB 904. |
| [Deng, Yangtao](mailto:ytdeng25@cse.cuhk.edu.hk) | TA | , SHB 117. |

### Piazza
- The Piazza page for this course is: [https://piazza.com/cuhk.edu.hk/fall2025/csci4430estr4120](https://piazza.com/cuhk.edu.hk/fall2025/csci4430estr4120).
- The self-signup code is "4430_rocks!". You may associate your account with multiple emails, so you can receive notifications from all of them.
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
\*: Zoom recording is provided for Jan 27 lecture due to CNY holiday, and for Apr 16 lecture.

| Week | Date | Topic(s) |  Textbook Readings  | Additional Readings
| :---: |:----------- | :-----------------: |  :------------: | :------------: |
|1| Jan 6; 8 | [Intro and Overview](lectures/lec1.pptx) |  1.1, 1.3, 1.4 |
|2| Jan 13; 15 | [Layering](lectures/lec2.pptx); <br>[Sockets and HTTP](lectures/lec3.pptx) | 1.5, 2.2, 2.4 | [End-to-end arguments <br>in system design](https://web.mit.edu/Saltzer/www/publications/endtoend/endtoend.pdf)
|3| Jan 20; 22 | [CDN, DNS](lectures/lec4.pptx) | 2.2, 2.4
|4| [Jan 27](https://cuhk.zoom.us/rec/share/YWUR_7PZ3Dt5F7VDbfluub58wMF21uAnup5RGDPNhe1YDYuaE1DBPZ6aHhNqreSp.P5r8k4rkzYQijJoP)\*; Feb 5 | [Video, datacenters](lectures/lec5.pptx) |  2.6
|5| Feb 10; 12 | [Transport layer](lectures/lec6.pptx) | 3.1–3.4
|6| Feb 17; 19 | [TCP Basics](lectures/lec7.pptx) |3.5, 3.6 | RFCs in the ppt
|7| Feb 24; 26 | [Congestion control](lectures/lec8.pptx) | 3.5, 3.6 | [BBR](https://github.com/google/bbr)
|8| Mar 10; 12 | [More on CC](lectures/lec9.pptx); <br>[Network layer](lectures/lec10.pptx) | 3.7, 4.1, 4.3.1, 4.3.2, 4.3.5 | [DCTCP](https://people.csail.mit.edu/alizadeh/papers/dctcp-sigcomm10.pdf)
|9| Mar 17; 19 | [Routing foundamentals](lectures/lec11.pptx) | 5.1, 5.2, 5.3 | [How Dijkstra's Algorithm Works](https://www.youtube.com/watch?v=EFg3u_E6eHU)
|10| Mar 24; 26 | [Intra-domain routing](lectures/lec12.pptx); <br>[Inter-domain routing](lectures/lec13.pptx) | 5.1, 5.2, 5.3 |
|11| Mar 31; no class | [Inter-domain routing](lectures/lec13.pptx) | 5.4
|12| Apr 7; 9 | [SDN](lectures/lec14.pptx); [Link layer](lectures/lec15.pptx) | 4.4, 5.5, 6.1, 6.3, 6.4
|13| Apr 14, [16](https://cuhk.zoom.us/rec/share/eWqr3xyJjT2MOSn5JMQuaNLt0GlFNm_Xz00QxnTcsSiGV-Eq7u3GuyC2kMvQMVZm.dCobzzOMTL5uCcFI)\* | [Link layer](lectures/lec15.pptx); <br>[Final review](lectures/review.pptx)| 6.1, 6.3, 6.4 | [CTE](lectures/CSCI4430_CTE.pptx)

### Tutorials and Assignments
<!--  ~~11:59:59 p.m., Sat, Jan 29th~~ 18:00:00 p.m., Mon, Jan 31st -->
<!-- assignment-1 -->
<!-- []() -->
| Week | Date | Topic | TA | Assignment | Due |
| :---: | :------------------ | :-----: | :-------------: | :-----: | :-------------: |
| 1 | Jan 8  | [Socket programming](tutorial/T01/) | Yicheng | [Assignment 1](assignment/assignment-1) | 11:59:59 p.m., Sat, Feb. 1st |
| 2 | Jan 15 |[Performance metrics](tutorial/T02/) | Yicheng |||
| 3 | Jan 22 | [HTTP](tutorial/T03/) | Yicheng |||
| 4 | Feb 5 | [Select programming](tutorial/T04/) | Yitao |||
| 5 | Feb 12 | [Video streaming](tutorial/T05/) | Yitao | [Assignment 2](assignment/assignment-2) | 11:59:59 p.m., Sun, March. 9th |
| 6 | Feb 19 | [HTTP Proxy](tutorial/T06/) | Yitao |||
| 7 | Feb 26 | [TCP](tutorial/T07/) | Yitao |||
| 8 | Mar 12 | [UDP](tutorial/T08/) | Shaofeng |[Assignment 3](assignment/assignment-3) | 11:59:59 p.m., Mon, Apr. 14th|
| 9 | Mar 19 | [IP Routing](tutorial/T09/) | Shaofeng |||
| 10 | Mar 26 | [WTP](tutorial/T10/) | Shaofeng |||
| 11 | Apr 2 | [LS/DV Routing](tutorial/T11/) | Yicheng |||
| 12 | Apr 9 | [BGP](tutorial/T12/) | Shaofeng |||
| 13 | Apr 16 | [ARP](tutorial/T13/) | Yicheng |||



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
