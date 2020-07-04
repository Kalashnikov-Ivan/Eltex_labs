#!/bin/bash

PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin:";

#touch /home/st/test_log/log.txt;

echo "----System start----" >> /home/st/log/log.txt;
echo "User:" $(whoami)		>> /home/st/log/log.txt;
echo "Machine: $HOSTNAME"   >> /home/st/log/log.txt;
echo "Time: " $(/bin/date)  >> /home/st/log/log.txt;
echo "--------------------" >> /home/st/log/log.txt;
echo 						>> /home/st/log/log.txt;