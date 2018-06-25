#!/bin/bash
DATE=`date +"%Y-%m-%d__%H:%M:%S"`;
#$2 sum $4 rest $5 perc 
DISK_INFO=(`df -m | grep -v tmpfs | tail -n 2 |awk '{printf("%-8s %-8d %-8d %d%\n", $6, $2, $4, $5);}'`)
LEN=`df -m | grep -v tmpfs | tail -n 2 | wc -l`
ALL=0
REST=0
for i in `seq 0 $[$LEN-1]`;do
    echo $DATE NAME = ${DISK_INFO[$i*4]} SIZE = ${DISK_INFO[$i*4+1]} REST = ${DISK_INFO[$i*4+2]} PREC = ${DISK_INFO[$i*4+3]}
    ALL=$[$ALL+${DISK_INFO[$i*4+1]}]
    REST=$[$REST+${DISK_INFO[$i*4+2]}]
done
echo $ALL $REST | awk '{printf("Surplus Rate : %d%\n", $2*100/$1)}';
