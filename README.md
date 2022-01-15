# CSCI4430, Computer Networks (Spring 2022)

## Administrivia

### Schedule
- Lectures: 
  * Mon 12:30pm -- 2:15pm, ERB LT ([Zoom link](https://cuhk.zoom.us/j/92811984025?pwd=eGE4Um5SV0Nwd3RJTlh2WmFpV2wzdz09))
  * Tue 4:30pm -- 5:15pm, ERB LT ([Zoom link](https://cuhk.zoom.us/j/95299586369?pwd=N2RnM3h6VkJlTG1ncVZHMEFsa0laUT09))
- ESTR lectures: 
  * Tue 5:30pm -- 6:15pm, LSB G34 ([Zoom link](https://cuhk.zoom.us/j/96114020070?pwd=RTB5c2FZaEtLTXBXWFQ4Q1FaQUJFUT09))
- Tutorials:
  * Thu 8:30am -- 9:15am, MMW 710 ([Zoom link](https://cuhk.zoom.us/j/94590014376?pwd=NDdlRzVDQW9oQURyMU5ESTJEUHh3Zz09))
  * Thu 12:30pm -- 1:15pm, MMW 703 ([Zoom link](https://cuhk.zoom.us/j/94590014376?pwd=NDdlRzVDQW9oQURyMU5ESTJEUHh3Zz09))

### Team
| Member | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Xu, Hong (Henry)](https://henryhxu.github.io/) | Prof | Tue 1-3 pm, SHB 914. **By appointments only.**
| [Hu, Junliang](mailto:jlhu@cse.cuhk.edu.hk) | Head TA | Mon 2:30-4:30 pm, SHB 921.
| [Song, Qingyu](mailto:qysong21@cse.cuhk.edu.hk) | TA | Wed 9:30-11:30 am, SHB 117.
| [Zhang, Jingze](mailto:zhang_jing_ze@link.cuhk.edu.hk) | TA | Tue 2:30-4:30 pm, SHB 117.

### Piazza
The Piazza page for this course is [here](https://piazza.com/cuhk.edu.hk/spring2022/csci4430).
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
| Tutorial Quizzes* | 5% | 5%
| Final Exam | 40% | 30%
| Project | - | 10%

\*: To encourage tutorial participation, quiz will be conducted at the tutorials randomly. We will randomly pick 5 tutorials and perform a quiz at the end of the tutorial. Each quiz is worth one mark.

### ESTR students
ESTR 4120 follows the same format as CSCI 4430, but with an additional project to be presented in the second half of the semester. The exams and quizzes will be the same as CSCI 4430.

Projects details will be announced in a later time.

## Schedules
Click on the date to view the video recording. Click on the topic to access the slides.

### Lecture (subject to change, espcially ESTR topics)
| Week | Monday | Tuesday | ESTR | Optional Readings |
| :--- | :--- | :--- | :--- | :--- | 
| 1 (Jan 10) | [Intro and Overview](lecture/lec1.pptx) ([recording](https://cuhk.zoom.us/rec/share/GMBuuyiGyLKiHf_dbTPYC1KZXTIFAOdwfq7bcpUrsU-QyzugFh0g9iMErY3SsSrW.YS3CeSVtEPexD0F1)) | [Intro and Overview](lecture/lec1.pptx) ([recording](https://cuhk.zoom.us/rec/share/88tdIlzjsMBhNQxtWYdd6TB--z-L4uEZBVBQvVXYdaDLQ8c0kXVH1zTNizqc193u.ZO8WyP5rvFng777j)) | [Internet](lecture/estr1.pptx) ([recording](https://cuhk.zoom.us/rec/share/3SZewEFYrPtDs01sjRwfKvTSSavGl65htD0RBTSy4v9jEgeZHdk38FHHhaZAx_zC.We45sM8DXlSAhJvj)) | 1.1, 1.3, 1.4
| 2 (Jan 17) | [Layering](lecture/lec2.pptx); [Socket programming, HTTP](lecture/lec3.pptx) | [Socket programming, HTTP](lecture/lec3.pptx) | [More on HTTP; P2P](lecture/estr2.pptx) | 1.5, 2.2, 2.4
| 3 (Jan 24) |  | 
| 4 (Feb 7) |  | 


### Tutorial and Assignments

| Week | Topic | Recording | Assignment | Due | 
| :--- | :--- | :--- | :--- | :--- |
| 1 | [Socket programming](tutorial/T01/tut01.pptx) | [link](https://cuhk.zoom.us/rec/share/ocCYRX0Pv0ZZfA3qEMIRc9JM5jDZLR9w8x6rnRtBG84f6_1cuu-L0igeQW9SKoUe.OiV8_R37BIAKtOPd?startTime=1642033608000) | [Assignment 1](assignment/assignment-1) | Sat, 29 Jan. 11:59:59 p.m.
| 2 | [Performance metrics](tutorial/T02/tut02.pptx) | [link]() | 


## Course policies
- *Special teaching arrangement* for students who cannot enter HK:
  * Recordings will be provided for each lecture or tutorial session. No live lecture will be provided.
  * Inform the course instructor, Henry, **immediately** when you can physically attend the class, so we can avoid the hassle of hybrid mode teaching.
- Homework and project: 
  * No late submission. No exception.
  * According to the University’s regulation, every assignment must be accompanied by a signed declaration of originality; submissions without it will receive zero mark.
  * The declaration form is available [here](declaration_en.doc).
- Lecture and tutorial:
  * Be on time. Set your mobile device to vibration/silient mode.
  * Feel free to ask questions and raise comments during the lecture, but we can only entertain short questions and discussions in-class.
  * Longer and deeper discussion and questions can happen in tutorials.
  * Follow University's regulations on COVID, including use of masks, hand sanitization, seating with social distance, etc.
