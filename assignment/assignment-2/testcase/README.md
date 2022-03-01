## Test Cases 

For assignment 2, we have **8 test cases** in total. Each test case will test the performance of the code under a specific condition. The basic setting for each test case is as follows:

| Test Case | Points | Condition                                                    |
| --------- | ------ | ------------------------------------------------------------ |
| 1         | 10     | Test high bandwidth with low alpha value (slow bitrate increasing) |
| 2         | 10     | Test high bandwidth with large alpha value (fast bitrate increasing) |
| 3         | 10     | Test 0.5mbps bandwidth (middle bandwidth)                    |
| 4         | 10     | Test bandwidth change from 10mbps to 1mbps                   |
| 5         | 15     | Test sudden bandwidth drop to less than 100kbps (50kbs)      |
| 6         | 15     | Test two browser case                                        |
| 7         | 15     | Test two browser case, bandwidths sum up to 1000kbps         |
| 8         | 15     | Test two browser case, bandwidth changes to 1mbps in 25 sec, then changes back to 10mbps in 60 sec |

 To avoid unexpected error, please do not update the software in the published virtual machine and keep the environment consistent with the original published version.

## How to Run the Test Case

To run the test case, **you need to download the test script and run it locally through Mininet**. The working directory for running test cases should contain the following files:

```
Makefile 	<-- The Makefile that can compile your miProxy with "make"

** source c or cpp files ** <-- code files that will be compiled

start_server.py	 	<-- in starter_files directory
launch_firefox.py 	<-- in starter_files directory

firefox_open_url.py	<-- newly downloaded from testcase directory
TestCase.py 		<-- newly downloaded from testcase directory
```

After all files are ready, you can run the test case with the command: **(You need to run as "sudo")**

```
sudo python TestCase.py <testcase num> 
# <testcase num> in 1-8
```

After running test case 1-8, 8 log files will be generated for each test case separately. The generated log file for test case **N** is named `log<N>.log`. You should see files `log1.log log2.log ... log8.log` in the working directory after all test cases tested. 

## Autograder for Testing the Logs

With the generated logs, you can then upload them to the Autograder to test whether your `miProxy` can react correctly for various network conditions. **Please NOTE that: Autograder is used for debugging and testing your code only. The final grade for this assignment will be determined through running the submitted code by the TA.**

## Final Grading

The final grading will be conducted on the original published virtual machine for Assignment 2. Your submitted code will be tested with the released test script (`TestCase.py`). Then, the generated logs will be graded with the same grading script as the one in the Autograder. Your final grade will be based on the grading script. To pass the test case, except passing the grading script test with the log file, you should also ensure your program will not exit with an error. Additionally, there should not be any unexpected disconnection between the proxy and the browser or between the proxy and the server.  



 