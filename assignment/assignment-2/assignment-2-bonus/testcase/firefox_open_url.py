import subprocess
import sys
import os

if len(sys.argv) != 3:
	print 'Error: Usage is python launch_firefox.py <profile_num> <url>'
	exit(1)

profileNum = str(int(sys.argv[1]))
url = sys.argv[2]
devNull = open(os.devnull, 'w')
subprocess.call(["sudo", "-u", "csci4430", "firefox", "-P", "csci4430profile" + profileNum, "-new-window", url], stdout=devNull, stderr=devNull)
