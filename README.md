# CSCI4430, Computer Networks (Spring 2022)

## Administrivia

### Schedule [Online teaching only since Feb]
- Lectures: 
  * Mon 12:30pm – 2:15pm, ERB LT ([Zoom link](https://cuhk.zoom.us/j/92811984025?pwd=eGE4Um5SV0Nwd3RJTlh2WmFpV2wzdz09))
  * Tue 4:30pm – 5:15pm, ERB LT ([Zoom link](https://cuhk.zoom.us/j/95299586369?pwd=N2RnM3h6VkJlTG1ncVZHMEFsa0laUT09))
- Tutorials:
  * Thu 8:30am – 9:15am, MMW 710 ([Zoom link](https://cuhk.zoom.us/j/94590014376?pwd=NDdlRzVDQW9oQURyMU5ESTJEUHh3Zz09))
  * Thu 12:30pm – 1:15pm, MMW 703 ([Zoom link](https://cuhk.zoom.us/j/94590014376?pwd=NDdlRzVDQW9oQURyMU5ESTJEUHh3Zz09))

### Team
| Member | Role | Office Hours |
| :---------------- | :--- | :----------- |
| [Xu, Hong (Henry)](https://henryhxu.github.io/) | Prof | Tue 1-3 pm, SHB 914. **By appointments only.** |
| [Hu, Junliang](mailto:jlhu@cse.cuhk.edu.hk) | Head TA | Mon 2:30-4:30 pm, SHB 921. |
| [Song, Qingyu](mailto:qysong21@cse.cuhk.edu.hk) | TA | Wed 9:30-11:30 am, SHB 117. |
| [Zhang, Jingze](mailto:zhang_jing_ze@link.cuhk.edu.hk) | TA | Tue 2:30-4:30 pm, SHB 117. |

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
| Assessment item | CSCI Weight 
| :---------------- | :--- | 
| Assignments | 55% | 
| Tutorial Quizzes* | 5% |
| Final Exam | 40% | 

\*: To encourage tutorial participation, quiz will be conducted at the tutorials randomly. We will randomly pick 5 tutorials and perform a quiz at the end of the tutorial. Each quiz is worth one mark.

### ESTR students [canceled since Feb 8]
ESTR 4120 follows the same format as CSCI 4430, but with an additional project to be presented in the second half of the semester. The exams and quizzes will be the same as CSCI 4430.

Projects details will be announced in a later time.

## Schedules
Click on the topic to access the slides, and on the date to view the recording. 

### Lectures
| Week | Topic(s) | Recordings | Optional Readings from Textbook |
| :-----------: | :-----------------: | :------------: | :------------: | 
| 1 | [Intro and Overview](lecture/lec1.pptx) | [Jan 10](https://cuhk.zoom.us/rec/share/GMBuuyiGyLKiHf_dbTPYC1KZXTIFAOdwfq7bcpUrsU-QyzugFh0g9iMErY3SsSrW.YS3CeSVtEPexD0F1), [11](https://cuhk.zoom.us/rec/share/88tdIlzjsMBhNQxtWYdd6TB--z-L4uEZBVBQvVXYdaDLQ8c0kXVH1zTNizqc193u.ZO8WyP5rvFng777j) | 1.1, 1.3, 1.4
| 2 | [Layering](lecture/lec2.pptx); [Sockets and HTTP](lecture/lec3.pptx) | [Jan 17](https://cuhk.zoom.us/rec/share/c5VrWKFwujdmMsgG7X9yasAPxhWlx1jj_3Rss8WwsL76rVCn1Grbl_YPjFVExg.fQOAykjhesRzjjWg), [18](https://cuhk.zoom.us/rec/share/d186v4bsOmWlKBxqd4jIYp4Win1y7L2f97WYDmg1MG6wcXpj6l8S6z3ebEKNImC0.NUY8kc11kSrQuoVP) | 1.5, 2.2, 2.4
| 3 | [CDN, DNS](lecture/lec4.pptx) | [Jan 24](https://cuhk.zoom.us/rec/share/KofQlqZ0Le6pJfJRSxUCvydViVuIY0soEFZzi_-jpAsu1jKSIyedUdxs2Zak1-8D.OCkuSjtQ5dUXMqH4), [25](https://cuhk.zoom.us/rec/share/OqAjOywy6n5Dnc7Ol2ix50_cCdU1ZLsjrnCTjQTbbuyIbrho12LliuIzNk9SMkvV.Tn6y8B7LIBFWe0FQ) | 2.2, 2.4
| 4 | [Video, cloud & datacenters](lecture/lec5.pptx), [Transport layer](lecture/lec6.pptx) | [Feb 7](https://cuhk.zoom.us/rec/share/DARFr18scLH3vOhatySK7BFS2NWdxkIqiLG3Y9GBVI5HmLoSkOiCHsxeis_HmkXg.u9T9lTBaRHdat8fh), [8](https://cuhk.zoom.us/rec/share/ikaPJSkyz0pObEZEI0wLpayXMGCiqeB9pxfrE55C9as0WVh750A2GyWNMPJ1YMOB.r213Z8hCro7My7ZO) | 2.6, 3.1, 3.2, 3.3, 3.4
| 5 | [Transport layer](lecture/lec6.pptx) | [Feb 14](https://cuhk.zoom.us/rec/share/qyR78D1rH_WG87amLo_NlGpA2vhbFBZuBOTLzsyiSCJ79wruT46wlfY1ZUBX0m2s.IH0RI6OHlNTi2XGX), [15](https://cuhk.zoom.us/rec/share/Wf1-ZBOeMj0kwoe1sBQkN0k9DPEY1cNUw3DMUdyMy5bKvj3qHOHM7kzJLRAHt5pK.3kacaFTWgYxS5Xt8) |  3.1, 3.2, 3.3, 3.4
| 6 | [TCP basics](lecture/lec7.pptx), [Congestion control](lecture/lec8.pptx) | [Feb 21](https://cuhk.zoom.us/rec/share/aDq_1pJ0QEqf4NCO3cEd3ZrKnC5VqD0pTMwePi3hjLB-FCdVF88k-MrQEmnyoBXs.MX5NIn4E_1-_Oalu),  [22](https://cuhk.zoom.us/rec/share/CGF-uBY_9ruG5OR_uCW3BFXFwitaYFl4HgZYxMFphCLvCOd7ygZit1DfLC64DHxS.qCe38hoEtW19S-Jm) |  3.5, 3.6
| 7 | [Congestion control](lecture/lec8.pptx) | [Feb 28](https://cuhk.zoom.us/rec/share/9KKetSM9RIHOQg10dgsmw6QWJmLiM-Ak7SnAGZwWbN1NBhdRMVrUx4s7Tem0U0Pr.UMWv4yc4e0Q9hO4r), [Mar 1](https://cuhk.zoom.us/rec/share/B2ayVmKbqvrPslMh1s9EdRci3Aufs42pqTF8Arr6wJmIrgzLgh3-E926h1hG34nH.Sj5CAL9xcj61tO33) |  3.5, 3.6
| 8 | [More on CC](lecture/lec9.pptx), [Network layer and IP](lecture/lec10.pptx) | [Mar 7](https://cuhk.zoom.us/rec/share/J6sEcYYk_vYX7LypQmqgmXc4JpvkguGffFNsVrbvXe-R0HGlwRJLP3WPfZXGbcqX.RRIKgHEBAGyS6RrL), [8](https://cuhk.zoom.us/rec/share/A0Uj8XXALkzi-day_y0nRWTSM-GytiQ6w8itBheuqPXUVXd3oqZYmP33uf9fEMrY.KNAHR0v43F6i44GM) |  3.7; 4.1, 4.3.1, 4.3.2, 4.3.5
| 9 | [Network layer: IP routers](lecture/lec11.pptx) | [Mar 14](https://cuhk.zoom.us/rec/share/-pmllbAyE0gewxTkibJRuJUgoKMqEciyw9w1CzmROm_PMf9BhVAM0tYUiMrMbJYj.MpRa7p1LJpR3B3Ut), [15](https://cuhk.zoom.us/rec/share/iIW8LmGKCyUSX4jZZPohR9eOHR5QjHrbDJaBf32I3zelETG1zf9ljDKjr4ejbB8S.SXxrs22DE0JhS1Rp) | 4.2
| 10 | [Routing fundamentals](lecture/lec12.pptx), [Intra-AS routing](lecture/lec13.pptx) | Mar 21, 22 | 5.1, 5.2, 5.3

### ESTR lecture materials
| Week | Topic(s) | 
| :-----------: | :-----------------: | 
| 1 | [Internet](lecture/estr1.pptx) ([Jan 11](https://cuhk.zoom.us/rec/share/3SZewEFYrPtDs01sjRwfKvTSSavGl65htD0RBTSy4v9jEgeZHdk38FHHhaZAx_zC.We45sM8DXlSAhJvj))
| 2 | [More on HTTP; P2P](lecture/estr2.pptx) ([Jan 18](https://cuhk.zoom.us/rec/share/PMFQRt2pALxYSfvwqk-KeSAPWFO9NggI6V_F4qlj_0vxZkBdJ0BF8Pf-y1K-CeLH.gmx0QsnHaQlI6W21)) 
| 3 | [CDN, Anycast](lecture/estr3.pptx) ([Jan 25](https://cuhk.zoom.us/rec/share/Usy19DUczqZ9dCzoIlwgoZXFWHcVJns6LfQQl65FBrhm6QRaM463QXtJnNnnzKdM.ZV7pn34V5u2H8feB))
| 4 | [ABR in video streaming](lecture/estr4.pdf)

### Tutorials and Assignments

| Week | Topic | Recording | Assignment | Due |
| :---: | :------------------: | :-----: | :-------------: | :-------------: |
| 1 | [Socket programming](tutorial/T01/tut01.pptx) | [Jan 13](https://cuhk.zoom.us/rec/share/ocCYRX0Pv0ZZfA3qEMIRc9JM5jDZLR9w8x6rnRtBG84f6_1cuu-L0igeQW9SKoUe.OiV8_R37BIAKtOPd?startTime=1642033608000) | [Assignment 1](assignment/assignment-1) | ~~11:59:59 p.m., Sat, Jan 29th~~ 18:00:00 p.m., Mon, Jan 31st |
| 2 | [Performance metrics](tutorial/T02/tut02.pptx) | [Jan 20](https://cuhk.zoom.us/rec/share/bN593V2QGLPNNZea6JewUtsWXiS-CcTvXc5m0FW68vahSLNwvYsDtksM5tJu0O4K.FBghXgcsGMJ8eb_S?startTime=1642652855000) | ||
| 3 | [HTTP](tutorial/T03/tut03.pptx) | [Jan 27](https://cuhk.zoom.us/rec/share/axNautJdYKCtHOTSEwHOLNUdT5WIWvce7gXJ3Z3S_idsTYvcI3nXNIDwaOonIbFs.pSVZ_d_cjhTFRbqf?startTime=1643257789000) | ||
| 4 | [Select programming](tutorial/T04/tut04.pptx) | [Feb 10](https://cuhk.zoom.us/rec/share/CDOr9mp0_9bFNWxc_txlzdoPm460e2xpHs8uE4Z0lMC9wDneTIZ2m39OCboiU9dd.uoiGrZpNm07x-PKW) | [Assignment 2](assignment/assignment-2) |~~11:59:59 p.m., Sun, Feb 27th~~ 11:59:59 p.m., Sun., March 6th|
| 5 |[HTTP Streaming and TCP](tutorial/T05/tut05.pptx)|[Feb 17](https://cuhk.zoom.us/rec/play/uaZUp3aVwBU3KKjg9LJ7jicr4LU8bHtUhwiLPmHdXBxJelwLs2dax4ZV0FaFcnj-vwriN_tN1dtQ9SZM.Ox-oeJskmDqqumKI?autoplay=true&startTime=1645072024000)|||
| 6 |[HTTP Proxy and TCP](tutorial/T06/tut06.pptx)|[Feb 24](https://cuhk.zoom.us/rec/play/JYn0vx0UWM_xBrHpb9YOAoUbv48sguxQmoNXq61bI-F5SRNn9N-VcVNci_b87bPKRC55kT8AkvxbFd5L.5e5IuA88lu64Q-3G?autoplay=true&startTime=1645676927000)|||
| 7 |[TCP Congestion Control](tutorial/T07/tut07.pptx)|[Mar 3](https://cuhk.zoom.us/rec/play/nnzhtdIPW04zDjaoAMY1aZODoaObZFDxjV07LLaiPcP-dNh1nEsjCqZBnU-jSZUP6-CCjN2i-xonqnMr.3b5D-22kFZW34eB2?autoplay=true&startTime=1646267408000)|||
| 8 |[UDP Socket programming](tutorial/T08/tut08.pptx)|[Mar 10](https://cuhk.zoom.us/rec/play/7Fosstztv2zG6Sl4OI0_HliePhxHo4_yifN-VtZrVIPrMUrTId-9DAGaVUjCJL3PfIS4t58971yKZLBM.qaYOMX7_IoLguOF0?autoplay=true&startTime=1646886484000)|[Assignment 3](assignment/assignment-3)||
| 9 |[IP and Network](tutorial/T09/tut09.pptx)|[Mar 17](https://cuhk.zoom.us/rec/play/dK7ZJZicHPfBUNM76Dfgg7AYs69t3QYQMo0KA2jUh3_9jvYEs57B4ZvRJyt5qew5UTlyEQAMaFz9Njo4.XjtPPx4KgylH-78X?autoplay=true&startTime=1647491403000)|||


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
