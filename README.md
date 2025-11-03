# CSCI4430/ESTR4120 Computer Networks, Fall 2025 (term 1)

## Administrivia

### Schedule

- Lectures: 
  * Mon 2:30pm – 5:15pm, Y.C. Liang Hall 103
  * Tue 10:30am – 11:15am, Lee Shau Kee LT3
  * Tue 9:30am - 10:15am, Lee Shau Kee LT3 (ESTR)
- Tutorials:
  * Tue 11:30am – 12:15pm, Lee Shau Kee LT3

### Team
| Member | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Xu, Hong (Henry)](https://henryhxu.github.io/) | Prof | Mon 9-10am, Tue 1-2 pm, SHB 914. **By appointments only.** |
| [Feng, Yicheng](mailto:yichengfeng@link.cuhk.edu.hk)  | Head TA | Tue 2:30-4:30 pm, SHB 904. |
| [Wu, Shaofeng](mailto:sfwu22@cse.cuhk.edu.hk) | TA | Online (Piazza), SHB 117. |
| [Deng, Yangtao](mailto:ytdeng25@cse.cuhk.edu.hk) | TA | Thu 10-12 am, SHB 117. |

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
| Assessment item | CSCI Weight | ESTR Weight | 
| :---------------- | :--- | :--- |
| Assignments | 45% | 45% | 
| Tutorial Quizzes* | 5% | 0%
| Midterm Exam | 10% | 10%
| Final Exam | 40% | 35%
| Project | 0% | 10% |

\*: To encourage tutorial participation, quiz will be conducted at the tutorials randomly. We will randomly pick 5 tutorials and perform a quiz at the end of the tutorial. Each quiz is worth one mark.

## Schedules
<!--  Click on the topic to access the slides, and on the date to view the recording if provided. -->

### Lectures

| Week | Date | Topic(s) |  Textbook Readings  | Additional Readings
| :---: |:----------- | :-----------------: |  :------------: | :------------: |
|1| Sep 1; 2 | [Intro and Overview](lec/lec1.pptx) |  1.1, 1.3, 1.4 |
|2| Typhoon; Sep 9 | [Layering](lec/lec2.pptx) | 1.5, 2.2, 2.4 | [End-to-end arguments <br>in system design](https://web.mit.edu/Saltzer/www/publications/endtoend/endtoend.pdf)
|3| Sep 15; 16 | [Sockets and HTTP](lec/lec3.pptx); <br>[CDN, DNS](lec/lec4.pptx) | 2.2, 2.4
|4| Sep 22; [23](https://cuhk.zoom.us/rec/share/QeGUpNGskwXn7lCegbbjcBMJ6u43wFLFSSUeC1J0YTktktenpdR03aQ7ifjXIRHG.jfKHRYTSLQy6rfm1) | [Video, datacenters](lec/lec5.pptx) |  2.6
|5| Sep 29; 30 | [Transport layer](lec/lec6.pptx) | 3.1–3.4
|6| Oct 6; holiday | [TCP Basics](lec/lec7.pptx) |3.5, 3.6 | RFCs in the ppt
|7| Oct 13; no class | Midterm | 
|8| Oct 20; 21 | [Congestion control](lec/lec8.pptx) | 3.5, 3.6 | [BBR](https://github.com/google/bbr)
|9| Oct 27; 28 | [More on CC](lec/lec9.pptx); <br>[Network layer](lec/lec10.pptx) | 3.7, 4.1, 4.3.1, 4.3.2, 4.3.5 | [DCTCP](https://people.csail.mit.edu/alizadeh/papers/dctcp-sigcomm10.pdf)
|10| Nov 3; 4 | [Routing fundamentals](lec/lec11.ppt); <br>[Intra-domain routing](lec/lec12.pptx) | 5.1, 5.2, 5.3 | [How Dijkstra's Algorithm Works](https://www.youtube.com/watch?v=EFg3u_E6eHU)
|11| Nov 10; 11 | [Intra-domain routing](lec/lec12.pptx); <br>[Inter-domain routing](lec/lec13.pptx) | 5.1, 5.2, 5.3, 5.4 |
|12| Nov 17; 18 | [Inter-domain routing](lec/lec13.pptx); <br>[SDN](lectures/lec14.pptx) | 4.4, 5.5
|13| Nov 24; 25 | [Link layer](lectures/lec15.pptx); <br>[Final review](lectures/review.pptx) | 6.1, 6.3, 6.4


### Tutorials and Assignments
**NOTE**: This course adopts **Approach 1 – Prohibit all use of AI tools**.

| Week | Date | Topic | TA | Assignment | Due |
| :---: | :------------------ | :-----: | :-------------: | :-----: | :-------------: |
| 1 | Sep 2 | [Socket programming](tutorial/T01) | Yicheng | [Assignment 1](assignment/assignment-1) | 11:59:59 p.m., Wed, Sep. 24th |
| 2 | Sep 9 |[Performance metrics](tutorial/T02) | Yicheng |||
| 3 | Sep 16 | [HTTP](tutorial/T03) | Yicheng |||
| 4 | Sep 23 | [Select programming](tutorial/T04) ([Recording](https://drive.google.com/file/d/1gocGr0SARpiupDL6Hxlbo5kTqPSpH8pP/view?usp=sharing)) | Yangtao |[Assignment 2]() | 11:59:59 p.m., Sun, Oct. 26th |
| 5 | Sep 30 | [Video streaming](tutorial/T05) | Yangtao |||
| 6 | Oct 7 | holiday | | | |
| 7 | Oct 14 | [HTTP Proxy](tutorial/T06) | Yicheng |||
| 8 | Oct 21 | [TCP](tutorial/T07) | Yangtao |||
| 9 | Oct 28 | [UDP]() | Yicheng |[Assignment 3]() | 11:59:59 p.m., Sun, Nov. 30th|
| 10 | Nov 4 | [IP Routing]() | Yicheng |||
| 11 | Nov 11 | [WTP]() | Yangtao |||
| 12 | Nov 18 | [LS/DV Routing]() | Yangtao |||
| 13 | Nov 25 | [BGP]() | Yangtao |||

### ESTR Lectures

| Week | Date | Topic(s) |   Additional Readings
| :---: |:----------- |  :------------: | :------------: |
|1| Sep 2 | [Internet](lec/estr/estr1.pptx) (more from [IERG5090](lec/estr/ierg5090_lecture_notes_2.pdf)) |  [How to read a paper](lec/estr/HowtoReadPaper.pdf), [A Brief History of the Internet](lec/estr/L2-brief-history.pdf)
|2| Sep 9 | [P2P, security](lec/estr/estr2.pptx) |  
|3| Sep 16 | [Consistent hashing](lec/estr/estr3.pptx); [Chord](lec/estr/estr3_chord.pdf) | [STOC'97](https://dl.acm.org/doi/10.1145/258533.258660), [SIGCOMM'01](https://pdos.csail.mit.edu/papers/chord:sigcomm01/chord_sigcomm.pdf)
|4| [Sep 23](https://cuhk.zoom.us/rec/share/spyyJ0Gk6ASdabs3bzlDwJnqhBpyoXNe6NzkGODdEg_IHNFoz9_Nb9oMM7TBZoOX.qyyWOXwSSACTolZO) | [Video ABR](lec/estr/estr4.pptx); [puffer](lec/estr/estr4-puffer.pdf) | [Pensieve](https://dl.acm.org/doi/10.1145/3098822.3098843), [puffer](https://puffer.stanford.edu/)
|5| Sep 30 | [Parallelisms in LLM training](lec/estr/parallelism.pdf) | [Megatron-LM paper](https://arxiv.org/pdf/1909.08053), [code](https://github.com/NVIDIA/Megatron-LM)
|6| holiday |  |  
|7| no class | Travel to SOSP'25 
|8| Oct 20 | [Pantheon: An Arena for CC](https://www.usenix.org/sites/default/files/conference/protected-files/atc18_slides_yan.pdf) | [Pantheon site](https://pantheon.stanford.edu/); [Congestion-control throwdown on HotNets'17](https://www.youtube.com/watch?v=T1DCoNoVvRM&t=1s)
|9| Oct 27 | [DCTCP](lec/estr/estr7-dctcp.pptx) | [BBR repo](https://github.com/google/bbr)
|10| Nov 4 | [NAT & VPN](lec/estr/estr8-vpn.ppt)

### ESTR Individual Projects
- Proposal [1 mark]
  * Due: 23:59, Oct ~~22~~24, 2025 HKT
  * 1 page, 12-pt Times New Roman, single column, single spacing
  * LaTeX strongly encouraged, using the article class
  * Submit by emailing Henry directly with a title "[ESTR4120] Proposal - Student_name"
- Presentation [5 marks]
  * Due: Nov 18 & 25 lectures
  * Schedule to be announced
- Report [4 marks]
  * Due: 23:59, Dec 2, 2025 HKT
  * 5 pages, 12-pt Times New Roman, single column, single spacing
  * LaTeX strongly encouraged, using the article class
  * Submit by emailing Henry directly with a title "[ESTR4120] Report - Student_name"

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
- Use of AI tools
  * This course adopts **Approach 1 – Prohibit all use of AI tools**.
  * This means that, "Students are **not** allowed to use any AI tools in any kind of learning activity or assessment that will be counted towards students’ final grade of the course, or used for evaluating students’ attainment of the desired learning outcomes. Students are expected to produce their own work independently without any collaboration or use of AI tools. Such information should be spelt out clearly in the course outline or learning activity/assessment guide.", from CUHK's Guidelines on the Use of Artificial Intelligence Tools in Teaching, Learning and Assessments.
