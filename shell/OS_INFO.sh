#!/bin/bash 
DATE=`date +"%Y-%m-%d__%H:%M:%S"`
HOST=`uname -n`
OS_NAME=`uname -o`
OS_VERSION=`uname -r`
UP_TIME=`uptime -p | tr -s " " "_"`
LOAD_TIME=`uptime | tr -s " " "\n" | tail -n 3 | tr -s "\n" " "`
DISK=(`df -m | sort -n -k 2 | tail -n 1 | awk '{printf("%d %d", $2, $5)}';`)
MEM=(`free -m| tail -n +2 | head -n -1 | awk '{printf("%s %s %.2f", $2, $3, $3*100/$2)}'`)
echo $DATE $HOST $OS_NAME $OS_VERSION $UP_TIME $LOAD_TIME ${DISK[0]} ${DISK[1]} ${MEM[0]} ${MEM[1]} ${MEM[2]}
